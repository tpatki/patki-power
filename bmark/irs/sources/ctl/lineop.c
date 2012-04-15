#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "FunctionTimer.h"
#include "irscom.h"
#ifdef READLINE
#include <readline.h>
extern void add_history (char *);
extern char *readline(char *);
extern char **completion_matches( char *, char *(*func)(char *, int) );
#endif
static char * * lineop_completion(char *text, int start, int end);
static char *   lineop_command_search(char *text, int state);
static char *   lineop_fgets(char *str, int num, FILE *stream, char *fullprompt);
int lineop_grab( char **buffer, char *stopstring, char *myps) {
   char *me = "lineop_grab";
   char *ps2;
   char *lnpt;
   char msg[MAXLINE];
   char myline[MAXLINE];
   char fullprompt[24];
   int i,j;
   int nlines;
   int nchars;
   int nchars2;
   int nlchars;
   int lcount;
   int endmsg;
   int count;
   FILE *fpfq = NULL;
   ifexp   = 0;
   ifcomfg = 0;
   if (myid == 0) {
      if ((fpfq = fopen("fqfile", "w+")) == NULL) {
         sprintf(msg,"Can't open fqfile"); 
         ctlerror(me,msg);
      }
   }
   nlines = 0;
   nchars = 0;
   lcount = 0;
   endmsg = 0;
   ps2 = myps;
   count = 0;
   while (endmsg == 0) {
      if (lastfile == 0) {
         if (ifhilite) {
            sprintf(fullprompt, YELOTXT "msg: " NRMLTXT) ;
         } else {
            sprintf(fullprompt, "msg: ") ;
         }
      }
      if ((myps == NULL) || ((myps != NULL) && (count > 0))) {
         if (lineop_get(line, MAXLINE, fpin, fullprompt) == NULL) {
            sprintf(msg,"\n\tMissing '%s' in following msg" "\n\t%s",stopstring,line);
            ctlnotice(me,msg);
            strcpy(sym, "done") ;
            return(-1);
         }
         ps2 = line;
      }
      i = 0;
      while ((*ps2 != '\0') && (*ps2 != '\n')) {
         myline[i++] = *ps2;
         if (*ps2 == '{') ifexp = 1;
         if (*ps2 == '}') ifexp = 0;
         if ((*ps2 == '*') && (ifexp == 0)) {
             i--;
             while ((*ps2 != '\0') && (*ps2 != '\n')) ps2++;
         }
         if ((*ps2 != '\0') && (*ps2 != '\n')) ps2++;
      }
      myline[i++] = *ps2;
      ps2++;
      nchars2 = i;
      if (nchars2 > 0) {
         myline[nchars2-1] = '$' ;
         myline[nchars2  ] = '\n' ;
         myline[nchars2+1] = '\0' ;
         nchars2++;
         if (fpout != NULL) {
            PRINT(fpout, "%s", myline) ;
         }
         if (myline[0] != '*') {
            ps = myline ;
            while ((ps != NULL) && (*ps != '\0')) {
               getsym() ;
               if (!strcmp(sym, stopstring)) {
                  endmsg = 1 ;
                  break ;
               }
            }   
            nlines++ ;
            nchars = nchars + nchars2 ;
            if (myid == 0) {
               PRINT(fpfq, "%s", myline) ;
            }
         }   
      }   
      count++;
   }   
   if (myid == 0) {
      rewind(fpfq) ;
   } 
   nchars = nchars + 16 ;
   *buffer = ALLOT(char, nchars);
   lnpt = *buffer;
   lcount = 0;
   for (i = 1; i <= nlines; i++) {
     lineop_get(myline, MAXLINE, fpfq, "") ;
     nlchars = strlen(myline) ;
     for ( j = 0 ; j < nlchars ; j++ ) { 
        lnpt[lcount++] = myline[j] ; 
     }
   }
   if (myid == 0) {
      fclose(fpfq);
   }
   ifexp   = 1;
   ifcomfg = 1;
   return(nchars);
}
char *lineop_get(char *str, int num, FILE *stream, char *fullprompt) {
   char *retstr;
   if (myid==0) {
      retstr = lineop_fgets(str, num, stream, fullprompt);
      if ( retstr == NULL ) strcpy(str, "\0");
   }
   if (ifparallel) {
      combcast(str, num, COM_CHAR, 0);
      if (myid!=0) {
         if ( strcmp(str, "\0") ) {
            retstr = str;
         } else {
            retstr = NULL;
         }
      }
   } 
   return(retstr);
}
static char *lineop_fgets(char *str, int num, FILE *stream, char *fullprompt) {
#ifdef READLINE
   char *line_read = (char *) NULL ;
   char *cmnd_read = (char *) NULL ;
   if (stream == stdin) {
      line_read = readline(fullprompt) ; 
      cmnd_read = line_read;  
      if (line_read) {
         while ((*cmnd_read == ' ') || (*cmnd_read == '\t')) cmnd_read++ ;
         if (*cmnd_read) {
            add_history(cmnd_read) ;
            strncpy(str, cmnd_read, num-2) ;
            str[num-2] = '\0' ;
            strcat(str, "\n") ;
         } else {
            strcpy(str, "\0");
         }
         FREEMEM(line_read) ;  
      } else {
         str = NULL;
      }
   } else {
      str = fgets(str, num, stream) ;  
   }
#else
   if (stream == stdin) {
      PRINT(stdout, "%s", fullprompt) ;
#ifdef aix
      PRINT(stdout, "\n");
#endif
      fflush(stdout);
   }
   str = fgets(str, num, stream) ;  
#endif
   return(str) ;
}
#define LINEOP_STACKMAX 256
typedef struct {
   int   len;
   char *line;
} LineOpStack_t;
static LineOpStack_t lineop_stack[LINEOP_STACKMAX];
static int lineop_stack_ptr = 0;
static int pdmd_save;
void lineop_push( void ) {
    char *me = "lineop_push";
    char msg[MAXLINE];
    int len;
    if (lineop_stack_ptr == LINEOP_STACKMAX - 1) {
       sprintf(msg,"Stack overflow:  Too many attempts to re-direct input.  Punting last one.");
       ctlwarning(me,msg);
       lineop_stack_ptr--;
    }
    if (ps != NULL) {
       len = strlen(ps);
    } else {
       len = 0;
    } 
    lineop_stack[lineop_stack_ptr].len  = len;
    if (lineop_stack[lineop_stack_ptr].len > 0) {
       lineop_stack[lineop_stack_ptr].line = ALLOT(char, len + 1);
       strcpy(lineop_stack[lineop_stack_ptr].line,ps);
    }
    lineop_stack_ptr++;
    pdmd_save = pdmd;
    pdmd = 0;
    lnbuf[0] = '\0';
    line = lnbuf;
    ps = NULL;
}
void lineop_pop( void ) {
    static int bufsize = MAXLINE;
    if (lineop_stack_ptr == 0) return;
    lineop_stack_ptr--;
    if (lineop_stack[lineop_stack_ptr].len > 0) {
       if (lineop_stack[lineop_stack_ptr].len+1 > bufsize ) {
          REALLOT(lnbuf, char, lineop_stack[lineop_stack_ptr].len+1);
          bufsize = lineop_stack[lineop_stack_ptr].len+1;
       }
       strcpy(lnbuf,lineop_stack[lineop_stack_ptr].line);
       FREEMEM(lineop_stack[lineop_stack_ptr].line);
       line = lnbuf;
       ps = line;
    } else {
       ps = NULL;
    } 
    pdmd = pdmd_save;
}
void lineop_init_readline(void) {
#ifdef READLINE
   rl_attempted_completion_function = (CPPFunction *) lineop_completion;
#endif
}
static char **lineop_completion( char *text, int start, int end ) {
   char **matches = NULL;
#ifdef READLINE
   if (start == 0) {
      matches = completion_matches( text, lineop_command_search );
   }
#endif
   return( matches );
}
static char *lineop_command_search( char *text, int state ) {
   static int i, j, len;
   static HashTable_t **htp;
   static HashTable_t *ht;
   static HashElm_t *next;
   char *command;
#define OTHRCMDSLEN 4
   char *othercmds[OTHRCMDSLEN] = { "end", "quit", "run", "endmsg" };
   if (!state) {
      htp = (HashTable_t **) rgst_get_t("symbols","HashTable_t *");
      ht = *htp;
      i = 0;
      j = 0;
      next = ht->tbl[0];
      len = strlen( text );
   }
   while (i < ht->size) {
      while (next != NULL) {
         if (strncmp(next->name, text, len) == 0) {
            command = MALLOT( char, strlen(next->name) + 1);
            strcpy( command, next->name );
            next = next->next;
            return( command );
         }
         next = next->next;
      }
      i++;
      next = ht->tbl[i];
   }
   while (j < OTHRCMDSLEN) {
      if (strncmp(othercmds[j], text, len) == 0) {
         command = MALLOT( char, strlen(othercmds[j]) + 1);
         strcpy( command, othercmds[j] );
         j++;
         return( command );
      }
      j++;
   }
   return( (char*) NULL );
}
