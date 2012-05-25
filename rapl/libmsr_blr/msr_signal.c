#include "msr_signal.h"
#include "msr_core.h"
#include "msr_rapl.h"
#include "msr_turbo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static sig_atomic_t in_handler = 0;

void handle_sig(int signum)
{
	//Don't usr printf in a sig handler. This is just for my testing for now. 
	
//	printf("\nProcess %d got signal %d\n", getpid(), signum);

	//Basically, do nothing if the in_handler is 1. This means someone else is
	//Running a signal handler too. And they will exit appropriately
	//from the application
	//If you're the first person in there who needs to fix the mess
	//You restore the registers and exit. You don't need to set the in_handler to 0 again,
	//Because you are eventually terminating the program and no one else but you is in the signal handler.
	//A naive version of mutual exclusion, I suppose
	
	//The reason this check is required is to avoid multiple segfaults leading to
	//non-deterministic behavior, and to be able to run our non-reentrant unsafe 
	//library code as safely as possible.
	
	if(in_handler == 0)
		restore_registers(); 

	//You should never reach this point.
	
	printf("\n \n In handle_sig: this is bad. If you're here, your exit call failed. ");
}

void register_sig()
{
	signal(SIGSEGV, handle_sig);
	signal(SIGKILL, handle_sig);
}

void restore_registers()
{	 
	int package;
        
       // Reset all limits.
	for(package=0; package<NUM_PACKAGES; package++){
             write_msr( package, MSR_PKG_POWER_LIMIT, 0x6845000148398 );
                   /*
                     write_msr( package, MSR_PP0_POWER_LIMIT, 0 );
                     #ifdef ARCH_062D
                         write_msr( package, MSR_DRAM_POWER_LIMIT, 0 );
                     # endif
            */ // These are currently locked out.
	 
	    //Disable turbo boost
	     disable_turbo(package); 
	}                     

	//The call to finalize_msr() closes files, not sure if I need it. We shall see. 
//        finalize_msr();

	//Now exit. 
         _exit(EXIT_FAILURE);

}
