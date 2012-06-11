#include "irs.h"
#include "irsgenrd.h"
static int command_info( char *request );
static void help( char *command_name, char *alt_name, char *request, int *found,
           char *info );
int input_command_help( void )
{
   char *me = "input_command_help";
   char op[MAXWORD] ;
   int found;
   if ( !lfchk() ) {
      geta(op);
      if ( ! command_info( op ) ) {
         printf("No basic info for '%s' available from the command line yet,"
                "\ncheck the online HTML docs or manual for any info.\n",op);
      }
   } else {
      printf("\nBasic command-line commands:\n");
      printf("   run, stop, wdmp, quit, reset, regen, print, set\n");
      printf("('help <cmd>' provides more info on these & other commands)\n\n");
   }
   return(0);
}
static int command_info( char *request ) {
   int found = 0;
   help( "help",       "h",          request, &found,
   "followed by a command gives help info on the specified command,"
   "\n""or by itself gives a list of the most common basic commands");
   help( "run",        "",           request, &found,
   "continues problem execution");
   help( "stop",       "",           request, &found,
   "pauses problem execution");
   help( "wdmp",       "",           request, &found,
   "writes a dump of the current execution state to disk");
   help( "quit",       "end",        request, &found,
   "terminates program execution");
   help( "print",      "",           request, &found,
   "describes command line print options");
   help( "set",        "",           request, &found,
   "assigns a specified value to a specified parameter");
   return( found );
}
static void help( char *command_name, char *alt_name, char *request, int *found,
                  char *info )
{
   if ( (!strcmp(request, command_name)) || (!strcmp(request, alt_name)) ) {
      printf("\nHELP: '%s'",command_name);
      if (strcmp(alt_name, "")) printf(" or '%s'",alt_name);
      printf("\n%s\n\n",info);
      *found = 1;
   }
}
