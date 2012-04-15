#include "irs.h"
#include "irsgen.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "AEStackElm.h"
#include "Command.h"
#include "Rgst.h"
#define EXP_PLUS   0
#define EXP_MINUS  1
#define EXP_MULT   2
#define EXP_DIVIDE 3
#define EXP_POWR   4
#define EXP_NEG    5
#define EXP_SQRT   6
#define EXP_SIN    7
#define EXP_COS    8
#define EXP_TAN    9
#define EXP_ASIN  10
#define EXP_ACOS  11
#define EXP_ATAN  12
#define EXP_EXP   13
#define EXP_LOG   14
#define EXP_FABS  15
#define EXP_MAX   16
#define EXP_MIN   17
#define EXP_RAN   18
#define EXP_INT   19
#define EXP_OR    20
#define EXP_AND   21
#define EXP_GT    22
#define EXP_GTE   23
#define EXP_LT    24
#define EXP_LTE   25
#define EXP_EQ    26
#define EXP_NE    27
#define EXP_NOT   28
#define EXP_MOD   29
#define EXP_NFUN 30
#define EXP_NREG 20
#define EXP_NEWFUN(xname,xtype,xmode,xnarg,xprec) \
   strcpy(funlist[nfun].name,xname) ; \
   funlist[nfun].type = xtype ; \
   funlist[nfun].mode = xmode ; \
   funlist[nfun].narg = xnarg ; \
   funlist[nfun].prec = xprec ; \
   nfun++ ;
static int    curOp ;
static int    lop ;
static int    nest ;
static int    nfun ;
typedef struct {
   double op;
   int    pendOp;
   int    nestLevel;
   int    precLevel;
} EXP_OPERAND;
static EXP_OPERAND operand[EXP_NREG];
typedef struct {
   char name[20] ;
   int  type ;
   int  mode ; 
   int  narg ;
   int  prec ;
 } EXP_FUNCTION;
