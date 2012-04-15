#include "irs.h"
#include "irsblk.h"    
#include "irsbndry.h"  
#include "irscom.h"    
#include "irsctl.h"    
#include "irscur.h"    
#include "irsdefs.h"   
#include "irsdmp.h"  
#include "irsedits.h"  
#include "irseos.h"	  
#include "irsgen.h"	  
#include "irsgenrd.h"  
#include "irslag.h"	     
#include "irsobjects.h"      
#include "irsparm.h"	     
#include "irsreg.h"	    
#include "irsrgst.h"     
#include "irssrc.h"
#include "irssys.h"
#include "irstdiff.h"
#include "irs.h"
#include "Command.h"
#include "Conditional.h"
#include "CycleMesg.h"
#include "FreqMesg.h"
#include "FunctionTimer.h"
#include "Hash.h"	     
#include "Spline.h"
#include "TimePlot.h"
#include "TimeStepControl.h"
#include "Tracer.h"
#include "Transform.h"
#include "UserList.h"
#include "NodeList.h"
int inst_com(void)
{
   hash_tbl_create_n_rgst(&symtab , 11, "symbols");
   inst_c( "deck",            deck,                    zargs,       0, symtab );
   inst_c( "done",            endfile,                 zargs,       0, symtab );
   inst_c( "boxid",           boxid,                   zargs,       0, symtab );
   inst_c( "step",            step,                    zargs,       0, symtab );
   inst_c( "pole",            pole,                    zargs,       0, symtab );
   inst_c( "print",           print,                   zargs,       0, symtab );
   inst_c( "printspline",     spline_print,            zargs,       0, symtab );
   inst_c( "psp",             spline_print,            zargs,       0, symtab );
   inst_c( "printnodelist",   printnodelist,           zargs,       0, symtab );
   inst_c( "pnl",             printnodelist,           zargs,       0, symtab );
   inst_c( "printtimefreqs",  printtimefreqs,          zargs,       0, symtab );
   inst_c( "ptf",             printtimefreqs,          zargs,       0, symtab );
   inst_c( "printcyclefreqs", printcyclefreqs,         zargs,       0, symtab );
   inst_c( "pcf",             printcyclefreqs,         zargs,       0, symtab );
   inst_c( "printtpcurves",   printtpcurves,           zargs,       0, symtab );
   inst_c( "ptpc",            printtpcurves,           zargs,       0, symtab );
   inst_c( "printtimeplots",  printtimeplots,          zargs,       0, symtab );
   inst_c( "ptp",             printtimeplots,          zargs,       0, symtab );
   inst_c( "printmap",        printmap,                zargs,       0, symtab );
   inst_c( "pm",              printmap,                zargs,       0, symtab );
   inst_c( "printhash",       printhash,               zargs,       0, symtab );
   inst_c( "ph",              printhash,               zargs,       0, symtab );
   inst_c( "printrgst",       printrgst,               zargs,       0, symtab );
   inst_c( "pr",              printrgst,               zargs,       0, symtab );
   inst_c( "printattr",       printattr,               zargs,       0, symtab );
   inst_c( "pa",              printattr,               zargs,       0, symtab );
   inst_c( "printattrlist",   printattrlist,           zargs,       0, symtab );
   inst_c( "pal",             printattrlist,           zargs,       0, symtab );
   inst_c( "printtsc",        TimeStepControl_print,   zargs,       0, symtab );
   inst_c( "ptsc",            TimeStepControl_print,   zargs,       0, symtab );
   inst_c( "printtc",         printtc,                 zargs,       0, symtab );
   inst_c( "ptc",             printtc,                 zargs,       0, symtab );
   inst_c( "printuserlist",   UserList_print,          zargs,       0, symtab );
   inst_c( "pul",             UserList_print,          zargs,       0, symtab );
   inst_c( "date",            printdate,               zargs,       0, symtab );
   inst_c( "help",            input_command_help,      zargs,       0, symtab );
   inst_c( "h",               input_command_help,      zargs,       0, symtab );
   inst_c( "printtimer",      printtimer,              zargs,       0, symtab );
   inst_c( "printtimers",     printtimer,              zargs,       0, symtab );
   inst_c( "prtimer",         printtimer,              zargs,       0, symtab );
   inst_c( "prtimers",        printtimer,              zargs,       0, symtab );
   inst_c( "prti",            printtimer,              zargs,       0, symtab );
   inst_c( "timers",          timers_file,             zargs,       0, symtab );
   inst_c( "timers_screen",   timers_stdout,           zargs,       0, symtab );
   inst_c( "hashopti",        hash_optimize_all,       zargs,       0, symtab );
   inst_c( "system",          SystemWrapper,           zargs,       0, symtab );
   inst_c( "bndrydev",        bndrydev,                zargse,      0, symtab );
   inst_c( "if",              conditionals_if,         zargse,      0, symtab );
   inst_c( "endif",           conditionals_endif,      zargse,      0, symtab );
   inst_c( "echo",            ctlecho,                 zargse,      0, symtab );
   inst_c( "fitspline",       spline_fit,              zargse,      0, symtab );
   inst_c( "set",             set,                     zargse,      0, symtab );
   inst_c( "doneset",         ndset,                   zargse,      0, symtab );
   inst_c( "bc",              bcin,                    zargse,      0, symtab );
   inst_c( "bnd",             bndin,                   zargse,      0, symtab );
   inst_c( "matchbnd",        Blocks_match,            zargse,      0, symtab );
   inst_c( "region",          region_input,            zargse,      0, symtab );
   inst_c( "regop",           region_opin,             zargse,      0, symtab );
   inst_c( "gen",             gen,                     zargse,      0, symtab );
   inst_c( "pregen",          regen_pregen,            zargse,      0, symtab );
   inst_c( "reset",           regen_reset,             zargse,      0, symtab );
   inst_c( "regen",           regen,                   zargse,      0, symtab );
   inst_c( "reblkdiv",        reblkdiv,                zargse,      0, symtab );
   inst_c( "altmesh",         altmesh,                 zargse,      0, symtab );
   inst_c( "plotmd",          plotmd,                  zargse,      0, symtab );
   inst_c( "delcur",          delcur,                  zargse,      0, symtab );
   inst_c( "xlim",            xlim,                    zargse,      0, symtab );
   inst_c( "ylim",            ylim,                    zargse,      0, symtab );

#ifdef SILO
   inst_c( "wgdmp",           wgdmp,                   zargse,      0, symtab );
   inst_c( "rdmp",            Restart_read,            zargse,      0, symtab );
   inst_c( "wdmp",            Restart_write,           sargs,       0, symtab );
   inst_c( "zdmp",            Restart_write,           sargs,       1, symtab );
   inst_c( "wtmesh",          wtmesh,                  zargse,      0, symtab );
#endif
   inst_c( "rdmesh",          rdmesh,                  zargse,      0, symtab );
   inst_c( "spline",          spline_input,            zargse,      0, symtab );
   inst_c( "fillvar",         fillvar_input,           zargse,      0, symtab );
   inst_c( "maxmin",          maxmin,                  zargse,      0, symtab );
   inst_c( "minmax",          maxmin,                  zargse,      0, symtab );
   inst_c( "create",          create_temp_pa,          zargse,      0, symtab );
   inst_c( "nodelist",        NodeList_read,           zargse,      0, symtab );
   inst_c( "list",            UserList_input,          zargse,      0, symtab );
   inst_c( "delete",          free_temp_pa,            zargse,      0, symtab );
   inst_c( "curbold",         curbold,                 zargse,      0, symtab );
   inst_c( "pamp",            pamp,                    zargse,      0, symtab );
   inst_c( "tpamp",           tpamp,                   zargse,      0, symtab );
   inst_c( "delmsg",          delfq,                   zargse,      0, symtab );
   inst_c( "redomsg",         redofq,                  zargse,      0, symtab );
   inst_c( "showmsg",         showfq,                  zargse,      0, symtab );
   inst_c( "purify",          purify,                  zargse,      0, symtab );
   inst_c( "matedit",         matedit,                 zargse,      0, symtab );
   inst_c( "flagedit",        flagedit,                zargse,      0, symtab );
   inst_c( "stateedit",       stateedit,               zargse,      0, symtab );
   inst_c( "realindex",       realindex,               zargse,      0, symtab );
   inst_c( "zone",            zone,                    zargse,      0, symtab );
   inst_c( "plsp",            spline_plsp,             zargse,      0, symtab );
   inst_c( "plspoff",         spline_plspoff,          zargse,      0, symtab );
   inst_c( "plnl",            NodeList_plnl,           zargse,      0, symtab );
   inst_c( "plnloff",         NodeList_plnloff,        zargse,      0, symtab );
   inst_c( "blocks",          Blocks_parse,            zargse,      0, symtab );
   inst_c( "name",            ObjectName_input,        zargse,      0, symtab );
   inst_c( "mpi_edit",  mpi_edit,  zargse,  0, symtab );
   RGST_ADD_OBJECT_ATTR( "mpi_edit",  "edit_function" );
   inst_c( "query_timer", query_timer, zargse, 0, symtab );
   RGST_ADD_OBJECT_ATTR( "query_timer",  "edit_function" );
   inst_c( "reg",             region_edit,             zargse,      0, symtab );
   RGST_ADD_OBJECT_ATTR( "reg",            "edit_function" );
   inst_c( "eval",            eval,                    zargse,      0, symtab );
   RGST_ADD_OBJECT_ATTR( "eval",           "edit_function" );
   inst_c( "walltime",        walltime,                zargse,      0, symtab );
   RGST_ADD_OBJECT_ATTR( "walltime",       "edit_function" );
   inst_c( "timestep",        TimeStepControl_getvalue,zargse,      0, symtab );
   RGST_ADD_OBJECT_ATTR( "timestep",       "edit_function" );
   
   
   inst_c( "src",             srcin,                   sargs,       0, symtab );
   inst_c( "regedit",         regedit,                 sargs,       1, symtab );
   inst_c( "blkdiv",          blkdivin,                sargs,       0, symtab );
   inst_c( "axis",            Transform_set,           sargs,       0, symtab );
   inst_c( "norm",            Transform_set,           sargs,       1, symtab );
   inst_c( "cent",            Transform_set,           sargs,       2, symtab );
   inst_c( "pc_rad",          Transform_getpolar,      sargs,       0, symtab );
   inst_c( "pc_theta",        Transform_getpolar,      sargs,       1, symtab );
   inst_c( "pc_phi",          Transform_getpolar,      sargs,       2, symtab );
   inst_c( "spln_dep",        spline_getvalues,        sargs,       0, symtab );
   inst_c( "spln_x",          spline_getvalues,        sargs,       1, symtab );
   inst_c( "spln_y",          spline_getvalues,        sargs,       2, symtab );
   inst_c( "spln_r",          spline_getvalues,        sargs,       3, symtab );
   inst_c( "spln_t",          spline_getvalues,        sargs,       4, symtab );
   inst_c( "spln_xy",         spline_getvalues,        sargs,       5, symtab );
   inst_c( "spln_rt",         spline_getvalues,        sargs,       6, symtab );
   RGST_ADD_OBJECT_ATTR( "spln_dep",     "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_x",       "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_y",       "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_r",       "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_t",       "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_xy",      "edit_function" );
   RGST_ADD_OBJECT_ATTR( "spln_rt",      "edit_function" );
   RGST_ADD_OBJECT_ATTR( "pc_rad",       "edit_function" );
   RGST_ADD_OBJECT_ATTR( "pc_theta",     "edit_function" );
   RGST_ADD_OBJECT_ATTR( "pc_phi",       "edit_function" );
   inst_c( "quad",            blockin0,                sargse, QUAD2D, symtab );
   inst_c( "hex",             blockin0,                sargse,  HEX3D, symtab );
   inst_c( "clear",           memclr_input,            sargse,      0, symtab );
   inst_c( "redeck",          memclr_input,            sargse,      1, symtab );
   inst_c( "point",           meshgen_input,           sargse,      0, symtab );
   inst_c( "line",            meshgen_input,           sargse,      1, symtab );
   inst_c( "fill",            meshgen_input,           sargse,      2, symtab );
   inst_c( "vpoint",          meshgen_input,           sargse,      3, symtab );
   inst_c( "vline",           meshgen_input,           sargse,      4, symtab );
   inst_c( "vfill",           meshgen_input,           sargse,      5, symtab );
   inst_c( "maxvar",          reducevar,               sargse,      0, symtab );
   inst_c( "minvar",          reducevar,               sargse,      1, symtab );
   inst_c( "avevar",          reducevar,               sargse,      2, symtab );
   inst_c( "avevvar",         reducevar,               sargse,      3, symtab );
   inst_c( "avemvar",         reducevar,               sargse,      4, symtab );
   inst_c( "sumvar",          reducevar,               sargse,      5, symtab );
   RGST_ADD_OBJECT_ATTR( "maxvar",      "edit_function" );
   RGST_ADD_OBJECT_ATTR( "minvar",      "edit_function" );
   RGST_ADD_OBJECT_ATTR( "avevar",      "edit_function" );
   RGST_ADD_OBJECT_ATTR( "avevvar",     "edit_function" );
   RGST_ADD_OBJECT_ATTR( "avemvar",     "edit_function" );
   RGST_ADD_OBJECT_ATTR( "sumvar",      "edit_function" );
   inst_c( "normvec",         gnorm,                   sargse,      0, symtab );
   inst_c( "vnormvec",        gnorm,                   sargse,      1, symtab );
   inst_c( "freq",            fqcyc,                   sargse,      1, symtab );
   inst_c( "do",              fqcyc,                   sargse,      1, symtab );
   inst_c( "cyc",             fqcyc,                   sargse,      0, symtab );
   inst_c( "timeplot",        fqcyc,                   sargse,      2, symtab );
   inst_c( "cycleplot",       fqcyc,                   sargse,      3, symtab );
   inst_c( "plot",            plot,                    sargse,      2, symtab );
   inst_c( "tplot",           tplot,                   sargse,      2, symtab );
   inst_c( "curprod",         curbop,                  sargse,      1, symtab ); 
   inst_c( "curdiv",          curbop,                  sargse,      2, symtab ); 
   inst_c( "cursum",          curbop,                  sargse,      3, symtab ); 
   inst_c( "curdif",          curbop,                  sargse,      4, symtab );
   inst_c( "wrtx",            curwrtxy,                sargse,      1, symtab );
   inst_c( "wrty",            curwrtxy,                sargse,      2, symtab );
   inst_c( "getx",            curgetxy,                sargse,      1, symtab );
   inst_c( "gety",            curgetxy,                sargse,      2, symtab );
   inst_c( "def",             gpdef,                   sargse,      0, symtab );
   inst_c( "kdef",            gpdef,                   sargse,     -1, symtab );
   inst_c( "ldef",            gpdef,                   sargse,      1, symtab );
   inst_c( "species",         species_input,           sargse,     -1, symtab );
   inst_c( "when",            conditionals_input,      sargse,      0, symtab );
   inst_c( "once",            conditionals_input,      sargse,      1, symtab );
   inst_c( "atexit",          conditionals_input,      sargse,      2, symtab );
   return(0);
}
