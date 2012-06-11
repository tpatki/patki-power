#include "irs.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsobjects.h"
#include "irsparm.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "BoundaryCondition.h"
#include "Boundary.h"
#include "Command.h"
#include "Domain.h"
#include "Hash.h"
#include "ProblemArray.h"
#include "FunctionTimer.h"
#include "Rgst.h"
#include "SpeciesFraction.h"
#include "TimeStepControl.h"
static void domain_null_fields(Domain_t *domain) ;
static void domain_TdiffOrient(char *name, int orientation);
void domain_attr(void) {
   int i;
   ProblemArray_add("den",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"den","Zonal");
   rgst_add_attr(A_OBJECT,"den","Mixed");
   rgst_add_attr(A_OBJECT,"den","OnDump");
   rgst_add_attr(A_OBJECT,"den","ScalAdvVar");
   rgst_add_attr(A_OBJECT,"den","MixedAdv");
   rgst_add_attr(A_OBJECT,"den","PermVar");
   rgst_add_attr(A_OBJECT,"den","DomainVar");
   rgst_add_attr(A_OBJECT,"den","RBNDCOM2");
   rgst_add_attr(A_OBJECT,"den","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","den","ValidField");
   ProblemArray_add("emat",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"emat","Zonal");
   rgst_add_attr(A_OBJECT,"emat","Mixed");
   rgst_add_attr(A_OBJECT,"emat","OnDump");
   rgst_add_attr(A_OBJECT,"emat","ScalAdvVar");
   rgst_add_attr(A_OBJECT,"emat","MultDen");
   rgst_add_attr(A_OBJECT,"emat","MixedAdv");
   rgst_add_attr(A_OBJECT,"emat","PermVar");
   rgst_add_attr(A_OBJECT,"emat","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","emat","ValidField");
   ProblemArray_add("x",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"x","Nodal");
   rgst_add_attr(A_OBJECT,"x","SlideData");
   rgst_add_attr(A_OBJECT,"x","PermVar");
   rgst_add_attr(A_OBJECT,"x","DomainVar");
   rgst_add_attr(A_OBJECT,"x","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","x","ValidField");
   ProblemArray_add("xdot",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"xdot","Nodal");
   rgst_add_attr(A_OBJECT,"xdot","OnDump");
   rgst_add_attr(A_OBJECT,"xdot","SlideData");
   rgst_add_attr(A_OBJECT,"xdot","PermVar");
   rgst_add_attr(A_OBJECT,"xdot","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","xdot","ValidField");
   ProblemArray_add("y",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"y","Nodal");
   rgst_add_attr(A_OBJECT,"y","SlideData");
   rgst_add_attr(A_OBJECT,"y","PermVar");
   rgst_add_attr(A_OBJECT,"y","DomainVar");
   rgst_add_attr(A_OBJECT,"y","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","y","ValidField");
   ProblemArray_add("ydot",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"ydot","Nodal");
   rgst_add_attr(A_OBJECT,"ydot","OnDump");
   rgst_add_attr(A_OBJECT,"ydot","SlideData");
   rgst_add_attr(A_OBJECT,"ydot","PermVar");
   rgst_add_attr(A_OBJECT,"ydot","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","ydot","ValidField");
   if (ndims == 3) {
      ProblemArray_add("z",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"z","Nodal");
      rgst_add_attr(A_OBJECT,"z","SlideData");
      rgst_add_attr(A_OBJECT,"z","PermVar");
      rgst_add_attr(A_OBJECT,"z","DomainVar");
      rgst_add_attr(A_OBJECT,"z","Only3D");
      rgst_add_attr(A_OBJECT,"z","RBNDCOM3");
      ProblemArray_add("zdot",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"zdot","Nodal");
      rgst_add_attr(A_OBJECT,"zdot","OnDump");
      rgst_add_attr(A_OBJECT,"zdot","SlideData");
      rgst_add_attr(A_OBJECT,"zdot","PermVar");
      rgst_add_attr(A_OBJECT,"zdot","DomainVar");
      rgst_add_attr(A_OBJECT,"zdot","Only3D");
   }
   rgst_add_attr(A_FIELD,"Domain_t","z","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","zdot","ValidField");

   ProblemArray_add("nmass",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"nmass","Nodal");
   rgst_add_attr(A_OBJECT,"nmass","SlideData");
   rgst_add_attr(A_OBJECT,"nmass","PermVar");
   rgst_add_attr(A_OBJECT,"nmass","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","nmass","ValidField");
   if (ndims == 2) {
      ProblemArray_add("area",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"area","Zonal");
      rgst_add_attr(A_OBJECT,"area","PermVar");
      rgst_add_attr(A_OBJECT,"area","DomainVar");
      rgst_add_attr(A_OBJECT,"area","Only2D");
   }
   rgst_add_attr(A_FIELD,"Domain_t","area","ValidField");
   ProblemArray_add("vol",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"vol","Zonal");
   rgst_add_attr(A_OBJECT,"vol","Mixed");
   rgst_add_attr(A_OBJECT,"vol","PermVar");
   rgst_add_attr(A_OBJECT,"vol","DomainVar");
   rgst_add_attr(A_OBJECT,"vol","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","vol","ValidField");
   ProblemArray_add("invLengthSqr",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"invLengthSqr","Zonal");
   rgst_add_attr(A_OBJECT,"invLengthSqr","Mixed");
   rgst_add_attr(A_OBJECT,"invLengthSqr","PermVar");
   rgst_add_attr(A_OBJECT,"invLengthSqr","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","invLengthSqr","ValidField");
   ProblemArray_add("tmat",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"tmat","Zonal");
   rgst_add_attr(A_OBJECT,"tmat","Mixed");
   rgst_add_attr(A_OBJECT,"tmat","PermVar");
   rgst_add_attr(A_OBJECT,"tmat","OnDump");
   rgst_add_attr(A_OBJECT,"tmat","DomainVar");
   rgst_add_attr(A_OBJECT,"tmat","ScalAdvVar");
   rgst_add_attr(A_OBJECT,"tmat","MixedAdv");
   rgst_add_attr(A_OBJECT,"tmat","RBNDCOM2");
   rgst_add_attr(A_OBJECT,"tmat","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","tmat","ValidField");
   ProblemArray_add("dedt",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"dedt","Zonal");
   rgst_add_attr(A_OBJECT,"dedt","Mixed");
   rgst_add_attr(A_OBJECT,"dedt","OnDump");
   rgst_add_attr(A_OBJECT,"dedt","MultDen");
   rgst_add_attr(A_OBJECT,"dedt","PermVar");
   rgst_add_attr(A_OBJECT,"dedt","DomainVar");
   rgst_add_attr(A_OBJECT,"dedt","ScalAdvVar");
   rgst_add_attr(A_OBJECT,"dedt","MixedAdv");
   rgst_add_attr(A_FIELD,"Domain_t","dedt","ValidField");
   ProblemArray_add("node",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"node","Nodal");
   rgst_add_attr(A_OBJECT,"node","SlideData");
   rgst_add_attr(A_OBJECT,"node","PermVar");
   rgst_add_attr(A_OBJECT,"node","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","node","ValidField");
   ProblemArray_add("p",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"p","Zonal");
   rgst_add_attr(A_OBJECT,"p","Mixed");
   rgst_add_attr(A_OBJECT,"p","OnDump");
   rgst_add_attr(A_OBJECT,"p","PermVar");
   rgst_add_attr(A_OBJECT,"p","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","p","ValidField");


   ProblemArray_add("cs2",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"cs2","Zonal");
   rgst_add_attr(A_OBJECT,"cs2","Mixed");
   rgst_add_attr(A_OBJECT,"cs2","PermVar");
   rgst_add_attr(A_OBJECT,"cs2","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","cs2","ValidField");
   ProblemArray_add("zmass",NULL,0,R_DOUBLE,NULL);
   rgst_add_attr(A_OBJECT,"zmass","Zonal");
   rgst_add_attr(A_OBJECT,"zmass","Mixed");
   rgst_add_attr(A_OBJECT,"zmass","PermVar");
   rgst_add_attr(A_OBJECT,"zmass","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","zmass","ValidField");
   ProblemArray_add("ireg",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"ireg","Zonal");
   rgst_add_attr(A_OBJECT,"ireg","Mixed");
   rgst_add_attr(A_OBJECT,"ireg","PermVar");
   rgst_add_attr(A_OBJECT,"ireg","DomainVar");
   rgst_add_attr(A_OBJECT,"ireg","RBNDCOM3");
   rgst_add_attr(A_FIELD,"Domain_t","ireg","ValidField");
   ProblemArray_add("nmatlst",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"nmatlst","Zonal");
   rgst_add_attr(A_OBJECT,"nmatlst","Mixed");
   rgst_add_attr(A_OBJECT,"nmatlst","PermVar");
   rgst_add_attr(A_OBJECT,"nmatlst","DomainVar");
   rgst_add_attr(A_FIELD,"Domain_t","nmatlst","ValidField");

   if (iftion) {
      ProblemArray_add("tion",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"tion","Zonal");
      rgst_add_attr(A_OBJECT,"tion","Mixed");
      rgst_add_attr(A_OBJECT,"tion","OnDump");
      rgst_add_attr(A_OBJECT,"tion","ScalAdvVar");
      rgst_add_attr(A_OBJECT,"tion","MixedAdv");
      rgst_add_attr(A_OBJECT,"tion","PermVar");
      rgst_add_attr(A_OBJECT,"tion","DomainVar");
      ProblemArray_add("pion",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"pion","Zonal");
      rgst_add_attr(A_OBJECT,"pion","Mixed");
      rgst_add_attr(A_OBJECT,"pion","OnDump");
      rgst_add_attr(A_OBJECT,"pion","PermVar");
      rgst_add_attr(A_OBJECT,"pion","DomainVar");
      ProblemArray_add("eion",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"eion","Zonal");
      rgst_add_attr(A_OBJECT,"eion","Mixed");
      rgst_add_attr(A_OBJECT,"eion","OnDump");
      rgst_add_attr(A_OBJECT,"eion","ScalAdvVar");
      rgst_add_attr(A_OBJECT,"eion","MultDen");
      rgst_add_attr(A_OBJECT,"eion","MixedAdv");
      rgst_add_attr(A_OBJECT,"eion","PermVar");
      rgst_add_attr(A_OBJECT,"eion","DomainVar");
      ProblemArray_add("deidt",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"deidt","Zonal");
      rgst_add_attr(A_OBJECT,"deidt","Mixed");
      rgst_add_attr(A_OBJECT,"deidt","OnDump");
      rgst_add_attr(A_OBJECT,"deidt","PermVar");
      rgst_add_attr(A_OBJECT,"deidt","DomainVar");
      rgst_add_attr(A_OBJECT,"deidt","ScalAdvVar");
      rgst_add_attr(A_OBJECT,"deidt","MultDen");
      rgst_add_attr(A_OBJECT,"deidt","MixedAdv");
      ProblemArray_add("e_cold",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"e_cold","Zonal");
      rgst_add_attr(A_OBJECT,"e_cold","Mixed");
      rgst_add_attr(A_OBJECT,"e_cold","OnDump");
      rgst_add_attr(A_OBJECT,"e_cold","ScalAdvVar");
      rgst_add_attr(A_OBJECT,"e_cold","MultDen");
      rgst_add_attr(A_OBJECT,"e_cold","MixedAdv");
      rgst_add_attr(A_OBJECT,"e_cold","PermVar");
      rgst_add_attr(A_OBJECT,"e_cold","DomainVar");
      ProblemArray_add("p_cold",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"p_cold","Zonal");
      rgst_add_attr(A_OBJECT,"p_cold","Mixed");
      rgst_add_attr(A_OBJECT,"p_cold","OnDump");
      rgst_add_attr(A_OBJECT,"p_cold","PermVar");
      rgst_add_attr(A_OBJECT,"p_cold","DomainVar");
   }
   rgst_add_attr(A_FIELD,"Domain_t","tion","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","pion","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","eion","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","deidt","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","e_cold","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","p_cold","ValidField");
   if ( kapsav == 1 ) {
      ProblemArray_add("kros",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"kros","Zonal");
      rgst_add_attr(A_OBJECT,"kros","Mixed");
      rgst_add_attr(A_OBJECT,"kros","OnDump");
      rgst_add_attr(A_OBJECT,"kros","PermVar");
      rgst_add_attr(A_OBJECT,"kros","DomainVar");
      ProblemArray_add("kplnk",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"kplnk","Zonal");
      rgst_add_attr(A_OBJECT,"kplnk","Mixed");
      rgst_add_attr(A_OBJECT,"kplnk","OnDump");
      rgst_add_attr(A_OBJECT,"kplnk","PermVar");
      rgst_add_attr(A_OBJECT,"kplnk","DomainVar");
   }
   rgst_add_attr(A_FIELD,"Domain_t","kros","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","kplnk","ValidField");
   if ( ioneq == 1 ) {
      ProblemArray_add("zstar",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"zstar","Zonal");
      rgst_add_attr(A_OBJECT,"zstar","Mixed");
      rgst_add_attr(A_OBJECT,"zstar","OnDump");
      rgst_add_attr(A_OBJECT,"zstar","ScalAdvVar");
      rgst_add_attr(A_OBJECT,"zstar","MultDen");
      rgst_add_attr(A_OBJECT,"zstar","MixedAdv");
      rgst_add_attr(A_OBJECT,"zstar","PermVar");
      rgst_add_attr(A_OBJECT,"zstar","DomainVar");
   }
   rgst_add_attr(A_FIELD,"Domain_t","zstar","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","tke","ValidField");

   rgst_add_attr(A_FIELD,"Domain_t","omegasq","ValidField");

   rgst_add_attr(A_FIELD,"Domain_t","work1","ValidField");

   rgst_add_attr(A_FIELD,"Domain_t","work1","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","work2","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","work3","ValidField");

   rgst_add_attr(A_FIELD,"Domain_t","work4","ValidField");

   if ( ngroup > 0 ) {
      ProblemArray_add("trad",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"trad","Zonal");
      rgst_add_attr(A_OBJECT,"trad","Mixed");
      rgst_add_attr(A_OBJECT,"trad","OnDump");
      rgst_add_attr(A_OBJECT,"trad","PermVar");
      rgst_add_attr(A_OBJECT,"trad","DomainVar");
      rgst_add_attr(A_OBJECT,"trad","RBNDCOM2");
      rgst_add_attr(A_OBJECT,"trad","RBNDCOM3");
      ProblemArray_add("erad",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"erad","Zonal");
      rgst_add_attr(A_OBJECT,"erad","Mixed");
      rgst_add_attr(A_OBJECT,"erad","OnDump");
      rgst_add_attr(A_OBJECT,"erad","PermVar");
      rgst_add_attr(A_OBJECT,"erad","DomainVar");
      ProblemArray_add("phi",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"phi","Zonal");
      rgst_add_attr(A_OBJECT,"phi","RBNDCOM3");
      rgst_add_attr(A_OBJECT,"phi","RBNDCOM1");
      ProblemArray_add("dphi",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"dphi","Zonal");
      rgst_add_attr(A_OBJECT,"dphi","RBNDCOM3");
      rgst_add_attr(A_OBJECT,"dphi","RBNDCOM1");
      ProblemArray_add("adphi",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"adphi","Zonal");
      rgst_add_attr(A_OBJECT,"adphi","RBNDCOM5");
      if (ndims == 3){
	ProblemArray_add("diffCoefU",NULL,0,R_DOUBLE,NULL);
	rgst_add_attr(A_OBJECT,"diffCoefU","Zonal");
	rgst_add_attr(A_OBJECT,"diffCoefU","RBNDCOM4");
	domain_TdiffOrient("diffCoefU", 3);
	ProblemArray_add("diffCoefD",NULL,0,R_DOUBLE,NULL);
	rgst_add_attr(A_OBJECT,"diffCoefD","Zonal");
	rgst_add_attr(A_OBJECT,"diffCoefD","RBNDCOM4");
	domain_TdiffOrient("diffCoefD", -3);
      }
      ProblemArray_add("diffCoefF",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"diffCoefF","Zonal");
      rgst_add_attr(A_OBJECT,"diffCoefF","RBNDCOM4");
      domain_TdiffOrient("diffCoefF", 2);
      ProblemArray_add("diffCoefB",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"diffCoefB","Zonal");
      rgst_add_attr(A_OBJECT,"diffCoefB","RBNDCOM4");
      domain_TdiffOrient("diffCoefB", -2);
      ProblemArray_add("diffCoefR",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"diffCoefR","Zonal");
      rgst_add_attr(A_OBJECT,"diffCoefR","RBNDCOM4");
      domain_TdiffOrient("diffCoefR", -1);
      ProblemArray_add("diffCoefL",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"diffCoefL","Zonal");
      rgst_add_attr(A_OBJECT,"diffCoefL","RBNDCOM4");
      domain_TdiffOrient("diffCoefL", 1);
      ProblemArray_add("flmt",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"flmt","Nodal");
      rgst_add_attr(A_OBJECT,"flmt","RBNDCOM4");
      ProblemArray_add("cellCenterContrib",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"cellCenterContrib","Zonal");
      rgst_add_attr(A_OBJECT,"cellCenterContrib","RBNDCOM6");
      ProblemArray_add("rhsContrib",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"rhsContrib","Zonal");
      rgst_add_attr(A_OBJECT,"rhsContrib","RBNDCOM6");

 {          rgst_add_attr(A_OBJECT,"erad","ScalAdvVar");
      } 
   }
   rgst_add_attr(A_FIELD,"Domain_t","trad","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","erad","ValidField");
   if ( ngroup > 0 ) {
      ProblemArray_add("ematsrc",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"ematsrc","Zonal");
      rgst_add_attr(A_OBJECT,"ematsrc","Mixed");
      rgst_add_attr(A_OBJECT,"ematsrc","PermVar");
      rgst_add_attr(A_OBJECT,"ematsrc","DomainVar");
      if ( iftion == 1 ) {
         ProblemArray_add("eionsrc",NULL,0,R_DOUBLE,NULL);
         rgst_add_attr(A_OBJECT,"eionsrc","Zonal");
         rgst_add_attr(A_OBJECT,"eionsrc","Mixed");
         rgst_add_attr(A_OBJECT,"eionsrc","PermVar");
         rgst_add_attr(A_OBJECT,"eionsrc","DomainVar");
      }
   }
   rgst_add_attr(A_FIELD,"Domain_t","ematsrc",    "ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","eionsrc",    "ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","tmat_extrap","ValidField");
   rgst_add_attr(A_FIELD,"Domain_t","tion_extrap","ValidField");
   if ( neosgroup > 0 ) {
      ProblemArray_add("eosvf",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"eosvf","MultiTable");
      rgst_add_attr(A_OBJECT,"eosvf","PermVar");
      rgst_add_attr(A_OBJECT,"eosvf","DomainVar");
      rgst_add_attr(A_OBJECT,"eosvf","Zonal");
      for (i = 0; i < neosgroup; i++) {
         char gname[MAXWORD];
         sprintf(gname, "eosvf_%d",i);
         ProblemArray_add(gname,NULL,0,R_DOUBLE,NULL);
         rgst_add_attr(A_OBJECT,gname,"ScalAdvVar");
         rgst_add_attr(A_OBJECT,gname,"OnDump");
         rgst_add_attr(A_OBJECT,gname,"Mixed");
         rgst_add_attr(A_OBJECT,gname,"MixedAdv");
         rgst_add_attr(A_OBJECT,gname,"MultDen");
         rgst_add_attr(A_OBJECT,gname,"Zonal");           
         rgst_add_attr(A_OBJECT,gname,"DomainVar");           
      }
      ProblemArray_add("eosef",NULL,0,R_DOUBLE,NULL);
      rgst_add_attr(A_OBJECT,"eosef","MultiTable");
      rgst_add_attr(A_OBJECT,"eosef","PermVar");
      rgst_add_attr(A_OBJECT,"eosef","DomainVar");
      rgst_add_attr(A_OBJECT,"eosef","Zonal");
      for (i = 0; i < neosgroup; i++) {
         char gname[MAXWORD];
         sprintf(gname, "eosef_%d",i);
         ProblemArray_add(gname,NULL,0,R_DOUBLE,NULL);
         rgst_add_attr(A_OBJECT,gname,"ScalAdvVar");
         rgst_add_attr(A_OBJECT,gname,"OnDump");
         rgst_add_attr(A_OBJECT,gname,"Mixed");
         rgst_add_attr(A_OBJECT,gname,"MixedAdv");
         rgst_add_attr(A_OBJECT,gname,"MultDen");
         rgst_add_attr(A_OBJECT,gname,"Zonal");           
         rgst_add_attr(A_OBJECT,gname,"DomainVar");           
      }
      if ( iftion == 1 ) {
         ProblemArray_add("eoseif",NULL,0,R_DOUBLE,NULL);
         rgst_add_attr(A_OBJECT,"eoseif","MultiTable");
         rgst_add_attr(A_OBJECT,"eoseif","PermVar");
         rgst_add_attr(A_OBJECT,"eoseif","DomainVar");
         rgst_add_attr(A_OBJECT,"eoseif","Zonal");
         for (i = 0; i < neosgroup; i++) {
            char gname[MAXWORD];
            sprintf(gname, "eoseif_%d",i);
            ProblemArray_add(gname,NULL,0,R_DOUBLE,NULL);
            rgst_add_attr(A_OBJECT,gname,"ScalAdvVar");
            rgst_add_attr(A_OBJECT,gname,"OnDump");
            rgst_add_attr(A_OBJECT,gname,"Mixed");
            rgst_add_attr(A_OBJECT,gname,"MixedAdv");
            rgst_add_attr(A_OBJECT,gname,"MultDen");
            rgst_add_attr(A_OBJECT,gname,"Zonal");           
            rgst_add_attr(A_OBJECT,gname,"DomainVar");           
         }
      }
   } 


   if (ifdynspec) {
      ProblemArray_add("specfrac",NULL,0,R_STRUCT,NULL);
      rgst_add_attr(A_OBJECT,"specfrac","PermVar");
      rgst_add_attr(A_OBJECT,"specfrac","Mixed");
      rgst_add_attr(A_OBJECT,"specfrac","SpeciesMassFraction");
   }
   rgst_add_attr(A_FIELD,"Domain_t","specfrac","ValidField");
   ProblemArray_add("grdpnt",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"grdpnt","MixMax");
   rgst_add_attr(A_OBJECT,"grdpnt","PermVar");
   rgst_add_attr(A_OBJECT,"grdpnt","DomainVar");
   ProblemArray_add("grdzn",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"grdzn","MixMax");
   rgst_add_attr(A_OBJECT,"grdzn","PermVar");
   rgst_add_attr(A_OBJECT,"grdzn","DomainVar");
   ProblemArray_add("lnkmix",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"lnkmix","MixMax");
   rgst_add_attr(A_OBJECT,"lnkmix","PermVar");
   rgst_add_attr(A_OBJECT,"lnkmix","DomainVar");
   ProblemArray_add("mixzn",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"mixzn","MixMax");
   rgst_add_attr(A_OBJECT,"mixzn","PermVar");
   rgst_add_attr(A_OBJECT,"mixzn","DomainVar");
   ProblemArray_add("grdmix",NULL,0,R_INT,NULL);
   rgst_add_attr(A_OBJECT,"grdmix","MixMax");
   rgst_add_attr(A_OBJECT,"grdmix","PermVar");
   rgst_add_attr(A_OBJECT,"grdmix","DomainVar");
   ProblemArray_add("rlen",     NULL, nregx+1,  R_INT , NULL);
   rgst_add_attr(A_OBJECT,"rlen","DomainVar");
   ProblemArray_add("rlencln",  NULL,  nregx+1, R_INT, NULL);
   rgst_add_attr(A_OBJECT,"rlencln","DomainVar");
   ProblemArray_add("rlenmix",  NULL,  nregx+1, R_INT, NULL);
   rgst_add_attr(A_OBJECT,"rlenmix","DomainVar");
}
void domain_free_attr(void) {
   RGST_AttributeElem_t *validvars;
   RGST_AttributeElem_t *validvars_ptr;
   rgst_del_attr_all("Zonal");
   rgst_del_attr_all("Nodal");
   rgst_del_attr_all("Mixed");
   rgst_del_attr_all("MixMax");
   rgst_del_attr_all("SlideData");
   rgst_del_attr_all("OnDump");
   rgst_del_attr_all("ScalAdvVar");
   rgst_del_attr_all("MixedAdv");
   rgst_del_attr_all("MultDen");
   rgst_del_attr_all("PermVar");
   rgst_del_attr_all("Only2D");
   rgst_del_attr_all("Only3D");
   rgst_del_attr_all("MultiGroup");
   rgst_del_attr_all("MultiTable");
   rgst_del_attr_all("Regional");
   rgst_del_attr_all("SpeciesMassFraction");
   rgst_del_attr_all("NewlyAllocated");
   rgst_del_attr_all("DomainVar");
   rgst_del_attr_all("RBNDCOM1");
   rgst_del_attr_all("RBNDCOM2");
   rgst_del_attr_all("RBNDCOM3");
   validvars    = rgst_list_attr(A_FIELD, "ValidField");
   validvars_ptr = validvars;
   while (validvars_ptr != NULL) {
      char *name    = ATTR_GET_FIELD_NAME(validvars_ptr);
      ProblemArray_del(name,NULL);
      validvars_ptr = validvars_ptr->next;
   }
   rgst_del_attr_all("ValidField");
}
void domain_setpa(Domain_t *domain) {
   char *name;	 
   char gname[MAXWORD];	 
   int  n;
   int  len;
   int  imtt;
   double *dptr;	 
   void *ptr;	 
   ProblemArray_t *prb;
   RGST_AttributeElem_t *permvars;
   RGST_AttributeElem_t *permvars_ptr;
   RGST_Datatype_t rtype;
   permvars     = rgst_list_attr(A_OBJECT, "PermVar");
   permvars_ptr = permvars;
   while ( permvars_ptr != NULL ) {
      name    = ATTR_GET_OBJECT_NAME(permvars_ptr);
      prb     = ProblemArray_find(name, NULL);
      ptr     = RGST_GET_FIELD(domain,"Domain_t",name);
      rtype   = prb->type;
      len = domain->nnalls;
      if  (RGST_QUERY_OBJECT_ATTR(name, "Mixed")) len = domain->namix;
      if  (RGST_QUERY_OBJECT_ATTR(name, "SlideData")) len = domain->nnodes;
      if  (RGST_QUERY_OBJECT_ATTR(name, "MixMax")) len = domain->mixmax;
      imtt = RGST_QUERY_OBJECT_ATTR(name, "MultiTable");
      if ((imtt == 0)  && 
          ((rtype == R_DOUBLE) || (rtype == R_INT))) {
        ProblemArray_add(name, ptr, len, rtype, domain->hash);
      } else if (imtt != 0) {
	 dptr = (double *) ptr;
         ProblemArray_add(name, dptr, neosgroup * domain->namix, rtype, 
	                   domain->hash);
         for (n = 0; n < neosgroup; n++) {
            sprintf(gname,"%s_%d",name,n);
            ProblemArray_add(gname, dptr, domain->namix, rtype, domain->hash);
            dptr += domain->namix;
         }
      } 
      permvars_ptr = permvars_ptr->next;
   }
   ProblemArray_add("rlen",     domain->rlen,     nregx+1, R_INT, domain->hash);
   ProblemArray_add("rlencln",  domain->rlencln,  nregx+1, R_INT, domain->hash);
   ProblemArray_add("rlenmix",  domain->rlenmix,  nregx+1, R_INT, domain->hash);
   domain->rmixzn[0]  = domain->mixzn;
   domain->rgrdmix[0] = domain->grdmix;
}
void domain_free(Domain_t *domain)
{
   char *me = "domain_free";
   char *name;
   int i, ibc, len, ispec;
   void **ptr;
   RGST_AttributeElem_t *permvars;
   RGST_AttributeElem_t *permvars_ptr;
   RGST_AttributeElem_t *func;
   permvars     = rgst_list_attr(A_OBJECT, "PermVar");
   permvars_ptr = permvars;
   while ( permvars_ptr != NULL ) {
      name    = ATTR_GET_OBJECT_NAME(permvars_ptr);
      ispec   = RGST_QUERY_OBJECT_ATTR(name, "SpeciesMassFraction"); 
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      if (ispec == 0) {
         FREEMEM(*ptr);
      }
      permvars_ptr = permvars_ptr->next;
   }
   FREEMEM(domain->rlen);
   FREEMEM(domain->rlencln);
   FREEMEM(domain->rlenmix);
   for (i = 0; i < domain->nsrc; i++) {
     if (domain->src != NULL) {
       FREEMEM(domain->src[i].ndxsrc);
       if (domain->src[i].nidat1>0) {
          FREEMEM(domain->src[i].idat1);
       }
       if (domain->src[i].nfdat1>0) {
          FREEMEM(domain->src[i].fdat1);
       }
       if (domain->src[i].ndat2>0) {
          FREEMEM(domain->src[i].dat2);
       }
     }
   }
   FREEMEM(domain->src);
   if (ifdynspec > 0) {
      for (i = 0; i < domain->namix; i++) {
         if (domain->specfrac[i].mass_frac != NULL) {
            FREEMEM(domain->specfrac[i].mass_frac);
         }
      }
      FREEMEM(domain->specfrac);
   }
   FREEMEM(domain->rndx) ;
   FREEMEM(domain->rndxmix) ;
   FREEMEM(domain->rgrdmix) ;
   FREEMEM(domain->rmixzn) ;
   for (ibc = 0; ibc < domain->nbc; ibc++) {
      if (domain->bc != NULL) {
        FREEMEM(domain->bc[ibc].ndx);
        FREEMEM(domain->bc[ibc].zonelist);
      }
   }
   FREEMEM(domain->bc);
   if (domain->phonlen > 0) {
      FREEMEM(domain->phondx  ) ;
      FREEMEM(domain->phonbc  ) ;
      FREEMEM(domain->bndndx  ) ;
   }
   if (domain->phozlen > 0) {
      FREEMEM(domain->phozdx  ) ;
      FREEMEM(domain->bndzdx  ) ;
   }
   for (ibc = 0; ibc < domain->nbnd; ibc++) {
      if (domain->bnd != NULL) {
         FREEMEM(domain->bnd[ibc].ndx_send);
         FREEMEM(domain->bnd[ibc].zdx_send);
         FREEMEM(domain->bnd[ibc].ndx_recv);
         FREEMEM(domain->bnd[ibc].zdx_recv);
         FREEMEM(domain->bnd[ibc].zdx_neighbor);
         FREEMEM(domain->bnd[ibc].momflxtag);
      }
   }
   FREEMEM(domain->bnd);
   GlobalArrays_free(domain->hash);
   TimeStepControl_free(domain->hash);
   FunctionTimer_free(domain->hash);
   FunctionTimer_ht_remove(domain->hash, "threaded");
   ProblemArray_del_all(domain->hash);
   func = rgst_list_attr(A_OBJECT, "Function_DomainFree");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(domain->hash);  
      func = func->next;
   }
   if (domain->hash->name != NULL) { 
     rgst_del(domain->hash->name); 
   }
   domain->hash = hash_tbl_free(domain->hash,FALSE);
}
void domain_allot( Domain_t *domain, int imax, int jmax, int kmax)
{
   Domain_init(domain);
   domain_setlimits( domain, imax, jmax, kmax);
   domain_null_fields(domain);
   domain_allot_arrays1(domain);
   domain->nsrc = 0;
   domain->ndeltat = deltat ;
   domain->dtg     = deltat ;
   domain->dtcon   = '0' ;
   domain->dti     = 0 ;
   domain->dtj     = 0 ;
   domain->dtk     = 0 ;
   domain->nbc  = 0 ;
   domain->nbnd = 0 ;
   domain->phonlen = 0 ;
   domain->phozlen = 0 ;
   domain_allot_arrays2(domain);
   domain_setpa(domain);
}
int domain_allot_arrays1(
  Domain_t *domain) 
{
  char *me = "domain_allot_arrays1";
  char *errmsg1 = "about to allocate domain field that is already allocated";
  char tstr[32];
  int i;
  if (domain->hash != NULL) {
    ctlnotice(me,"Re-allocating domain level hash table");
    if (domain->hash->name != NULL) { rgst_del(domain->hash->name); }
    domain->hash = hash_tbl_free(domain->hash,FALSE);
  }
  domain->hash = hash_tbl_create(DEFAULT_HASHSIZE,NULL); 
  FunctionTimer_ht_setup(domain->hash, "threaded");
  if (   (domain->src       != NULL)
      || (domain->rndx      != NULL)
      || (domain->rndxmix   != NULL)
      || (domain->rgrdmix   != NULL)
      || (domain->rmixzn    != NULL)
      || (domain->bc        != NULL)
      || (domain->bnd       != NULL)
     ) ctlerror(me,errmsg1);
  domain->src = Source_construct(nsrcx);
  domain->nsrc = nsrcx;
  domain->rndx    = ALLOT(pint,nregxplus1);
  domain->rndxmix = ALLOT(pint,nregxplus1);
  domain->rgrdmix = ALLOT(pint,nregxplus1);
  domain->rmixzn  = ALLOT(pint,nregxplus1);
  domain->bc  = ALLOT(BoundaryCondition_t,nbcx);
  domain->nbc = nbcx;
  for (i=0; i<nbcx;  i++) BoundaryCondition_init(&domain->bc[i]);
  domain->bnd    = ALLOT(Boundary_t, nbndx);
  domain->nbnd   = nbndx;
  if (   (domain->src       == NULL)
      || (domain->rndx      == NULL)
      || (domain->rndxmix   == NULL)
      || (domain->rgrdmix   == NULL)
      || (domain->rmixzn    == NULL)
      || (domain->bc        == NULL)
      || (domain->bnd       == NULL)
     ) ctlerror(me, gv_errmsg_memory);
  for (i=0; i<nbndx; i++) domain->bnd[i].active = 0;
  if (   (domain->rlen    != NULL)
      || (domain->rlencln != NULL)
      || (domain->rlenmix != NULL) ) ctlerror(me,errmsg1);
  domain->rlen     = ALLOT(int, nregxplus1);
  domain->rlencln  = ALLOT(int, nregxplus1);
  domain->rlenmix  = ALLOT(int, nregxplus1);
  if (   (domain->rlen    == NULL)
      || (domain->rlencln == NULL)
      || (domain->rlenmix == NULL) ) ctlerror(me, gv_errmsg_memory);
  return(0);
}
int domain_allot_arrays2( Domain_t *domain )
{
   char *me      = "domain_allot_arrays" ;
   int i;
   GlobalArrays_allot(domain->hash);
   domain_allot_fields( domain ) ;
   return(0) ;
}
void domain_allot_fields( Domain_t *domain ) {
   char *name;	 
   int i     ;
   int len   ;
   int flag  ;
   int ispec ;
   int *iptr;	 
   double *dptr;	 
   void **ptr;	 
   SpeciesFraction_t *specmf;
   ProblemArray_t *prb;
   RGST_AttributeElem_t *validfield;
   RGST_AttributeElem_t *validfield_ptr;
   RGST_AttributeElem_t *permvars;
   RGST_AttributeElem_t *permvars_ptr;
   RGST_Datatype_t rtype;
   validfield     = rgst_list_attr(A_FIELD, "ValidField");
   validfield_ptr = validfield;
   while ( validfield_ptr != NULL ) {
      name    = ATTR_GET_FIELD_NAME(validfield_ptr);
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      flag    = RGST_QUERY_OBJECT_ATTR(name, "PermVar") ;
      ispec   = RGST_QUERY_OBJECT_ATTR(name, "SpeciesMassFraction"); 
      if ((ispec == 0) && (flag == 0) && (*ptr != NULL))   {
         FREEMEM(*ptr);
         ProblemArray_del(name,domain->hash);
      }
      if ((ispec != 0) && (flag == 0) && (*ptr != NULL))  {
          specmf = (SpeciesFraction_t *)(*ptr);
          for (i = 0; i < domain->namix; i++) {
             if (specmf[i].mass_frac != NULL) FREEMEM(specmf[i].mass_frac);
          }
          FREEMEM(specmf);
          ProblemArray_del(name,domain->hash);
      }
      validfield_ptr = validfield_ptr->next;
   }
   permvars     = rgst_list_attr(A_OBJECT, "PermVar");
   permvars_ptr = permvars;
   while ( permvars_ptr != NULL ) {
      name    = ATTR_GET_OBJECT_NAME(permvars_ptr);
      prb     = ProblemArray_find(name, NULL);
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      rtype   = prb->type;
      len = domain->nnalls;
      if  (RGST_QUERY_OBJECT_ATTR(name, "Mixed"))      len = domain->namix;
      if  (RGST_QUERY_OBJECT_ATTR(name, "SlideData"))  len = domain->nnodes;
      if  (RGST_QUERY_OBJECT_ATTR(name, "MultiGroup")) len = ngroup * domain->namix;
      if  (RGST_QUERY_OBJECT_ATTR(name, "MultiTable")) len = neosgroup * domain->namix;
      if  (RGST_QUERY_OBJECT_ATTR(name, "MixMax"))     len = domain->mixmax;
      if (*ptr == NULL) {
         if (rtype == R_DOUBLE) {
            dptr = ALLOT(double, len);
            *ptr = dptr;
            RGST_ADD_FIELD_ATTR("Domain_t",name,"NewlyAllocated");
         } else if (rtype == R_INT) {
            iptr = ALLOT(int, len);
            *ptr = iptr;
            RGST_ADD_FIELD_ATTR("Domain_t",name,"NewlyAllocated");
         } else if  (RGST_QUERY_OBJECT_ATTR(name, "SpeciesMassFraction")) {
            int ii;
            SpeciesFraction_t *myspecmf = MALLOT(SpeciesFraction_t, len);
            RGST_ADD_FIELD_ATTR("Domain_t",name,"NewlyAllocated");
            *ptr = myspecmf;
            for (ii = 0; ii < domain->namix; ii++) {
               myspecmf[ii].mass_frac = NULL;
            }
         } 
      } else {
         if (rtype == R_DOUBLE) {
            dptr = (double *) (*ptr);
            dptr = REALLOT(dptr, double, len);
            *ptr = dptr;
         } else if (rtype == R_INT) {
            iptr = (int *) (*ptr);
            iptr = REALLOT(iptr, int, len);
            *ptr = iptr;
         } else if  (RGST_QUERY_OBJECT_ATTR(name, "SpeciesMassFraction")) {
            SpeciesFraction_t *myspecmf;
            myspecmf = (SpeciesFraction_t *) (*ptr);
            myspecmf = REALLOT(myspecmf, SpeciesFraction_t, len);
            *ptr = myspecmf;
         } 
      }
      permvars_ptr = permvars_ptr->next;
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "tmat", "NewlyAllocated") ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->tmat[i]    = ptiny ;
      }
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "tion", "NewlyAllocated") ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->tion[i]  = ptiny ;
      }
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "trad", "NewlyAllocated") ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->trad[i] = ptiny ;
      }
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "tmat_extrap", "NewlyAllocated") ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->tmat_extrap[i] =  domain->tmat[i];
      }
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "tion_extrap", "NewlyAllocated") ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->tion_extrap[i] =  domain->tion[i];
      }
   }
   if (RGST_QUERY_FIELD_ATTR("Domain_t", "eosvf", "NewlyAllocated") ) {
      for ( i = 0 ; i < ( neosgroup * domain->namix ) ; i++ ) {
         domain->eosvf[i] = 1.0 ;
      }
   }
   rgst_del_attr_all("NewlyAllocated");
}
static void domain_null_fields(Domain_t *domain) {
   RGST_AttributeElem_t *validvars;
   RGST_AttributeElem_t *validvars_ptr;
   char *name;
   void **ptr;
   validvars     = rgst_list_attr(A_FIELD, "ValidField");
   validvars_ptr = validvars;
   while ( validvars_ptr != NULL ) {
      name    = ATTR_GET_FIELD_NAME(validvars_ptr);
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      *ptr = NULL;
      validvars_ptr = validvars_ptr->next;
   }
}
void domain_setlimits( Domain_t *domain, int imax, int jmax, int kmax)
{
   int  ilen, jlen, klen, ijlen, jklen, iklen, maxlen;
   if ( domain->type == QUAD2D ) {
      domain->imin = NPNL ;
      domain->jmin = NPNL ;
      domain->kmin = 0 ;
      domain->imax = imax + NPNL - 1 ;
      domain->jmax = jmax + NPNL - 1 ;
      domain->kmax = 0 ;
      domain->jp     = domain->imax - domain->imin + 1 + NPNL + NPNR ;
      domain->kp     = 0 ;
      domain->nnalls = domain->jp * (domain->jmax - domain->jmin + 1 + NPNL + NPNR) ;
      domain->fpn    = 0 ;
      domain->lpn    = domain->nnalls - 1 ;
      domain->frn    = domain->fpn + NPNL * domain->jp + NPNL ;
      domain->lrn    = domain->lpn - NPNR * domain->jp - NPNR ;
      domain->fpz    = domain->frn - domain->jp - 1 ;
      domain->lpz    = domain->lrn ;
      domain->frz    = domain->frn ;
      domain->lrz    = domain->lrn - domain->jp - 1 ;
      ilen    = domain->imax - domain->imin + 1 + NPNL + NPNR ;
      jlen    = domain->jmax - domain->jmin + 1 + NPNL + NPNR ;
      maxlen  = MAX( ilen, jlen ) ;
   }
   if ( domain->type == HEX3D ) {
      domain->imin = NPNL ;
      domain->jmin = NPNL ;
      domain->kmin = NPNL ;
      domain->imax = imax + NPNL - 1 ;
      domain->jmax = jmax + NPNL - 1 ;
      domain->kmax = kmax + NPNL - 1 ;
      domain->jp     = domain->imax - domain->imin + 1 + NPNL + NPNR ;
      domain->kp     = domain->jp * (domain->jmax - domain->jmin + 1 + NPNL + NPNR) ;
      domain->nnalls = domain->kp * (domain->kmax - domain->kmin + 1 + NPNL + NPNR) ;
      domain->fpn    = 0 ;
      domain->lpn    = domain->nnalls - 1 ;
      domain->frn    = domain->fpn + NPNL * (domain->kp + domain->jp) + NPNL ;
      domain->lrn    = domain->lpn - NPNR * (domain->kp + domain->jp) - NPNR ;
      domain->fpz    = domain->frn - domain->jp - domain->kp - 1 ;
      domain->lpz    = domain->lrn ;
      domain->frz    = domain->frn ;
      domain->lrz    = domain->lrn - domain->jp - domain->kp - 1 ;
      ilen    = domain->imax - domain->imin + 1 + NPNL + NPNR ;
      jlen    = domain->jmax - domain->jmin + 1 + NPNL + NPNR ;
      klen    = domain->kmax - domain->kmin + 1 + NPNL + NPNR ;
      ijlen   = ilen * jlen ;
      jklen   = jlen * klen ;
      iklen   = ilen * klen ;
      maxlen  = MAX( ijlen, jklen  ) ;
      maxlen  = MAX( iklen, maxlen ) ;
   }
   domain->mixmax  = domain->sclnamix * domain->nnalls ;
   domain->namix   = domain->nnalls + domain->mixmax ;
   domain->nmixcnt = 0 ;
   domain->nmixzn  = 0 ;
   domain->imaxmix = 0 ;
   if (domain->nnodes == 0) {
     domain->nnodes = domain->nnalls;
   }
   domain->nzones = domain->nnalls ;
}
static void domain_TdiffOrient(char *name, int orientation)
{
  HashTable_t *hash;
  int *data = MALLOT(int, 1);
  data[0] = orientation;
  rgst_add_attr(A_OBJECT, name,"HasOrientation");
  ProblemArray_CreateHash(name, NULL, 23);
  hash = ProblemArray_GetHash(name, NULL);
  hash_add("Orientation", "int", data, hash);
}