static EXP_FUNCTION funlist[EXP_NFUN];
static void expressions_check(char *sym) ;
static int  expressions_isfun(char *op) ;
static void expressions_xop( int prec ) ;
void expressions_init( void ) {
   nfun = 0 ;
   EXP_NEWFUN("+",EXP_PLUS  ,2,2,4) ;
   EXP_NEWFUN("-",EXP_MINUS ,2,2,4) ;
   EXP_NEWFUN("*",EXP_MULT  ,2,2,6) ;
   EXP_NEWFUN("/",EXP_DIVIDE,2,2,6) ;
   EXP_NEWFUN("%",EXP_MOD   ,2,2,6) ;
   EXP_NEWFUN("^",EXP_POWR  ,2,2,8) ;
   EXP_NEWFUN("==",EXP_EQ  ,2,2,9) ;
   EXP_NEWFUN("!=",EXP_NE  ,2,2,9) ;
   EXP_NEWFUN(">",EXP_GT  ,2,2,9) ;
   EXP_NEWFUN(">=",EXP_GTE  ,2,2,9) ;
   EXP_NEWFUN("<",EXP_LT  ,2,2,9) ;
   EXP_NEWFUN("<=",EXP_LTE  ,2,2,9) ;
   EXP_NEWFUN("|",EXP_OR  ,2,2,9) ;
   EXP_NEWFUN("&",EXP_AND  ,2,2,9) ;
   EXP_NEWFUN("~",EXP_NEG   ,1,1,10) ;
   EXP_NEWFUN("!",EXP_NOT   ,1,1,10) ;
   EXP_NEWFUN("sqrt",EXP_SQRT,1,1,10) ;
   EXP_NEWFUN("sin",EXP_SIN,1,1,10) ;
   EXP_NEWFUN("cos",EXP_COS,1,1,10) ;
   EXP_NEWFUN("tan",EXP_TAN,1,1,10) ;
   EXP_NEWFUN("asin",EXP_ASIN,1,1,10) ;
   EXP_NEWFUN("acos",EXP_ACOS,1,1,10) ;
   EXP_NEWFUN("atan",EXP_ATAN,1,1,10) ;
   EXP_NEWFUN("exp",EXP_EXP,1,1,10) ;
   EXP_NEWFUN("log",EXP_LOG,1,1,10) ;
   EXP_NEWFUN("fabs",EXP_FABS,1,1,10) ;
   EXP_NEWFUN("max",EXP_MAX,1,2,10) ;
   EXP_NEWFUN("min",EXP_MIN,1,2,10) ;
   EXP_NEWFUN("rand",EXP_RAN,1,0,10) ;
   EXP_NEWFUN("int",EXP_INT,1,0,10) ;
}
void expressions_eval(char *string) {
   char *me = "expressions_eval";	 
   int len;
   int curFun;
   int gotone;
   int output_dest_save;
   char op[MAXLINE] ;
   RGST_Object_t *ro;
   Command_t     *cp;
   double *fpa;
   nest = 0 ;
   curOp = 0 ;
   lop  = 0 ;
   gotone = 1 ;
   while ( gotone ) {
      geta(op) ;
      if (!strcmp(op,"done")) {
         ctlerror(me,"Problem with expression evaluator\n") ;
      }
      curFun = expressions_isfun(op) ;
      if (curFun > -1) {
         if (funlist[curFun].prec <=  operand[lop].precLevel) {
            expressions_xop( funlist[curFun].prec );
         }
         operand[lop+1].precLevel = funlist[curFun].prec ;
         if (lop > 0) {
            if ((operand[lop].precLevel != 10) && 
                (operand[lop].precLevel > operand[lop+1].precLevel)) {
               expressions_xop(operand[curOp].precLevel) ;
            }
	 }
         lop++ ;
         operand[lop].pendOp  = funlist[curFun].type ;
         operand[lop].nestLevel = nest ;
      } else if (rgst_check_for_obj(op)) {
         if ( (RGST_QUERY_OBJECT_ATTR(op,"DomainVar" ) == TRUE)
            ||(RGST_QUERY_OBJECT_ATTR(op,"GlobalArray") == TRUE)) {
            len = getfpaa_rgst(op, &fpa, -1);
         } else if (RGST_QUERY_OBJECT_ATTR(op,"edit_function" ) == TRUE) {
            output_dest_save = output_dest;
            output_dest = TO_STACK;
	    ro = rgst_get_RGST_Object_t(op);
            cp = (Command_t *)ro->obj;
            (*(cp->handler))(cp);
	    fpa = MALLOT(double,1);
	    fpa[0] = ae_stack_pop_dbl();
	    len    = 1;
            output_dest = output_dest_save;
         } else if (  (RGST_QUERY_OBJECT_ATTR(op,"int_parm"    ) == TRUE) 
                   || (RGST_QUERY_OBJECT_ATTR(op,"double_parm" ) == TRUE) ) {
            len = getrgstdata(R_DOUBLE, op, (void **)&fpa, -1);
         }
         if (len > 0) {
            curOp++ ;
            operand[curOp].op = fpa[0] ;
            FREEMEM(fpa);
         } else {
            curOp++ ;
            operand[curOp].op = 0.;
         } 
      } else if (!strcmp(op,"(")) { 
         nest++ ;   
      } else if (!strcmp(op,")"))  { 
         expressions_xop(0);
         nest-- ; 
      } else if (!strcmp(op,",")) {
      } else if (!strcmp(op,"}"))  {
         expressions_xop(0);
         gotone = 0 ;
      } else {
         curOp++ ;
         expressions_check(op) ;
         operand[curOp].op = atof(op) ;
      }
   }  
   sprintf(string,"%.14g",operand[1].op) ;
}
static void expressions_check(char *sym) {
   int flag1,flag2,last ;
   char op[MAXLINE] ;
   flag1 = 0 ;
   if (('0' <= sym[0]) && (sym[0] <= '9')) flag1 = 1 ;
   last = strlen(sym) - 1 ;
   flag2 = 0 ;
   if ((sym[last] == 'e') || (sym[last] == 'E')) flag2 = 1 ;
   if ((flag1 > 0) && (flag2 > 0)) {
      geta(op) ;
      strcat(sym,op) ;
      if ((op[0] == '+') || (op[0] == '-')) {
         geta(op) ;
         strcat(sym,op) ;
      }
   } 
}
static int expressions_isfun(char *op) {
   int i,curFun ;
   curFun = -1 ;
   for ( i = 0 ; i < nfun ; i++ ) {
      if (!strcmp(funlist[i].name,op)) {
         curFun = i ;
         break ;
      }
   }
   return(curFun) ;
}
static void   expressions_xop( int prec ) {
   int op ;
   int iop1 ;
   int iop2 ;
   double aconv;
   aconv = PI / 180.;
   while(1) {
      if (lop < 1) break ;
      if (operand[lop].nestLevel != nest) break ;
      if (operand[lop].precLevel < prec) break ;
      op = operand[lop].pendOp ;
      lop-- ;
      if (op == EXP_PLUS)  {
         operand[curOp-1].op = operand[curOp-1].op + operand[curOp].op ;
         curOp-- ;
      } else if (op == EXP_MINUS) {
         operand[curOp-1].op = operand[curOp-1].op - operand[curOp].op ;
         curOp-- ;
      } else if (op == EXP_MULT) {
         operand[curOp-1].op = operand[curOp-1].op * operand[curOp].op ;
         curOp-- ;
      } else if (op == EXP_DIVIDE) {
         operand[curOp-1].op = operand[curOp-1].op /( operand[curOp].op + ptiny);
         curOp-- ;
      } else if (op == EXP_MOD) {
         iop1 = (int)(operand[curOp-1].op);
         iop2 = (int)(operand[curOp].op);
         operand[curOp-1].op = (double)(iop1 % iop2);
         curOp-- ;
      } else if (op == EXP_POWR) {
         operand[curOp-1].op = pow(operand[curOp-1].op,operand[curOp].op) ;
         curOp-- ;
      } else if (op == EXP_OR) {
	 iop1 = (int) (operand[curOp-1].op + 0.5);
	 iop2 = (int) (operand[curOp  ].op + 0.5);
         operand[curOp-1].op = (double)(iop1 || iop2);
         curOp-- ;
      } else if (op == EXP_AND) {
	 iop1 = (int) (operand[curOp-1].op + 0.5);
	 iop2 = (int) (operand[curOp  ].op + 0.5);
         operand[curOp-1].op = (double)(iop1 && iop2);
         curOp-- ;
      } else if (op == EXP_EQ) {
	 if (operand[curOp-1].op == operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
      } else if (op == EXP_NE) {
	 if (operand[curOp-1].op != operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
      } else if (op == EXP_GT) {
	 if (operand[curOp-1].op > operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
       } else if (op == EXP_GTE) {
	 if (operand[curOp-1].op >= operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
       } else if (op == EXP_LT) {
	 if (operand[curOp-1].op < operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
       } else if (op == EXP_LTE) {
	 if (operand[curOp-1].op <= operand[curOp].op) {
            operand[curOp-1].op = 1.;
	 } else {
            operand[curOp-1].op = 0.;
	 } 
         curOp-- ;
      } else if (op == EXP_NEG) {
         operand[curOp].op = -operand[curOp].op ;
      } else if (op == EXP_NOT) {
         if ( operand[curOp].op <= 0.) {
            operand[curOp].op  = 1.;
         } else {
            operand[curOp].op  = 0.;
         } 
      } else if (op == EXP_SQRT) {
         operand[curOp].op = sqrt(operand[curOp].op) ;
      } else if (op == EXP_SIN) {
         operand[curOp].op = sin(aconv*operand[curOp].op) ;
      } else if (op == EXP_COS) {
         operand[curOp].op = cos(aconv*operand[curOp].op) ;
      } else if (op == EXP_TAN) {
         operand[curOp].op = tan(aconv*operand[curOp].op) ;
      } else if (op == EXP_ASIN) {
         operand[curOp].op = asin(operand[curOp].op)/aconv ;
      } else if (op == EXP_ACOS) {
         operand[curOp].op = acos(operand[curOp].op)/aconv ;
      } else if (op == EXP_ATAN) {
         operand[curOp].op = atan(operand[curOp].op)/aconv ;
      } else if (op == EXP_EXP) {
         operand[curOp].op = exp(operand[curOp].op) ;
      } else if (op == EXP_LOG) {
         operand[curOp].op = log(operand[curOp].op) ;
      } else if (op == EXP_MAX) {
         if (operand[curOp].op > operand[curOp-1].op) {
            operand[curOp-1].op = operand[curOp].op ;
         }
         curOp-- ;
      } else if (op == EXP_MIN) {
         if (operand[curOp].op < operand[curOp-1].op)  {
            operand[curOp-1].op = operand[curOp].op ;
         }
         curOp-- ;
      } else if (op == EXP_FABS) {
         if (operand[curOp].op < 0.) {
            operand[curOp].op = -operand[curOp].op ;
         }
      } else if (op == EXP_RAN) {
         curOp++ ;
      } else if (op == EXP_INT) {
         operand[curOp].op = (double)( (int) operand[curOp].op);
      }
   }
}
