#ifndef irsctl_H
#define irsctl_H

#include "Rgst.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/
#ifdef MSC
extern int vcprint();
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
extern char * lineop_get(char *str, int num, FILE *stream, char *fullprompt);
extern double getf(int *cflag);
extern double getnxtm(void);
extern int SystemWrapper(void);
extern int irspcs_check(void);
extern int ctlecho(void);
extern int ctloutput(char *routine, char *label, RGST_Datatype_t type, ...);
extern int domsg(void);
extern int endfile(void);
extern int eval(void);
extern int exit_cleanup(void);
extern int fqcyc(int fcflag);
extern int delfq(void);
extern int geta_leftparen(void);
extern int geta_rightparen(void);
extern int getflst(double * *datain, int inlen);
extern int getfq(int *msgtype, int *msgnum);
extern int geti(int *cflag);
extern int getnxcy(void);
extern int gpdef(int gptype);
extern int gpdef0(int gptype, char *newsym, char *newval);
extern int ifnotin(char *d, char *ps);
extern int lfchk(void);
extern int lineop_grab(char * *buffer, char *stopstring, char *myps);
extern int lnadv(char *lnout, char *msg, int msglen, int *count);
extern int main(int argc, char * *argv);
extern int newfile(char *filename, int errflag);
extern int printdate(void);
extern int printmap(void);
extern int printmsg(int msgtype, int msgnum);
extern int printtc(void);
extern int prirup(void);
extern int redofq(void);
extern int run(void);
extern int showfq(void);
extern int step(void);
extern int walltime(void);
extern void irspcs_register(void);
extern void cpuse(void);
extern void ctlerror(char *proc_name, char *msg);
extern void ctlmsg(char *msg);
extern void ctlmsg1(char *msg);
extern void ctlnotice(char *proc_name, char *msg);
extern void ctlwarning(char *proc_name, char *msg);
extern void endout(void);
extern void expressions_eval(char *string);
extern void expressions_init(void);
extern void geta(char *s);
extern void geta_discard(int verbose);
extern void getsym(void);
extern void getversion(void);
extern void initget(void);
extern void lineop_init_readline(void);
extern void lineop_pop(void);
extern void lineop_push(void);
extern void newline(void);
extern void noop(int noarg);
extern void nxtsym(int ifadvance);
extern void outfile(char *filename);
extern void parmsym(void);
extern void pd_init(void);
extern void peekc(char *s);
extern void peekc2(char *s);
extern void printhelp(void);
extern void printrc(void);
extern void pversion(void);
extern void resetio(void);
extern void resetmsg(void);
extern void setiomrk(char *string, int nlen);
extern void setirup(int i);
extern void setup_attrs(void);
extern void unsetio(void);
extern void userexitfn(int (*fn_ptr)(void));

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

extern HashTable_t *symtab;
 
extern FILE *fpin;
extern FILE *fpold[MAXFILE];
 
extern char inputDeck[MAXLINE];
extern char *lnbuf;		/* HH_INIT NULL */
extern char sym[MAXLINE];
extern char *ps;		/* HH_INIT NULL */
extern char *line;		/* HH_INIT NULL */
extern char *iomrkstr;		/* HH_INIT NULL */
extern char *iomrkps;		/* HH_INIT NULL */
extern char nospace[64];
extern char delim[64];
extern char prompt[24];

extern int ifdofq;
extern int ifdocy;
extern int lastfile;
extern int ifecho;
extern int iflf;
extern int symflag;
extern int ctlflag;
extern int iomrkflag;
extern int iomrkrset;
extern int ifcomfg ;
extern int ifexp ;
extern int do_just_one_command; /* HH_INIT FALSE */

extern int output_dest;         /* HH_INIT TO_SCREEN */

extern int iplusmin;
extern int ifplusmin;
extern int ifparm ;

extern int pccsflag;
extern int pccsoff;

extern int sp2_dont_run_flag;		/* HH_INIT FALSE */
extern int sp2_seq_run_flag;		/* HH_INIT FALSE */

extern double runtime_max; 		/* HH_INIT -1.0 */

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
extern int ctlerror_already_called ;       /* HH_INIT FALSE */

extern int (*user_exit_fn) (void) ;        /* HH_INIT NULL  */

/*------------------------------------------------------------------------------
- timing scalars
- 
- runcpu  - updated in xirs() to track the cpu used in the physics routines
- delcyc  - delta cycle, how many cycles the code ran
  
------------------------------------------------------------------------------*/
extern double runcpu ;  /* HH_INIT 0.0 */
extern int    delcyc ;  /* HH_INIT 0 */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
