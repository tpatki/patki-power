#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void curwrtxy0(
	    char     *outfile,	   double   val0,	  int	   cn,
	    double   val,	   int	    mode )
{
   double ret[100] ;
   int nret ;
   FILE *fpcat ;
   char fullname[MAXLINE];
   strcpy(fullname,outpath);
   strcat(fullname,outfile);
   fpcat = fopen(fullname,"a+") ;
   if (mode == 1)  
      {
      getcurroot( ret, &nret  
                , p1d[2*cn+1].fpa , p1d[2*cn].fpa , p1d[2*cn].palen , val 
                , xmn , xmx ) ;
      fprintf(fpcat,"%e %e\n",ret[0],val0) ;
      }
   else if ( mode == 2 ) 
      {
      getcurroot( ret, &nret  
                , p1d[2*cn].fpa , p1d[2*cn+1].fpa , p1d[2*cn].palen , val 
                , ymn , ymx ) ;
      fprintf(fpcat,"%e %e\n",val0,ret[0]) ;
      }
   fclose(fpcat) ;
}
