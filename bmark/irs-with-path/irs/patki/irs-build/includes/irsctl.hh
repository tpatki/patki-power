#ifndef irsctl_H
#define irsctl_H

#include "Rgst.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/
#ifdef MSC
int vcprint();
#endif

#define TO_STACK        0
#define TO_SCREEN       1

/* define external i/o data needed */
 
/* local variables */

#define MAXFILE   		50
#define NTIMES_INCREMENT	64

/* #define PRNTCPU */

/* define TERMFLG_ vars in order of precedence to establish the way to */
/* determine accepted value (highest) when multiple commands performed */
/* during same cycle (conditionals) each issue a returned TERMFLG_ val */
#define TERMFLG_CHECK   -1
#define TERMFLG_READY    0
#define TERMFLG_RUN      1
#define TERMFLG_USERSTOP 2
#define TERMFLG_CSTOP    3
#define TERMFLG_TSTOP    4
#define TERMFLG_TIME     5
#define TERMFLG_EXIT     6
#define TERMFLG_ERROR    7

/* VT100 Terminal ESC sequences for text highlights */
#define NRMLTXT "\033[0m"
#define YELOTXT "\033[1m"
#define RED_TXT "\033[2m"
#define UNDRTXT "\033[4m"
#define INVSTXT "\033[7m"

#ifdef aix
/* sp2 (parll) indents msgs to include proc # on msg line, print fewer dashes */
#define ERROR_LINE "\n%s------------------------------- E R R O R --------------------------------%s\n"
#define WARN_LINE  "\n%s----------------------------- W A R N I N G ------------------------------%s\n"
#define DASH_LINE      "--------------------------------------------------------------------------\n"
#else
#define ERROR_LINE "\n%s--------------------------------- E R R O R ----------------------------------%s\n"
#define WARN_LINE  "\n%s------------------------------- W A R N I N G --------------------------------%s\n"
#define DASH_LINE      "------------------------------------------------------------------------------\n"
#endif

#define PROC_LINE      "+++ Procedure: %s\n"
#define MSG_LINE       "+++ Error Msg: %s\n"
#define MSG2_LINE      "+++          : %s\n+++          : %s\n"

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
char * lineop_get(char *str, int num, FILE *stream, char *fullprompt);
double getf(int *cflag);
double getnxtm(void);
int SystemWrapper(void);
int irspcs_check(void);
int ctlecho(void);
int ctloutput(char *routine, char *label, RGST_Datatype_t type, ...);
int domsg(void);
int endfile(void);
int eval(void);
int exit_cleanup(void);
int fqcyc(int fcflag);
int delfq(void);
int geta_leftparen(void);
int geta_rightparen(void);
int getflst(double * *datain, int inlen);
int getfq(int *msgtype, int *msgnum);
int geti(int *cflag);
int getnxcy(void);
int gpdef(int gptype);
int gpdef0(int gptype, char *newsym, char *newval);
int ifnotin(char *d, char *ps);
int lfchk(void);
int lineop_grab(char * *buffer, char *stopstring, char *myps);
int lnadv(char *lnout, char *msg, int msglen, int *count);
int main(int argc, char * *argv);
int newfile(char *filename, int errflag);
int printdate(void);
int printmap(void);
int printmsg(int msgtype, int msgnum);
int printtc(void);
int prirup(void);
int redofq(void);
int run(void);
int showfq(void);
int step(void);
int walltime(void);
void irspcs_register(void);
void cpuse(void);
void ctlerror(char *proc_name, char *msg);
void ctlmsg(char *msg);
void ctlmsg1(char *msg);
void ctlnotice(char *proc_name, char *msg);
void ctlwarning(char *proc_name, char *msg);
void endout(void);
void expressions_eval(char *string);
void expressions_init(void);
void geta(char *s);
void geta_discard(int verbose);
void getsym(void);
void getversion(void);
void initget(void);
void lineop_init_readline(void);
void lineop_pop(void);
void lineop_push(void);
void newline(void);
void noop(int noarg);
void nxtsym(int ifadvance);
void outfile(char *filename);
void parmsym(void);
void pd_init(void);
void peekc(char *s);
void peekc2(char *s);
void printhelp(void);
void printrc(void);
void pversion(void);
void resetio(void);
void resetmsg(void);
void setiomrk(char *string, int nlen);
void setirup(int i);
void setup_attrs(void);
void unsetio(void);
void userexitfn(int (*fn_ptr)(void));

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

HashTable_t *symtab;
 
FILE *fpin;
FILE *fpold[MAXFILE];
 
char inputDeck[MAXLINE];
char *lnbuf =  NULL ;
char sym[MAXLINE];
char *ps =  NULL ;
char *line =  NULL ;
char *iomrkstr =  NULL ;
char *iomrkps =  NULL ;
char nospace[64];
char delim[64];
char prompt[24];

int ifdofq;
int ifdocy;
int lastfile;
int ifecho;
int iflf;
int symflag;
int ctlflag;
int iomrkflag;
int iomrkrset;
int ifcomfg ;
int ifexp ;
int do_just_one_command =  FALSE ;

int output_dest =  TO_SCREEN ;

int iplusmin;
int ifplusmin;
int ifparm ;

int pccsflag;
int pccsoff;

int sp2_dont_run_flag =  FALSE ;
int sp2_seq_run_flag =  FALSE ;

double runtime_max =  -1.0 ;

/*------------------------------------------------------------------------------
-
- ctlerror_already_called
-   is a flag used by the abort routines to ensure that only the first call
-   to abort is processed.
-
- user_exit_fn
-   is a pointer to a user-supplied function to be called by the error routine
-   before the program ends.  This function gives the user a chance to
-   close files, and do other things that may be needed to end the program
-   nicely.
-
------------------------------------------------------------------------------*/
int ctlerror_already_called  =  FALSE ;

int (*user_exit_fn) (void)  =  NULL  ;

/*------------------------------------------------------------------------------
- timing scalars
- 
- runcpu  - updated in xirs() to track the cpu used in the physics routines
- delcyc  - delta cycle, how many cycles the code ran
  
------------------------------------------------------------------------------*/
double runcpu  =  0.0 ;
int    delcyc  =  0 ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
