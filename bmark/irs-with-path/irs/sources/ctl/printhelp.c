#include "irs.h"
void printhelp(void) 
{
   PRINT(stdout,"\nusage: %s [-h] [-k KERNEL] [-d DUMP] [DECK]\n\n",codename);
   PRINT(stdout,"CAPS indicates user input\n\n");
   PRINT(stdout,"[-c CYCLE]   condense all dump files from cycle"
                " CYCLE to one dump\n");
   PRINT(stdout,"[-cg CYCLE]  condense all graphics dump files from"
                " cycle CYCLE to one dump\n");
   PRINT(stdout,"[-cx CYCLE]  condense all x-ray dump files from cycle"
                " CYCLE to one dump\n");
   PRINT(stdout,"[-d DUMP]    read dump DUMP, default none\n");
   PRINT(stdout,"[-d [last | lastwith KERNEL] ]   read last dump\n");
   PRINT(stdout,"[-dm KERNEL-CYCLE]   read multiple dumps\n");
   PRINT(stdout,"[-dm [last | lastwith KERNEL] ]  read last multiple dump\n");
   PRINT(stdout,"[-fam]       write re-start files as directory families\n");
   PRINT(stdout,"[-help]      display this menu\n");
   PRINT(stdout,"[-k KERNEL]  set problem kernel to KERNEL, default is %s\n",
                codename);
   PRINT(stdout,"[-nbaton NUMBER]  let no more than NUMBER procs"
                " read/write at once\n");
   PRINT(stdout,"[-nd NUMBER] split output dump files into NUMBER files\n");
   PRINT(stdout,"[-o PATH]    set path for all output files\n");
   PRINT(stdout,"[-r ]        imediately run input deck or restart,"
                " exit when done\n");
   PRINT(stdout,"[-runtime TIME]  specify the run time in minutes\n"); 
   PRINT(stdout,"[-merge]     run in merge mesh mode\n");
   PRINT(stdout,"[-threads ]  run with threads\n");
   PRINT(stdout,"[-v ]        print out code version information \n");
   PRINT(stdout,"[-warn  TIME ]  specify that you want a shutdown warning"
                " from DPCS where TIME is in minutes\n");
   PRINT(stdout,"[-debug ]    run with debug flag set\n");
   PRINT(stdout,"[-def flag=value]    define a variable named flag and asign it value\n");
   PRINT(stdout,"[DECK]       read input DECK, default none\n\n");

   PRINT(stdout,"[-child_out_off]    Turn off stdout and stderr files mpi processes other than rank 0\n\n");
   PRINT(stdout,"[-child_outpath /path/to/dir]  Send child io files to this directory\n\n");
}
