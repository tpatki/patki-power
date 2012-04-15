#include "irs.h"
#include "irsreg.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "AEStackElm.h"
#include "NodeList.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "UserList.h"
static void region_op( int ir );
int region_edit( void ) 
{
   char *me = "region_edit";	 
   char msg[MAXLINE],label[MAXLINE];
   char op[MAXLINE];
   char name[MAXLINE];
   char fieldname[MAXLINE];
   int is, ir, ir_min, ir_max;
   int gotone;	 
   int error;	 
   int regobj_size;
   int *ivalue;
   int ival;
   double *dvalue;
   double dval;
   NodeWindow_t            *ndxin;
   RGST_AttributeElem_t  *regobjs;
   RGST_AttributeElem_t  *regobjs_ptr;
   RGST_StructTypeDef_t *td;
   RGST_Field_t          *regfield;
   HashElm_t       *hash_elm = NULL;
   ProblemArray_t *prb;
   void *fieldptr;
   error = 0;
   ndxin = NULL;
   sprintf(name,"reg");
   error = NodeWindow_read(name,&ndxin);
   if (error != 0) return(-1);
   ir_min = MIN(ndxin->in[0][0], ndxin->in[0][1]);
   ir_max = MAX(ndxin->in[0][0], ndxin->in[0][1]);
   if (ndxin->rank > 1) {
      error = -1;
      sprintf(msg,"Reg command cannot take multi-dimensional indices.");
   }
   if (ir_min < 0) {
      error = -1;
      sprintf(msg,"Regional index %i is out of range in reg command.",ir_min);
   }
   if (ir_max > nreg) {
      error = -1;
      sprintf(msg,"Regional index %i is out of range in reg command.",ir_max);
   }
   if (error != 0) {
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   if (lfchk()) {
      sprintf(msg,"Reg command expects a period followed by regional field.");
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   if (ps[0] != '.') {
      sprintf(msg,"Reg command expects a period followed by regional field.");
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   ps++;
   geta(name);
   sprintf(msg,"reg%s",name);
   prb = ProblemArray_find(msg, NULL);
   if (prb != NULL) {
      if (prb->type == R_INT) {
         ivalue = (int *) prb->ptr;
         for (ir = ir_min; ir <= ir_max; ir++) {
            sprintf(label,"reg(%i).%s",ir,name);
            ctloutput(me,label,R_INT,ivalue[ir]);
         }
      } else if (prb->type == R_DOUBLE) {
         dvalue = (double *) prb->ptr;
         for (ir = ir_min; ir <= ir_max; ir++) {
            sprintf(label,"reg(%i).%s",ir,name);
            ctloutput(me,label,R_DOUBLE,dvalue[ir]);
         }
      } 
      NodeWindow_free(ndxin);
      return(0);
   }
   regobjs = rgst_list_attr(A_OBJECT, "RegionalEditObject");
   regobjs_ptr = regobjs;
   gotone = 0;
   while (regobjs_ptr != NULL) {
      fieldptr = rgst_get_field_addr(regobjs_ptr->rgst_obj,
                                     regobjs_ptr->rgst_obj->usertype,
                                     name,
                                     &regfield);
      if (fieldptr != NULL) {
	 hash_elm  = hash_lookup_elm( regobjs_ptr->rgst_obj->usertype,
	                rgst_types_hash_tbl);
	 td = (RGST_StructTypeDef_t *)hash_elm->obj;
	 regobj_size = td->struct_size;
         gotone = 1;
         break;
      }
      regobjs_ptr = regobjs_ptr->next;
   }
   if (gotone == 0) {
      sprintf(msg,"Cannot find regional object %s.",name);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   memset(label,'\0',MAXLINE);
   if (regfield->type == R_DOUBLE) {
      for (ir = ir_min; ir <= ir_max; ir++) {
         dvalue = (double *) ((*(unsigned char **)regobjs_ptr->rgst_obj->obj) + 
	                       ir * regobj_size + 
                              regfield->offset);
         sprintf(label,"reg(%i).%s",ir,name);
         ctloutput(me,label,R_DOUBLE,*dvalue);
      }
   } else if (regfield->type == R_INT) {
      for (ir = ir_min; ir <= ir_max; ir++) {
         ivalue = (int *)  ((*(unsigned char **)regobjs_ptr->rgst_obj->obj) + 
	                     ir * regobj_size + 
                             regfield->offset);
         sprintf(label,"reg(%i).%s",ir,name);
         ctloutput(me,label,R_INT,*ivalue);
      }
   } else if (!strcmp(name,"species")) {
      error = UserList_parse("RegionCommand");
      if (error != 0) {
         sprintf(msg,"Error in parsing the species list in reg command.");
         ctlwarning(me,msg);
         NodeWindow_free(ndxin);
         return(-1);
      }
      geta(op);
      if (op[0] != '.') {
         sprintf(msg,"Species command expects a period followed by species field.");
         ctlwarning(me,msg);
         NodeWindow_free(ndxin);
         return(-1);
      }
      strcpy(fieldname,&op[1]);
      for (ir = ir_min; ir <= ir_max; ir++) {
	 UserList_t *ul = UserList_find("RegionCommand");
         gotone = 0;
         while (ul != NULL) {
            for (is = 0; is < reg[ir].nspec; is++) {
               if (!strcmp(ul->name,reg[ir].species[is].name)) break;
            }
            if (is < reg[ir].nspec) {
               gotone = 1;
               fieldptr = rgst_get_field_addr(&reg[ir].species[is],
                                     "Species_t", fieldname, &regfield);
               if (fieldptr == NULL) {
                  sprintf(msg,"Cannot access species field %s",fieldname);
                  ctlwarning(me,msg);
                  NodeWindow_free(ndxin);
                  return(-1);
               }
               if (regfield->type == R_INT) {
                  ival = *((int *) fieldptr);
               } else if (regfield->type == R_DOUBLE) {
                  dval = *((double *) fieldptr);
               } 
            } else {
               sprintf(msg,"Cannot find species named %s",name);	 
               ctlwarning(me,msg);
               NodeWindow_free(ndxin);
               UserList_del("RegionCommand");
               return(-1);
            } 
            if (gotone) {
               sprintf(label,"reg(%i).species(%s).%s",ir,ul->name,fieldname);
               if (regfield->type == R_INT)    {
                 ctloutput(me,label,R_INT,ival);
               } else if (regfield->type == R_DOUBLE) {
                 ctloutput(me,label,R_DOUBLE,dval);
               }
            }
            gotone = 0;
            ul = ul->next;
         } 
         UserList_del("RegionCommand");
      }
   } else {
      sprintf(msg,"Cannot access value for field %s",name);	 
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   } 
   NodeWindow_free(ndxin);
   return(0);
}
int  region_input( void )
{
   char *me = "region_input";
   char msg[128];
   int error, cflag, ir ;
   error = 0 ;
   ir = geti(&cflag) ;
   current_region = ir ;
   current_eos    = -1 ;
   nreg = MAX( nreg, ir ) ;
   nregplus1 = nreg + 1;
   if ( nreg >= nregx ) {
      error = 1 ;
      sprintf(msg,"%d regions exceeds maximum, set nregx to %i",nreg,nreg+1) ;
      ctlwarning(me,msg);
   }
   if ( error == 0 ) {
      region_op(ir) ;
   }
   return(error) ;
}
int  region_opin( void )
{
   char *me = "region_opin";
   char msg[128];
   int error, ir, cflag ;
   error = 0 ;
   ir = geti(&cflag) ;
   if ((ir < 1) || (ir > nreg)) {
      error = 1 ;
      sprintf(msg,"reg %d undefined in regop",ir) ;
      ctlwarning(me,msg);
   } else {
      region_op(ir) ;
   }
   return(error) ;
}
static void region_op( int ir )
{
   char *me = "region_op";
   char msg[MAXLINE];
   char regop[MAXWORD], newcolr[MAXWORD] ;
   int i ;
   int cflag ;
   int opfg ;
   int ispec;
   int eosnum;
   int eosfm;
   opfg  =  1 ;
   ispec = -1;
   while ( opfg == 1 ) {
      peekc(regop) ;
      if        ( !strcmp(regop,"eos") ) {
         geta(regop) ;
         (void) eosin() ;
      } else if ( !strcmp(regop,"opacity") ) {
         geta(regop) ;
         (void) opacin() ;
      } else if ( !strcmp(regop,"pminmd") ) {
         geta(regop) ;
         reg[ir].pminmd = geti(&cflag) ;
      } else if ( !strcmp(regop,"burn") ) {
         geta(regop) ;
         reg[ir].burn = geti(&cflag) ;
      } else if ( !strcmp(regop,"str") ) {
         geta(regop) ;
         reg[ir].str = geti(&cflag) ;
      } else if ( !strcmp(regop,"ioneq") ) {
         geta(regop) ;
         reg[ir].ioneq = geti(&cflag) ;
      } else if ( !strcmp(regop,"color") ) {
         geta(regop) ;
         geta(newcolr) ;
      } else if ( !strcmp(regop,"damage") ) {
         geta(regop) ;
         reg[ir].damage = geti(&cflag) ;
      } else if ( !strcmp(regop,"por0") ) {
         geta(regop) ;
         reg[ir].por0 = getf(&cflag) ;
      } else if ( !strcmp(regop,"porfail") ) {
         geta(regop) ;
         reg[ir].porfail = getf(&cflag) ;
      } else if ( !strcmp(regop,"etahold") ) {
         geta(regop) ;
         reg[ir].etahold = getf(&cflag) ;
      } else if ( !strcmp(regop,"rxwgt") ) {
         geta(regop) ;
         reg[ir].rxwgt = getf(&cflag) ;
      } else if ( !strcmp(regop,"xray") ) {
         geta(regop) ;
         reg[ir].xray = getf(&cflag) ;
      } else if ( !strcmp(regop,"bhe") ) {
         geta(regop) ;
         reg[ir].bhe = getf(&cflag) ;
      } else if ( !strcmp(regop,"detvel") ) {
         geta(regop) ;
         reg[ir].detvel = getf(&cflag) ;
      } else if ( !strcmp(regop,"plklmt") ) {
         geta(regop) ;
         reg[ir].plklmt = getf(&cflag) ;
      } else if ( !strcmp(regop,"mfplmt") ) {
         geta(regop) ;
         reg[ir].mfplmt = getf(&cflag) ;
      } else if ( !strcmp(regop,"dmin") ) {
         geta(regop) ;
         reg[ir].dmin = getf(&cflag) ;
      } else if ( !strcmp(regop,"emin") ) {
         geta(regop) ;
         reg[ir].emin = getf(&cflag) ;
      } else if ( !strcmp(regop,"pmin") ) {
         geta(regop) ;
         reg[ir].pmin = getf(&cflag) ;
      } else if ( !strcmp(regop,"qlin") ) {
         geta(regop) ;
         reg[ir].qlin = getf(&cflag) ;
      } else if ( !strcmp(regop,"qquad") ) {
         geta(regop) ;
         reg[ir].qquad = getf(&cflag) ;
      } else if ( !strcmp(regop,"hgfrac") ) {
         geta(regop) ;
         reg[ir].hgfrac = getf(&cflag) ;
      } else if ( !strcmp(regop,"visca") ) {
         geta(regop) ;
         reg[ir].visca = getf(&cflag) ;
      } else if ( !strcmp(regop,"viscb") ) {
         geta(regop) ;
         reg[ir].viscb = getf(&cflag) ;
      } else if ( !strcmp(regop,"viscc") ) {
         geta(regop) ;
         reg[ir].viscc = getf(&cflag) ;
      } else if ( !strcmp(regop,"viscn") ) {
         geta(regop) ;
         reg[ir].viscn = getf(&cflag) ;
      } else if ( !strcmp(regop,"cv") ) {
         geta(regop) ;
         reg[ir].visccv = getf(&cflag) ;
      } else if ( !strcmp(regop,"schmidt") ) {
         geta(regop) ;
         reg[ir].schmidt = getf(&cflag) ;
      } else if ( !strcmp(regop,"prandtl") ) {
         geta(regop) ;
         reg[ir].prandtl = getf(&cflag) ;
      } else if ( !strcmp(regop,"aturb") ) {
         geta(regop) ;
         reg[ir].aturb = getf(&cflag) ;
      } else if ( !strcmp(regop,"bturb") ) {
         geta(regop) ;
         reg[ir].bturb = getf(&cflag) ;
      } else if ( !strcmp(regop,"cturb") ) {
         geta(regop) ;
         reg[ir].cturb = getf(&cflag) ;
      } else if ( !strcmp(regop,"dturb") ) {
         geta(regop) ;
         reg[ir].dturb = getf(&cflag) ;
      } else if ( !strcmp(regop,"redo") ) {
         geta(regop) ;
         current_region = ir ;
         current_eos    = -1 ;
         Region_destruct(&reg[ir]);
         Region_init(&reg[ir]);
      } else {
         opfg = 0 ;
      }
   }
}
