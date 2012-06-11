#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "irsobjects.h"
#include "Command.h"
#include "Hash.h"
#include "NodeList.h"
#include "Rgst.h"
#include "Region.h"
#include "Source.h"
#include "Transform.h"
#include "UserList.h"
int SourceNew_gen( void ) {
   char *name;
   int   iblk;
   SourceNew_t *mysrc, *dsrc;
   RGST_AttributeElem_t *srclist;
   for (iblk = 0; iblk < nblk; iblk++) {   
      SourceNew_free(domains[iblk].hash);
      srclist = rgst_list_attr(A_OBJECT, "SourceList");
      while (srclist != NULL) {
         name = ATTR_GET_OBJECT_NAME(srclist);
         mysrc  = SourceNew_find(name, NULL);
         SourceNew_domain(mysrc, &domains[iblk]);
         srclist = srclist->next;
      }
   }
   return(0);
}
void SourceNew_domain(SourceNew_t *mysrc, Domain_t *domain) {
   char *name;
   char myname[MAXLINE];
   SourceNew_t  *dsrc;
   NodeList_t *nl;
   dsrc = SourceNew_new(mysrc->name);
   sprintf(myname,"NL_%s",mysrc->name);
   nl = NodeList_find(myname);
   if (mysrc->centering == ZONAL_ARRAY) {
      NodeWindow_buildndx(nl->list, NDX_GLBL_PHONY, NDX_ZONAL, domain->gblk,
                          &dsrc->len, &dsrc->ndx);
   } else {
      NodeWindow_buildndx(nl->list, NDX_GLBL_PHONY, NDX_NODAL, domain->gblk,
                          &dsrc->len, &dsrc->ndx);
   } 
   SourceNew_copy(mysrc, dsrc);
   SourceNew_add(dsrc, domain->hash);
}
void SourceNew_copy(SourceNew_t *src1, SourceNew_t *src2) {
   int i;
   src2->type = NULL;
   src2->region    = src1->region;
   src2->centering = src1->centering;
   src2->additive  = src1->additive;
   src2->mode      = src1->mode;
   src2->lenData = src1->lenData;
   src2->depData = MALLOT(double, src1->lenData);
   src2->indData = MALLOT(double, src1->lenData);
   for ( i = 0; i < src1->lenData; i++) {
      src2->depData[i] = src1->depData[i];
      src2->indData[i] = src1->indData[i];
   }
   if (src1->tableName != NULL) src2->tableName = strsave(src1->tableName);
   if (src1->depField  != NULL) src2->depField = strsave(src1->depField);
   if (src1->indField1 != NULL) src2->indField1 = strsave(src1->indField1);
   if (src1->indField2 != NULL) src2->indField2 = strsave(src1->indField2);
   if (src1->indField3 != NULL) src2->indField3 = strsave(src1->indField3);
   src2->dSourceEdit = src1->dSourceEdit;
   src2->SourceEdit  = src1->SourceEdit;
}
int SourceNew_init(SourceNew_t *mysrc) {
   mysrc->type = NULL;
   mysrc->len = 0;
   mysrc->ndx = NULL;
   mysrc->region    = -1;
   mysrc->centering = -1;
   mysrc->additive  =  0;
   mysrc->mode      =  _SourceUnknown_;
   mysrc->depData = NULL;
   mysrc->indData = NULL;
   mysrc->lenData = 0;
   mysrc->tableName = NULL;
   mysrc->depField = NULL;
   mysrc->indField1 = NULL;
   mysrc->indField2 = NULL;
   mysrc->indField3 = NULL;
   mysrc->dSourceEdit = 0.;
   mysrc->SourceEdit  = 0.;
   return(0);
}
SourceNew_t* SourceNew_new(char *name)
{
   int len;
   SourceNew_t *mysrc;
   mysrc = MALLOT(SourceNew_t, 1);
   mysrc->name = strsave(name);
   SourceNew_init(mysrc);
   return(mysrc);
}
void SourceNew_free(HashTable_t *hash) {
   char *name;
   SourceNew_t *mysrc;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      name = ATTR_GET_OBJECT_NAME(srclist);
      mysrc  = SourceNew_find(name, hash);
      srclist = srclist->next;
      if (mysrc != NULL) {
         if (hash == NULL) {
            rgst_del(name);
         } else {
            hash_del2(name, "SourceNew_t", hash);
         } 
         SourceNew_release(mysrc);
      } 
   }
}
void SourceNew_release( SourceNew_t *mysrc) {
   FREEMEM(mysrc->name);
   FREEMEM(mysrc->type);
   if (mysrc->len > 0) {
      FREEMEM(mysrc->ndx);
   }
   if (mysrc->lenData > 0) {
      FREEMEM(mysrc->depData);
      FREEMEM(mysrc->indData);
   }
   if (mysrc->tableName != NULL)  FREEMEM(mysrc->tableName);
   if (mysrc->depField  != NULL)  FREEMEM(mysrc->depField);
   if (mysrc->indField1 != NULL)  FREEMEM(mysrc->indField1);
   if (mysrc->indField2 != NULL)  FREEMEM(mysrc->indField2);
   if (mysrc->indField3 != NULL)  FREEMEM(mysrc->indField3);
   FREEMEM(mysrc);
}
void SourceNew_add( SourceNew_t *mysrc, HashTable_t *hash) {
   char msg[MAXLINE];
   char name[MAXLINE];
   sprintf(name,"SourceNew_%s",mysrc->name);
   if (hash == NULL) {
      if (rgst_check_for_obj(name)) {
         sprintf(msg,"Attempting to add an already existing source - %s",mysrc->name);
         ctlerror("SourceNew_add",msg);
      }
      rgst_add(name,"SourceNew_t", mysrc, NULL);
      rgst_add_attr(A_OBJECT, name, "SourceList");
   } else {
      hash_add(name,"SourceNew_t", mysrc, hash);
   }
}
SourceNew_t *SourceNew_find(char *name, HashTable_t *hash) {
   SourceNew_t *mysrc = NULL;
   if (hash == NULL) {
     mysrc = (SourceNew_t *) rgst_get_t(name, "SourceNew_t");
   } else {
     mysrc = (SourceNew_t *) hash_lookup_obj(name, hash);
   } 
   return(mysrc);
}
#ifdef SILO
int SourceNew_rdsilo ( DBfile *idbid ) {
   char dirname[MAXLINE];
   int i,n;
   int error;
   SourceNew_t *mysrc;
   DBShowErrors(DB_NONE, NULL);
   error = DBSetDir(idbid, "/Global/Source");
   DBShowErrors(DB_TOP, NULL);
   if (error != 0) return(0);
   error += DBReadVar(idbid, "NumSources",&n);
   for (i = 0; i < n; i++) {
      sprintf(dirname,"/Global/Source/Source%i",i);
      mysrc = rgst_read_struct_in_dir(idbid, dirname, "SourceNew_t", NULL, NULL);
      SourceNew_add(mysrc, NULL);
      SourceNew_setattr(mysrc);
   }
   return(0);
}
#endif

