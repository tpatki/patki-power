#include "irs.h"
#include "Spline.h"
#define SIZEINC 200
#define CHKLEN(a,b) \
   if (inlen < 0 ) { \
      if (b > (maxlen-1)) { \
         tmp=a; \
         while (b >= maxlen) maxlen += SIZEINC; \
         a = realloc(tmp,(maxlen)*sizeof(double)); \
      } \
   } else { \
      if (b > inlen) { \
        b = inlen - 1; \
        numflg = 0; \
        nextflg = 0; \
      } \
   } 
int getflst( double **datain, int inlen )
{
   char *me = "getflst";
   char msg[MAXLINE];
   int i,j, len, cflag, rep, lenrep, maxlen, nextflg, numflg;
   int ns, flg, numpts, error, newlen; 
   double deltastart, delta;
   double xmin, xmax;
   double *data;
   double *tmp;
   double *x;
   double *y;
   char op[MAXWORD];
   Spline_t *spline;
   error = 0;
   maxlen = 200;
   if (inlen < -1) {
      inlen = -inlen;
      data = ALLOT(double,inlen);
   }
   else if (inlen < 0) {
      data = ALLOT(double,maxlen);
   } else {
      data = datain[0];
   } 
   len = 0;
   numflg = 1;
   while (numflg) {
      peekc(op);
      if (!strcmp(op,"(")) {
         geta(op);
         len--;
         rep = (int) data[len];
         rep = rep -1;
         nextflg = 1;
         lenrep = 0;
         while (nextflg) {
            peekc(op);
            if (!strcmp(op,")")) {
               geta(op);
               nextflg = 0;
            } else if (!isalpha(op[0])) {
               data[len++] = getf(&cflag);
               if (cflag) {
                  nextflg  =0;
                  numflg  =0;
                  len = -1;
                  ctlwarning(me,"Non-numeric data in input string");
               }
               CHKLEN(data,len);
               lenrep++;
            } else {
               ctlwarning(me,"Parenthesis not closed in data string");
               nextflg = 0;
               numflg = 0 ;
               len = -1;
            } 
         }
         newlen = len + rep*lenrep;
         CHKLEN(data,newlen);
         for (i=0;i<rep;i++) {
            for (j=0;j<lenrep;j++) {
               data[len]=data[len-lenrep];
               len++;
            }
         }
      } else if (!strcmp(op,"[")) {
         geta(op);
         delta = getf(&cflag);
         geta(op);
         if (strcmp(op,"]")) {
            ctlwarning(me,"Bracket not closed in data string");
            numflg = 0;
            len = -1;
         } else {
            lenrep = geti(&cflag);
            len--;
            deltastart = data[len];
            newlen = len + lenrep;
            CHKLEN(data,newlen);
            for (i=0;i<lenrep;i++) {
               data[len++] = deltastart + i*delta; 
            }
         }  
      } else if ((!strcmp(op,"spln_x")) ||
                 (!strcmp(op,"spln_y")) || 
                 (!strcmp(op,"spln"))) {
         geta(op);
         flg = 0;
         if (!strcmp(op,"spln_x")) flg = 1;
         if (!strcmp(op,"spln_y")) flg = 2;
         geta(op);
         geta(op);
         spline = spline_find(op);
         if (spline == NULL) {
           sprintf(msg,"Spline %s not defined.",op);
           ctlwarning(me, msg);
           return(-1);
         }
         geta(op); 
         xmin = getf(&cflag);
         geta(op); 
         xmax = getf(&cflag);
         geta(op); 
         numpts = geti(&cflag);
         x = MALLOT(double,numpts);
         y = MALLOT(double,numpts);
         error = spline_getxy(x, y, numpts, xmin, xmax, 0., 0., spline);
         if (error) {
            FREEMEM(x);
            FREEMEM(y);
            return(-1);
         }
         newlen = len + numpts;
         if (flg == 0) newlen = len + 2*numpts;
         CHKLEN(data,newlen);
         for (i = 0; i < numpts; i++) {
            if (flg == 0) {
               data[len++] = x[i];
               data[len++] = y[i];
            } else if (flg == 1) {
               data[len++] = x[i];
            } else if (flg == 2) {
               data[len++] = y[i];
            } 
         }
         geta(op);
         FREEMEM(x);
         FREEMEM(y);
      } else if (!strcmp(op,"end")) {
         geta(op);
         numflg = 0;
      } else if (isalpha(op[0])) {
         numflg  = 0;
      } else {
         data[len++] = getf(&cflag);
         CHKLEN(data,len);
         if (cflag) {
           len--;
           inlen = len;
         }
      } 
      if ( (len >= inlen) && (inlen>0) ) {
         numflg = 0;
      }
   } 
   datain[0] = data;
   return(len);
}
#undef SIZEINC 
#undef CHKLEN
