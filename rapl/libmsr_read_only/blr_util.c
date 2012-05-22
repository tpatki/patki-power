#include <stdlib.h>		// mkstmp, getenv
#include <unistd.h>		// close
#include "blr_util.h"

double 
ts_delta(struct timeval *start, struct timeval *stop){
	return (stop->tv_sec + stop->tv_usec/1000000.0) - (start->tv_sec + start->tv_usec/1000000.0);
}

FILE *
safe_mkstemp( const char *filetag ){
	FILE *f;
	int fd=-1;
	char filename[4097];	
	if ( filetag == NULL ){
		filetag = "rapl_tick";
	}
	sprintf(filename, "%s__XXXXXXXX", filetag);
	fd=mkstemp(filename);
	if(fd==-1){
		fprintf(stderr, "%s::%d  Error opening %s for reading.\n", __FILE__, __LINE__, filename);
		return NULL;
	}
	close(fd);
	f = fopen(filename, "w");
	return f;
}

void get_env_int(const char *name, int *val){
	char *str;
	str = getenv(name);
	*val = (int) strtol(str, (char **)NULL, 0);
}

	