#ifdef SILO
int SourceNew_wtsilo ( DBfile *idbid ) {
   char *me = "SourceNew_wtsilo";
   char *name;
   char dirname[MAXLINE];
   int n;
   int error = 0;
   int dims[1];
   SourceNew_t *mysrc;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   if (srclist == NULL) return(error);
   error += DBMkDir(idbid, "/Global/Source");
   error += DBSetDir(idbid, "/Global/Source");
   if (error != 0) ctlerror(me,gv_errmsg_DBMkDir);
   n = 0;
   while (srclist != NULL) {
      name = ATTR_GET_OBJECT_NAME(srclist);
      mysrc  = SourceNew_find(name, NULL);
      sprintf(dirname,"/Global/Source/Source%i",n);
      error += rgst_write_struct_in_dir(idbid, dirname, "SourceNew_t", mysrc, NULL);
      n++;
      srclist = srclist->next;
   }
   error += DBSetDir(idbid, "/Global/Source");
   dims[0] = 1;
   error += DBWrite(idbid, "NumSources",&n,dims,1,DB_INT);
   if (error != 0) {
      ctlerror(me, "Error writing out Sources.");
   }
   return(0);
}
#endif
int SourceNew_input (void) {
   char *me = "SourceNew_input" ;
   char *oname;
   char op[MAXWORD], msg[MAXLINE], ndxname[MAXLINE] , name[MAXLINE];
   int i;
   int gotone;
   int error = 0 ;
   int cflag = 0 ;
   NodeWindow_t *ndxin = NULL ;
   SourceNew_t *mysrc;
   sprintf(op,"src");
   error = NodeWindow_read( op, &ndxin ) ;
   if ( error != 0 ) {
      sprintf( msg, "Error reading index list for %s", op ) ;
      ctlwarning( me, msg ) ;
      return( error ) ;
   }
   NodeList_addnextseq( "NL_SRC", ndxin, ndxname ) ;
   oname = ObjectName_get();
   if (oname != NULL) {
      strcpy(name,oname);
      sprintf(msg,"NL_%s",name);
      NodeList_rename(ndxname, msg);
   } else {
      strcpy(name,ndxname + 3);
   } 
   geta( op ) ;
   mysrc = SourceNew_new(name);
   geta( op ) ;
   mysrc->type = strsave(op);
   SourceNew_add(mysrc, NULL);
   error = SourceNew_setattr(mysrc);
   if ( error != 0 ) {
      sprintf( msg, "Source type %s is not recognized",op);
      ctlwarning( me, msg ) ;
      SourceNew_release(mysrc);
      NodeWindow_free(ndxin);
      return( error ) ;
   }
   if (mysrc->mode == _SourceTimeDep_) mysrc->lenData = geti(&cflag);
   if ((!strcmp(mysrc->type, "erate2")) ||
       (!strcmp(mysrc->type, "erate4")) ||
       (!strcmp(mysrc->type, "tesrcint1")) ||
       (!strcmp(mysrc->type, "tesrcint2")) ||
       (!strcmp(mysrc->type, "tisrcint1")) ||
       (!strcmp(mysrc->type, "tisrcint2")) ||
       (!strcmp(mysrc->type, "tsrcint"))) {
       mysrc->region = geti(&cflag);
       gotone = 1;
       while (gotone) {
          peekc(op);
          if (!strcmp(op,"species")) {
             geta(op);
             error = UserList_parse(ndxname);
             if (error != 0) {
                ctlwarning(me,"Failed to read in list of species.");
             }
          } else if (!strcmp(op,"table")) {
             geta(op);
             mysrc->mode    = _SourceTable_;
          } else {
             gotone = 0;
          } 
       }
   }
   if (mysrc->mode == _SourceTimeDep_) {
      mysrc->indData = MALLOT(double, mysrc->lenData);
      mysrc->depData = MALLOT(double, mysrc->lenData);
      for (i = 0; i < mysrc->lenData; i++) {
         mysrc->indData[i] = getf(&cflag);
         mysrc->depData[i] = getf(&cflag);
      }
   } else if (mysrc->mode == _SourceConstant_) {
      mysrc->lenData = 1;
      mysrc->indData = MALLOT(double, 1);
      mysrc->depData = MALLOT(double, 1);
      mysrc->depData[0] = getf(&cflag);
      mysrc->indData[0] = 0.;
   } else if (mysrc->mode == _SourceTable_) {
      
   } 
   return( error ) ;
}
int SourceNew_setattr( SourceNew_t *mysrc ) {
   char name[MAXLINE];
   sprintf(name,"SourceNew_%s",mysrc->name);
   if (!strcmp(mysrc->type,"dsrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceDensity");
      rgst_add_attr(A_OBJECT, name, "SourceMassEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode = _SourceConstant_;
   } else if (!strcmp(mysrc->type,"esrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceEnergy");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"psrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourcePressure");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"tesrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceElectronTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"tisrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceIonTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"tesrcint1")) {
      rgst_add_attr(A_OBJECT, name, "SourceElectronTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"tisrcint1")) {
      rgst_add_attr(A_OBJECT, name, "SourceIonTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"tesrcint2")) {
      rgst_add_attr(A_OBJECT, name, "SourceElectronTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"tisrcint2")) {
      rgst_add_attr(A_OBJECT, name, "SourceIonTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"xvsrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceXVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceXmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"yvsrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceYVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceYmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"zvsrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceZVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceZmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"xasrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceXAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"yasrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceYAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"zasrc1")) {
      rgst_add_attr(A_OBJECT, name, "SourceZAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"xasrc3")) {
      rgst_add_attr(A_OBJECT, name, "SourceXAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"yasrc3")) {
      rgst_add_attr(A_OBJECT, name, "SourceYAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"zasrc3")) {
      rgst_add_attr(A_OBJECT, name, "SourceZAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"xeuler")) {
      rgst_add_attr(A_OBJECT, name, "SourceXAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"yeuler")) {
      rgst_add_attr(A_OBJECT, name, "SourceYAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"zeuler")) {
      rgst_add_attr(A_OBJECT, name, "SourceZAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"xminsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceXCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"yminsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceYCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"zminsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceZCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"xmaxsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceXCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"ymaxsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceYCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"zmaxsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceZCoordinate");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceConstant_;
   } else if (!strcmp(mysrc->type,"dsrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceDensity");
      rgst_add_attr(A_OBJECT, name, "SourceMassEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"dsrc3")) {
      rgst_add_attr(A_OBJECT, name, "SourceDensity");
      rgst_add_attr(A_OBJECT, name, "SourceMassEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTable_;
   } else if (!strcmp(mysrc->type,"esrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceEnergy");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"erate2")) {
      rgst_add_attr(A_OBJECT, name, "SourceEnergyRateHydro");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"erate4")) {
      rgst_add_attr(A_OBJECT, name, "SourceEnergyRateRadiation");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"psrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourcePressure");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"tesrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceElectronTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"tisrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceIonTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"xvsrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceXVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceXmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"yvsrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceYVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceYmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"zvsrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceZVelocity");
      rgst_add_attr(A_OBJECT, name, "SourceZmomEdit");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"xasrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceXAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"yasrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceYAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"zasrc2")) {
      rgst_add_attr(A_OBJECT, name, "SourceZAcceleration");
      mysrc->centering = NODAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"tsrc")) {
      rgst_add_attr(A_OBJECT, name, "SourceRadiationTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else if (!strcmp(mysrc->type,"tsrcint")) {
      rgst_add_attr(A_OBJECT, name, "SourceRadiationTemperature");
      rgst_add_attr(A_OBJECT, name, "SourceEnergyEdit");
      mysrc->centering = ZONAL_ARRAY;
      if (mysrc->mode == _SourceUnknown_) mysrc->mode =  _SourceTimeDep_;
   } else {
      return(-1);
   } 
   return(0);
}
void SourceNew_general( double *field, double *weight, char *mysrcname, 
                         double dtime, Domain_t *domain, 
			 SourceEditMode_t ifedit)
{
   int i;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, mysrcname);
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      int flag  = 0;
      int mflag;
      if (mysrc->additive) flag = 1;
      mflag = 1 - flag;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      if (mysrc->mode == _SourceConstant_) {
         for (i = 0; i < len; i++) {
            double f = field[ndx[i]];
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += (mysrc->depData[0] - mflag * f)*weight[ndx[i]];
            }
            field[ndx[i]] = flag * f + mysrc->depData[0];
         }
      } else if (mysrc->mode == _SourceTimeDep_) {
         double value;
	 if (dtime >= mysrc->indData[mysrc->lenData - 1]) {
	    value = mysrc->depData[mysrc->lenData - 1];
	 } else if (dtime <= mysrc->indData[0]) {
	    value = mysrc->depData[0];
	 } else {
            if (RGST_QUERY_OBJECT_ATTR(name, "QuadInterp")) {
            } else {
            } 
         } 
         for (i = 0; i < len; i++) {
            double f = field[ndx[i]];
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += (value - mflag * f) * weight[ndx[i]];
            }
            field[ndx[i]] = value;
         }
      } else if (mysrc->mode == _SourceTable_) {
         if (len > 0) {
            double *value = MALLOT(double, len);
            SourceNew_table (mysrc, value, dtime, domain);
            for (i = 0; i < len; i++) {
               double f = field[ndx[i]];
               field[ndx[i]] = flag * field[ndx[i]] + value[i];
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += (value[i] - mflag * f) * weight[ndx[i]];
               }
            }
            FREEMEM(value);
         }
      } 
      srclist = srclist->next;
   }
}
void SourceNew_temperature( double *e, double *t, double *dedt,
                         double *weight, char *mysrcname, double dtime, 
                         Domain_t *domain, SourceEditMode_t ifedit)
{
   int i;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, mysrcname);
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      if (mysrc->mode == _SourceConstant_) {
         for (i = 0; i < len; i++) {
            double de = dedt[ndx[i]] * (mysrc->depData[0] - t[ndx[i]]);
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += de * weight[ndx[i]];
            }
            e[ndx[i]] += de;
            t[ndx[i]]  = mysrc->depData[0];
         }
      } else if (mysrc->mode == _SourceTimeDep_) {
         double value;
	 if (dtime >= mysrc->indData[mysrc->lenData - 1]) {
	    value = mysrc->depData[mysrc->lenData - 1];
	 } else if (dtime <= mysrc->indData[0]) {
	    value = mysrc->depData[0];
	 } else {
            if (RGST_QUERY_OBJECT_ATTR(name, "QuadInterp")) {
            } else {
             } 
         } 
         for (i = 0; i < len; i++) {
            double de = dedt[ndx[i]] * (value - t[ndx[i]]);
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += de * weight[ndx[i]];
            }
            e[ndx[i]] += de;
            t[ndx[i]]  = value;
         }
      } else if (mysrc->mode == _SourceTable_) {
         if (len > 0) {
            double *value = MALLOT(double, len);
            SourceNew_table (mysrc, value, dtime, domain);
            for (i = 0; i < len; i++) {
               double de = dedt[ndx[i]] * (value[i] - t[ndx[i]]);
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += de * weight[ndx[i]];
               }
               e[ndx[i]] += de;
               t[ndx[i]]  = value[i];
            }
            FREEMEM(value);
         }
      } 
      srclist = srclist->next;
   }
}
void SourceNew_energyrate( double *dele, double *weight, char *mysrcname, 
                           double dtime, double dterate,  Domain_t *domain, 
                           SourceEditMode_t ifedit)
{
   int i;
   double etime = dtime + 0.5 * dterate;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, mysrcname);
   while (srclist != NULL) {
      int  mynspec       = 0;
      int *speclist      = NULL;
      double *frac       = NULL;
      double *e          = NULL;
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      if (len > 0) {
         e    = MALLOT(double, len);
         frac = MALLOT(double, len);
         for (i = 0; i < len; i++) {
            frac[i] = 1.0;
            e[i]    = 0.0;
         }
         if ((mysrc->region > 0) && (ifdynspec > 0)) {
            speclist = MALLOT(int, reg[mysrc->region].nspec);
            mynspec  = Species_getlist(speclist, mysrc->name, 
	                               reg[mysrc->region].species, 
                                       reg[mysrc->region].nspec); 
         }
         if (mynspec > 0) {
            for (i = 0; i < len; i++) {
               int j;
               frac[i] = 0.;
               for (j = 0; j < mynspec; j++) {
                  frac[i] += domain->specfrac[ndx[i]].mass_frac[speclist[j]];
               }
            }
         }
         if ((mysrc->region > 0) && (ifdynspec > 0)) {
            FREEMEM(speclist);
         }
         if (mysrc->mode == _SourceConstant_) {
            for (i = 0; i < len; i++) {
               double de = mysrc->depData[0] * frac[i];
               de = MAX(0., de);
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += de * weight[ndx[i]];
               }
               e[i] += de;
            }
         } else if (mysrc->mode == _SourceTimeDep_) {
            double value;
            if (etime >= mysrc->indData[mysrc->lenData - 1]) {
	       value = mysrc->depData[mysrc->lenData - 1];
	    } else if (etime <= mysrc->indData[0]) {
	       value = mysrc->depData[0];
	    } else {
               if (RGST_QUERY_OBJECT_ATTR(name, "QuadInterp")) {
               } else {
               } 
            }
            for (i = 0; i < len; i++) {
               double de = value * frac[i];
               de = MAX(0., de);
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += de * weight[ndx[i]];
               }
               e[i] += de;
            }
         } else if (mysrc->mode == _SourceTable_) {
            double *value = MALLOT(double, len);
            SourceNew_table (mysrc, value, etime, domain);
            for (i = 0; i < len; i++) {
               double de = value[i] * frac[i];
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += de * weight[ndx[i]];
               }
               e[i] += de;
            }
            FREEMEM(value);
         }
         if (RGST_QUERY_OBJECT_ATTR(name, "SourceEnergyRateHydro")) {
            for (i = 0; i < len; i++) {
               dele[ndx[i]] += e[i] * dterate;
            }
         } else {
            if (iftmode == 1) {
               for (i = 0; i < len; i++) {
                   domain->ematsrc[ndx[i]] += e[i] * dterate;               }
            } else if (iftion == 1) {
               double *tmat = domain->tmat;
               for (i = 0; i < len; i++) {
                  double fraction;
                  double etmp = e[i] * dterate;
                  fraction = tmat[ndx[i]] / ( tmat[ndx[i]] + tsplit ) ;
                  fraction = MIN (fraction, 1.0 );
                  fraction = MAX (fraction, 0.0 );
                  domain->ematsrc[ndx[i]] += (1.0 - fraction ) * etmp;
                  domain->eionsrc[ndx[i]] +=        fraction   * etmp;
               }
            } 
         } 
         FREEMEM(e);
         FREEMEM(frac);
      } 
      srclist = srclist->next;
   }
}
void SourceNew_radtemperature( double *phi, double *t, double *weight, 
                               char *mysrcname, double dtime, Domain_t *domain,
                               SourceEditMode_t ifedit)
{
   int i;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, mysrcname);
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      if (mysrc->mode == _SourceConstant_) {
         double dt4 = mysrc->depData[0] * mysrc->depData[0];
	 dt4 = dt4 * dt4;
         for (i = 0; i < len; i++) {
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += (dt4 - phi[ndx[i]]) * weight[ndx[i]];
            }
            phi[ndx[i]] = dt4;
            t[ndx[i]]   = mysrc->depData[0];
         }
      } else if (mysrc->mode == _SourceTimeDep_) {
         double value, dt4;
	 if (dtime >= mysrc->indData[mysrc->lenData - 1]) {
	    value = mysrc->depData[mysrc->lenData - 1];
	 } else if (dtime <= mysrc->indData[0]) {
	    value = mysrc->depData[0];
	 } else {
            if (RGST_QUERY_OBJECT_ATTR(name, "QuadInterp")) {
            } else {
            } 
         } 
         dt4 = value * value;
	 dt4 = dt4 * dt4;
         for (i = 0; i < len; i++) {
            if (ifedit == _SourceEdit_) {
               mysrc->dSourceEdit += (dt4 - phi[ndx[i]]) * weight[ndx[i]];
            }
            phi[ndx[i]] = dt4;
            t[ndx[i]]   = value;
         }
      } else if (mysrc->mode == _SourceTable_) {
         if (len > 0) {
            double *value = MALLOT(double, len);
            SourceNew_table (mysrc, value, dtime, domain);
            for (i = 0; i < len; i++) {
               double dt4 = value[i] * value[i];
	       dt4 = dt4 * dt4;
               if (ifedit == _SourceEdit_) {
                  mysrc->dSourceEdit += (dt4 - phi[ndx[i]]) * weight[ndx[i]];
               }
               phi[ndx[i]] = dt4;
               t[ndx[i]]   = value[i];
            }
            FREEMEM(value);
         }
      } 
      srclist = srclist->next;
   }
}
void SourceNew_table (SourceNew_t *mysrc, double *value, double dtime, 
                      Domain_t *domain) {
   double *x;    
   double *y;    
   double *z;    
   double *r;    
   double *t;    
   double *theta;    
   double *ind[3];
   int i;
   int ifrt;
   int len;
   int *myndx = NULL;
   if (mysrc->region > 0) {
      int *ndx = domain->rndx[mysrc->region];
      len      = domain->rlen[mysrc->region];
      if (len > 0) myndx = MALLOT(int,len);
      for (i = 0; i < len; i++) {
         myndx[i] = ndx[i];
         if (ndx[i] >= domain->nnalls) {
            myndx[i] = domain->grdpnt[ndx[i] - domain->nnalls];
         }
      }
   } else {
      len   = mysrc->len;
      myndx = mysrc->ndx;
   }
   x = MALLOT(double, len);
   y = MALLOT(double, len);
   if (ndims == 3) z = MALLOT(double, len);
   r = MALLOT(double, len);
   t = MALLOT(double, len);
   theta = MALLOT(double, len);
   ind[0] = NULL;
   ind[1] = NULL;
   ind[2] = NULL;
   ifrt = Transform_setptr(mysrc->indField1, mysrc->indField2, mysrc->indField3, 
                           ind, x, y, z, r, theta, NULL, t);
   Transform_getcoord(x, y, z, r, theta, NULL, myndx, len, mysrc->centering, ifrt, 
                      domain, NULL);
   for (i = 0; i < len; i++) t[i] = dtime;
   FREEMEM(x);
   FREEMEM(y);
   if (ndims == 3) FREEMEM(z);
   FREEMEM(r);
   FREEMEM(t);
   FREEMEM(theta);
   if (mysrc->region > 0) FREEMEM(myndx);
}
int SourceNew_setup_attrs(void) {
  char *me = "SourceNew_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("SourceNew_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("SourceNew_free", SourceNew_free, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"SourceNew_free", "Function_Free");
    rgst_add_attr(A_OBJECT,"SourceNew_free", "Function_DomainFree");
    rgst_add_attr(A_OBJECT,"SourceNew_free", "Function_ReGenDomainFree");

#ifdef SILO
    inst_c("SourceNew_wtsilo", SourceNew_wtsilo, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"SourceNew_wtsilo", "Function_WriteSilo");
    inst_c("SourceNew_rdsilo", SourceNew_rdsilo, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"SourceNew_rdsilo", "Function_ReadSilo");
#endif
    inst_c("SourceNew_gen", SourceNew_gen, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"SourceNew_gen", "Function_Gen");
    rgst_add_attr(A_OBJECT,"SourceNew_gen", "Function_ReGen");
    inst_c("SourceNew_init", SourceNew_init, zargse, 0, symtab);
    inst_c("src2", SourceNew_input, zargse, 0, symtab);
    inst_c("showsrc", SourceNew_showsrc, zargse, 0, symtab);
    inst_c("srcoff", SourceNew_srcoff, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
void SourceNew_packedit( double *buffer, int *len ) 
{
   int iblk;
   int mylen = *len;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      char *name            = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,NULL);
      buffer[mylen] = mysrc->dSourceEdit;
      mylen++;
      srclist = srclist->next;
   }
   *len = mylen;
}
void SourceNew_unpackedit( double *buffer, int *len ) 
{
   int iblk;
   int mylen = *len;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      char *name            = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,NULL);
      mysrc->dSourceEdit  = buffer[mylen];
      mylen++;
      srclist = srclist->next;
   }
   *len = mylen;
}
void SourceNew_sumedits( void ) 
{
   int iblk;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      char *name            = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,NULL);
      mysrc->dSourceEdit  = 0.;
      for (iblk = 0; iblk < nblk; iblk++) {
         SourceNew_t *dsrc     = SourceNew_find(name,domains[iblk].hash);
	 if (dsrc != NULL) {
            mysrc->dSourceEdit  += dsrc->dSourceEdit;
	 }
      }
      srclist = srclist->next;
   }
}
void SourceNew_getedits( double *mysrc_mass, double *mysrc_e, double *mysrc_xmom,
                      double *mysrc_ymom, double *mysrc_zmom) 
{
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      char *name            = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc      = SourceNew_find(name,NULL);
      mysrc->SourceEdit  += mysrc->dSourceEdit;
      if (RGST_QUERY_OBJECT_ATTR(name, "SourceMassEdit")) {
         *mysrc_mass += mysrc->SourceEdit;
      } else if (RGST_QUERY_OBJECT_ATTR(name, "SourceEnergyEdit")) {
         *mysrc_e += mysrc->SourceEdit;
      } else if (RGST_QUERY_OBJECT_ATTR(name, "SourceXmomEdit")) {
         *mysrc_xmom += mysrc->SourceEdit;
      } else if (RGST_QUERY_OBJECT_ATTR(name, "SourceYmomEdit")) {
         *mysrc_ymom += mysrc->SourceEdit;
      } else if (RGST_QUERY_OBJECT_ATTR(name, "SourceZmomEdit")) {
         *mysrc_zmom += mysrc->SourceEdit;
      } 
      srclist = srclist->next;
   }
}
int SourceNew_showsrc( void ) {
   char *me = "SourceNew_showsrc";
   char *name;
   char msg[MAXLINE];
   SourceNew_t *src;
   RGST_AttributeElem_t *srclist;
   srclist = rgst_list_attr(A_OBJECT, "SourceList");
   while (srclist != NULL) {
      name = ATTR_GET_OBJECT_NAME(srclist);
      src  = SourceNew_find(name, NULL);
      sprintf(msg,"src(%s) = %s",src->name, src->type);
      ctlmsg(msg);
      srclist = srclist->next;
   }
   return(0);
}
int SourceNew_srcoff( void ) {
   char *me = "SourceNew_srcoff";
   char *name;
   char msg[MAXLINE];
   char myname[MAXLINE];
   char ndxname[MAXLINE];
   char op[MAXLINE];
   SourceNew_t *src;
   int iblk;
   geta(op);
   sprintf(myname, "SourceNew_%s",op);
   src = SourceNew_find(myname,NULL);
   if (src == NULL) {
      sprintf(msg,"SourceNew region %s cannot be found.",op);
      return(-1);
   }
   SourceNew_release(src);
   rgst_del(myname);
   for (iblk = 0; iblk < nblk; iblk++) {
      src = SourceNew_find(myname,domains[iblk].hash);
      if (src != NULL) {
         sprintf(ndxname,"NL_%s",src->name);
         NodeList_del(ndxname);
         hash_del2(myname, "SourceNew_t", domains[iblk].hash);
         SourceNew_release(src);
      }
   }
   return(0);
}
