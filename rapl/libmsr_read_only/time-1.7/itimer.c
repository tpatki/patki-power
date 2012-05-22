#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include "itimer.h"
#include "../msr_rapl.h"

static void
handler(int sig, siginfo_t *si, void *unused){
	rapl_tick(NULL);
}

int
setup_itimer(){
	int rc;
	struct itimerval itimerval;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	if( sigaction(SIGALRM, &sa, NULL )){
		fprintf(stderr,"sigaction up and died.\n");
	}

	itimerval.it_interval.tv_sec=0;
	itimerval.it_interval.tv_usec=100000;
	itimerval.it_value.tv_sec=0;
	itimerval.it_value.tv_usec=100000;

	rc = setitimer(ITIMER_REAL, &itimerval, NULL);
}

	
