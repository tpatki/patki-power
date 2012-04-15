#include "irs.hh"
#include "irsbndry.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "irslag.h"
#include "irsctl.h"
#include "irsdmp.h"
#include "irseos.h"
#include "irslag.hh"
#include "irsparm.hh"
#include "BlockMapping.h"
#include "CycleMesg.h"
#include "FunctionTimer.h"
#include "Hash.h"
#include "Gparm.h"
#include "VersionData.h"
#include "TimePlot.h"
#include "TimeStepControl.hh"
void parminit( void )
{
   char *me = "parminit", myversion[MAXWORD] ;
   int i, my_maxtpdata;
   char msg[128];
   strcpy(myversion,gv_ver.date_compiled) ;
   NEWPARMI("mixmax", mixmax,  -1)
   NEWPARMI("nblkx",  nblkx,  576)
   NEWPARMI("nblk",   nblk,     0)
   NEWPARMI("gnblk",  gnblk,    0)
   NEWPARMI("unblk",  unblk,    0)
   NEWPARMI("blknum", blknum,   0)
   NEWPARMI("ndims",  ndims,    2)
   NEWPARMF("sclnamix", sclnamix, 0.1)
   memset(box,    '\0',MAXWORD);
   memset(title,  '\0',MAXWORD);
   memset(pbnm,   '\0',MAXWORD);

/* memset(version,'\0',MAXWORD); */

   memset(dtcon,  '\0',1);
   memset(RestartKernel,'\0',RESTART_KERNEL_LEN);
   NEWPARMC("box",     box,     "x00",                MAXWORD);
   NEWPARMC("title",   title,   codename,             MAXWORD);
   NEWPARMC("pbnm",    pbnm,    codename,             MAXWORD);

/* NEWPARMC("version", version, gv_ver.date_compiled, MAXWORD); */

   NEWPARMC("dtcon", dtcon, "0", 1);
   NEWPARMC("RestartKernel",RestartKernel, codename, RESTART_KERNEL_LEN);
   NEWPARMI("pdmd",        pdmd,         0)
   NEWPARMI("coredumpflag",coredumpflag, 0)
   NEWPARMI("RestartCycle",RestartCycle, 0)
   NEWPARMI("ifhilite", ifhilite, 0)
   NEWPARMI("ifdivgrad",ifdivgrad,1)
   NEWPARMI("electronConduction",ifedif,0)
   NEWPARMI("ionConduction",ifidif,0)
   NEWPARMI("ifhgfb",ifhgfb,0)
   NEWPARMI("ifkrwgt",ifkrwgt,1)
   NEWPARMI("ifplane",ifplane,0)
   NEWPARMI("ifpolar",ifpolar,1)
   NEWPARMI("iftion",iftion,0)
   NEWPARMI("iftmode",iftmode,0)
   NEWPARMI("ifeden",ifeden,0)
   NEWPARMI("ifvol72",ifvol72,0)
   NEWPARMI("ngroup",ngroup,0)
   NEWPARMI("solver",solver,2)
   NEWPARMI("ifprecon",ifprecon,2)
   NEWPARMI("wainwright",wainwright,1)
   NEWPARMI("kapsav",kapsav,0)
   NEWPARMI("lmax",lmax,0) 
   NEWPARMF("ptiny",ptiny,1.0e-80)
   NEWPARMF("plarge",plarge,1.0e80)
   NEWPARMF("xcut",xcut,1.0e-10)
   NEWPARMF("ucut",ucut,1.0e-10)
   NEWPARMF("volcut",volcut,1.e-16)
   NEWPARMF("xgrav",xgrav,0.)
   NEWPARMF("ygrav",ygrav,0.)
   NEWPARMF("zgrav",zgrav,0.)
   NEWPARMF("eifrac",eifrac,1.0)
   NEWPARMI("ifcom",ifcom,0)
   NEWPARMI("ifsewbnd",ifsewbnd,0)
   NEWPARMI("ifthreads",ifthreads,0)
   NEWPARMI("ifparallel",ifparallel,0)
   NEWPARMI("ifvsame",ifvsame,0)
   NEWPARMI("vsame_max_id",vsame_max_id,0)
   NEWPARMF("com_physics_time",com_physics_time,0.0)
   NEWPARMI("warntime",warntime,900)
   NEWPARMF("time",ttime,0.)
   NEWPARMF("tstop",tstop,0.)
   NEWPARMF("deltat",deltat,1.e-3)
   NEWPARMF("ndeltat",ndeltat,1.e-3)
   NEWPARMF("deltatSubcycle",deltatSubcycle,1.e-3)
   NEWPARMI("cycle",cycle,0)
   NEWPARMI("cstop",cstop,10000)
   NEWPARMF("dtmin",dtmin,1.0e-4)
   NEWPARMF("dtmax",dtmax,1.0)
   NEWPARMF("fcrnt",fcrnt,0.5)
   NEWPARMF("dtfc",dtfc,1.2)
   NEWPARMF("dtffc",dtffc,0.1)
   NEWPARMF("dtgfc",dtgfc,1.0)
   NEWPARMF("dtjfc",dtjfc,0.1)
   NEWPARMF("dtefc",dtefc,0.2)
   NEWPARMF("dtifc",dtifc,0.2)
   NEWPARMF("dtrfc",dtrfc,0.2)
   NEWPARMF("dtsefc",dtsefc,0.05)
   NEWPARMF("dtsifc",dtsifc,0.05)
   NEWPARMF("dttfc",dttfc,0.1)
   NEWPARMF("dtvfc",dtvfc,0.5)
   NEWPARMF("dtwfc",dtwfc,0.1)
   NEWPARMF("dtemin",dtemin,0.01)
   NEWPARMF("dtimin",dtimin,0.01)
   NEWPARMF("dtrmin",dtrmin,0.01)
   NEWPARMF("dtsemin",dtsemin,0.05)
   NEWPARMF("dtsimin",dtsimin,0.05)
   NEWPARMF("dtwmin",dtwmin,0.001)
   NEWPARMF("vfdtmin",vfdtmin,0.01)
   NEWPARMI("dtb",dtb,0)
   NEWPARMI("dti",dti,0)
   NEWPARMI("dtj",dtj,0)
   NEWPARMI("dtk",dtk,0)
   NEWPARMF("qquad",xquad,0.75)
   NEWPARMF("qlin",qlin,0.5)
   NEWPARMF("qprlx",qprlx,0.5)
   NEWPARMF("qneg",qneg,0.0)
   NEWPARMF("hgfrac",hgfrac,1.0)
   NEWPARMF("hgheat",hgheat,1.0)
   NEWPARMF("qdvfrac",qdvfrac,1.0)
   NEWPARMI("hgiter",hgiter,1)
   NEWPARMI("pdviter",pdviter,1)
   NEWPARMI("qmode",qmode,1)
   NEWPARMI("nditer",nditer,0)
   NEWPARMF("srcfi",srcfi,1.0) ;
   NEWPARMF("srcfe",srcfe,1.0) ;
   NEWPARMI("neos",neos,0)
   NEWPARMI("neosx",neosx,20)
   NEWPARMF("sndmin",sndmin,1.0e-4)
   NEWPARMF("tscale",tscale,1.0e-3)
   NEWPARMI("ioneq",ioneq,0)
   NEWPARMI("ifconvert",ifconvert,0)
   NEWPARMI("if_eos_mix_zeq",if_eos_mix_zeq,0)
   NEWPARMI("nspec",nspec,0)
   NEWPARMI("ifdynspec",ifdynspec,0)
   NEWPARMI("neosgroup",neosgroup,0)
   NEWPARMF("sbc",sbc,137.20160)
   NEWPARMI("planckwt",planckwt,0)
   NEWPARMF("tfloor",tfloor,1.0e-6)
   NEWPARMF("rflx",rflx,1.0)
   NEWPARMI("rdifit",rdifit,0)
   NEWPARMI("edifit",edifit,0)
   NEWPARMI("idifit",idifit,0)
   NEWPARMI("rdifitn",rdifitn,1)
   NEWPARMI("rdifitx",rdifitx,1000)
   NEWPARMF("rdifeps",rdifeps,0.0)
   NEWPARMF("rdifepsx",rdifepsx,1.0e-6)
   NEWPARMF("rdifmiln",rdifmiln,0.756)
   NEWPARMF("ktfloor",ktfloor,0.01)
   NEWPARMI("irvoid",irvoid,0)
   NEWPARMF("denvoid",denvoid,1.0e-6)
   NEWPARMF("ematvoid",ematvoid,0.)
   NEWPARMF("mass0",mass0,0.)
   NEWPARMF("etot0",etot0,0.)
   NEWPARMF("masstot",masstot,0.)
   NEWPARMF("volumetot",volumetot,0.)
   NEWPARMF("xmomtot",xmomtot,0.)
   NEWPARMF("ymomtot",ymomtot,0.)
   NEWPARMF("zmomtot",zmomtot,0.)
   NEWPARMF("xmomtotp",xmomtotp,0.)
   NEWPARMF("ymomtotp",ymomtotp,0.)
   NEWPARMF("zmomtotp",zmomtotp,0.)
   NEWPARMF("xmomtotn",xmomtotn,0.)
   NEWPARMF("ymomtotn",ymomtotn,0.)
   NEWPARMF("zmomtotn",zmomtotn,0.)
   NEWPARMF("ketot",ketot,0.)
   NEWPARMF("ietot",ietot,0.)
   NEWPARMF("etot",etot,0.)
   NEWPARMF("tketot",tketot,0.)
   NEWPARMF("petot",petot,0.)
   NEWPARMF("qdvtot",qdvtot,0.)
   NEWPARMF("eleak",eleak,0.)
   NEWPARMF("engsrc",engsrc,0.)
   NEWPARMF("tnetot",tnetot,0.)
   NEWPARMF("dtnetot",dtnetot,0.)
   NEWPARMF("eloss",eloss,0.)
   NEWPARMF("echk",echk,0.)
   NEWPARMF("echkx",echkx,0.1)
   NEWPARMF("delag",delag,0.)
   NEWPARMF("deadv",deadv,0.)
   NEWPARMF("dieadv",dieadv,0.)
   NEWPARMF("dkeadv",dkeadv,0.)
   NEWPARMI("nbcx",nbcx,10)
   NEWPARMI("nbndx",nbndx,27)
   NEWPARMI("nsrc",nsrc,0)
   NEWPARMI("nsrcx",nsrcx,20)
   NEWPARMI("nbq",nbq,0)
   NEWPARMI("nbqx",nbqx,20)
   NEWPARMI("nfq",nfq,0)		
   NEWPARMI("maxtimeplot",maxtimeplot,50)		
   NEWPARMI("ncyc",ncyc,0)
   NEWPARMI("maxcycleplot",maxcycleplot,50)
   NEWPARMI("ntp",ntp,0)
   NEWPARMI("itp",itp,1)
   my_maxtpdata = maxtimeplot + maxcycleplot;
   NEWPARMI("maxtpdata",maxtpdata,my_maxtpdata)
   NEWPARMI("maxtplot",maxtplot,256)	
   NEWPARMI("nreg",nreg,0)
   NEWPARMI("nregplus1",nregplus1,0)
   NEWPARMI("nregx",nregx,20)
   NEWPARMI("nregxplus1",nregxplus1,21)
   NEWPARMI("ngroupx",ngroupx,5)
   NEWPARMI("ngparm",ngparm,0)
   NEWPARMI("ngparmx",ngparmx,100)
   NEWPARMI("ndtg", ndtg, 1)
   NEWPARMI("ndtgx", ndtgx, 1)
   NEWPARMI("subcycle", subcycle, 0)
   NEWPARMI("maxsubcycles", maxsubcycles, 1000)
   NEWPARMI("sourcesubcycle",sourcesubcycle,0)
   NEWPARMF("dtg", dtg, 0.0)
   NEWPARMI("ifkwgt",ifkwgt,0)
   NEWPARMF("tkewgt",tkewgt,1.)
   NEWPARMF("tkecut",tkecut,1.)
   rgst_add_attr(A_OBJECT, "etot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "ketot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "ietot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "petot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "masstot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "volumetot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "xmomtot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "ymomtot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "zmomtot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "xmomtotp", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "ymomtotp", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "zmomtotp", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "xmomtotn", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "ymomtotn", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "zmomtotn", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "tnetot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "dtnetot", "ParmAccumEdit");
   rgst_add_attr(A_OBJECT, "nblkx",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ndims",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ifplane",   "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "iftion",    "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "kapsav",    "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ioneq",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ifdynspec", "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "nbcx",      "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "nbndx",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "nsrcx",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "nregx",     "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ngparmx",   "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "sclnamix",  "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "sourcesubcycle", "ParmMemorySensitive");
   rgst_add_attr(A_OBJECT, "ifsewbnd", "ParmParallelSensitive");
   rgst_add_attr(A_OBJECT, "ifvsame",  "ParmParallelSensitive");
   rgst_add_attr(A_OBJECT, "irvoid",   "ParmParallelSensitive");
   rgst_add_attr(A_OBJECT, "ifprecon", "ParmParallelSensitive");
   hash_tbl_create_n_rgst(&gv_hash_tbl, 3, GENERAL_HASHTBL_NAME);
   FunctionTimer_ht_setup(gv_hash_tbl, "global");
}
