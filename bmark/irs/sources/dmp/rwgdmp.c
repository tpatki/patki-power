#include "irs.h"
#include "irsdmp.h"
#ifdef SILO
int rwgdmp(DBfile *idbidin, DBfile *idbidout, char* qvarnames[], int *nqvar,
           char* ucdnames[], int *nucdvar, int iblk, int gblk)
{
   int i;
   int myintopt;
   int centering;
   char outstring[20];    
   char dirnamein[40];      
   char dirnameout[40];      
   int mylopt[3]={0,0,0};
   int myhopt[3]={0,0,0};
   int error;
   int n ;
   DBzonelist *zones;
   DBucdmesh *ucdmesh;
   DBucdvar *ucdvar;
   DBquadmesh *quadmesh;
   DBquadvar *quadvar;
   DBmaterial *material;
   DBoptlist *ioptnod;
   DBtoc *toc;
   error = 0 ;
   ioptnod = DBMakeOptlist( MAXOPTS );
   error = DBReadVar(idbidin, "dtime", &ttime);
   error = DBReadVar(idbidin, "cycle", &cycle);
   sprintf(dirnamein,"/domain%i",iblk);
   error = DBSetDir(idbidin, dirnamein);
   sprintf(dirnameout,"/domain%i",gblk);
   error = DBMkDir(idbidout, dirnameout);
   error = DBSetDir(idbidout, dirnameout);
   quadmesh = DBGetQuadmesh(idbidin,"hydro_mesh");
   if (quadmesh->ndims == 3) {
      error = error + DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
      error = error + DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
      error = error + DBAddOption( ioptnod, DBOPT_LO_OFFSET, mylopt );
      error = error + DBAddOption( ioptnod, DBOPT_HI_OFFSET, myhopt );
      myintopt = DB_CARTESIAN;
      error = error + DBAddOption( ioptnod, DBOPT_COORDSYS, &myintopt );
      error = error + DBAddOption( ioptnod, DBOPT_XLABEL, "X");
      error = error + DBAddOption( ioptnod, DBOPT_YLABEL, "Y");
      error = error + DBAddOption( ioptnod, DBOPT_ZLABEL, "Z");
      error = error + DBAddOption( ioptnod, DBOPT_XUNITS, "cm");
      error = error + DBAddOption( ioptnod, DBOPT_YUNITS, "cm");
      error = error + DBAddOption( ioptnod, DBOPT_ZUNITS, "cm");
   } else {
      error = error + DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
      error = error + DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
      error = error + DBAddOption( ioptnod, DBOPT_LO_OFFSET, mylopt );
      error = error + DBAddOption( ioptnod, DBOPT_HI_OFFSET, myhopt );
      if (quadmesh->coord_sys == DB_CARTESIAN) {
         myintopt = DB_CARTESIAN;
         error = error + DBAddOption( ioptnod, DBOPT_COORDSYS, &myintopt );
         error = error + DBAddOption( ioptnod, DBOPT_XLABEL, "X");
         error = error + DBAddOption( ioptnod, DBOPT_YLABEL, "Y");
      } else {
         myintopt = DB_CYLINDRICAL;
         error = error + DBAddOption( ioptnod, DBOPT_COORDSYS, &myintopt );
         error = error + DBAddOption( ioptnod, DBOPT_XLABEL, "Z");
         error = error + DBAddOption( ioptnod, DBOPT_YLABEL, "R");
      }
      error = error + DBAddOption( ioptnod, DBOPT_XUNITS, "cm");
      error = error + DBAddOption( ioptnod, DBOPT_YUNITS, "cm");
   }
   error = DBPutQuadmesh(idbidout,"hydro_mesh", 
                                  quadmesh->labels, 
                                  quadmesh->coords,
                                  quadmesh->dims, 
                                  quadmesh->ndims, DB_DOUBLE, 
                                  DB_NONCOLLINEAR, ioptnod);   
   DBFreeQuadmesh(quadmesh);
   strcpy(outstring,"Materials");
   material = DBGetMaterial(idbidin,outstring);
   error = DBPutMaterial(idbidout, material->name,
                                 "hydro_mesh",
                                  material->nmat,
                                  material->matnos,
                                  material->matlist,
                                  material->dims,
                                  material->ndims,
                                  material->mix_next,
                                  material->mix_mat,
                                  material->mix_zone,
                                  material->mix_vf,
                                  material->mixlen, DB_DOUBLE,ioptnod);
   DBFreeMaterial(material);
   toc = DBGetToc(idbidin);
   if (toc->nucdvar > 0 ) {
      *nucdvar = toc->nucdvar;
      ucdmesh = DBGetUcdmesh(idbidin,"slide_mesh");
      error = DBPutUcdmesh(idbidout,"slide_mesh",
                            ucdmesh->ndims,
                            ucdmesh->labels,
                            ucdmesh->coords,
                            ucdmesh->nnodes,
                            ucdmesh->zones->nzones,
                            "slide_zlist",NULL, DB_DOUBLE, ioptnod);
      zones = ucdmesh->zones;
      error = DBPutZonelist(idbidout,"slide_zlist",
                            zones->nzones,
                            zones->ndims,
                            zones->nodelist,
                            zones->lnodelist,0,
                            zones->shapesize,
                            zones->shapecnt,1);
      for (i = 0; i < toc->nucdvar; i++) {
         strcpy(ucdnames[i],toc->ucdvar_names[i]);
         ucdvar = DBGetUcdvar(idbidin,toc->ucdvar_names[i]);
         error = DBPutUcdvar1(idbidout,ucdvar->name,
                             "slide_mesh",
                              ucdvar->vals[0],
                              ucdvar->nels,
                              NULL,
                              0,
                              ucdvar->datatype,
                              ucdvar->centering, ioptnod);
         DBFreeUcdvar(ucdvar);
      }
   }
   *nqvar = toc->nqvar;
   for (i = 0; i < toc->nqvar; i++) {
      strcpy(qvarnames[i],toc->qvar_names[i]);
      quadvar = DBGetQuadvar(idbidin,toc->qvar_names[i]);
      if (quadvar->align[0]>0) {
        centering = DB_ZONECENT;
      } else {
        centering = DB_NODECENT;
      }
      if (quadvar->mixlen>0) {
         error = DBPutQuadvar1(idbidout,quadvar->name,
                                   "hydro_mesh",
                                   quadvar->vals[0], 
                                   quadvar->dims, 
                                   quadvar->ndims,
                                   quadvar->mixvals[0], 
                                   quadvar->mixlen, 
                                   quadvar->datatype,
                                   centering, ioptnod);
      } else {
         error = DBPutQuadvar1(idbidout,quadvar->name,
                                   "hydro_mesh",
                                   quadvar->vals[0], 
                                   quadvar->dims, 
                                   quadvar->ndims,
                                   NULL,
                                   0, 
                                   quadvar->datatype,
                                   centering, ioptnod);
      } 
      DBFreeQuadvar(quadvar);
   }
   error = DBFreeOptlist(ioptnod);
   return(error) ;
}
#endif
