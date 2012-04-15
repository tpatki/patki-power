#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
#include "irsctl.h"
#include <unistd.h>
#include <errno.h>
extern int errno ;
extern char **environ ;
extern pid_t waitpid( pid_t pid, int *status, int options ) ;
int SystemWrapper( void )
{
   char command[MAXLINE], msg[MAXLINE] ;
   char *me = "SystemWrapper" ;
   int j, ierr = 0, pid, status ;
   if ( myid == 0 ) {
      if ( ps == NULL) {
         sprintf( msg, "No argument given to system command." ) ;
         ctlwarning( me, msg ) ;
         return( 0 ) ;
      }
      if ( *ps != '\"' ) {
         sprintf( msg, "Command string must be in quotes." ) ;
         ctlwarning( me, msg ) ;
         return( 0 ) ;
      }
      *ps++ ;
      j = 0 ;
      while ( (j != MAXLINE) && (*ps != '\0') && (ps != NULL) && (*ps != '\"') ) { 
         command[j++] = *ps ;
         *ps++ ;
      }
      command[j] = '\0' ;
      if ( *ps == '\"' ) {
         *ps++ ;
      } else {
         sprintf( msg, "Hit end of line without finding close quote in system." ) ;
         ctlwarning( me, msg ) ;
         return( 0 ) ;
      } 
      pid = vfork() ;
      if ( pid == -1 ) {
         sprintf( msg, "Failed to fork process from system command." ) ;
         ctlwarning( me, msg ) ;
      }
      if ( pid == 0 ) {
         char *argv[4] ;
         argv[0] = "sh" ;
         argv[1] = "-c" ;
         argv[2] = command ;
         argv[3] = 0 ;
         ierr = execve( "/bin/sh", argv, environ ) ;
         exit(127) ;
      }
      if ( ierr != 0 ) {
         sprintf( msg, "Command '%s' failed with error %d.", command, ierr ) ;
         ctlnotice( me, msg ) ;
      }
      do {
         if (waitpid(pid, &status, 0) == -1) {
	    if ( errno != EINTR ) {
            return( -1 ) ;
	    }
         } else {
            return( status ) ;
	 }
      } while( 1 ) ;
   }
   return( 0 ) ;
}
