#ifndef cgl_H
#define cgl_H
 
/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

        /*---------------------------------------------------------------------
        - w2s(x,y)
        - converts x and y from world coordinates to screen coordinates
        ---------------------------------------------------------------------*/
#define w2s(x,y)  \
   x = _axw2s + _bxw2s*x ; \
   y = _ayw2s + _byw2s*y ; \
   if (x < 0.001) x = 0.001 ;  if (x > 0.999) x = 0.999 ;  \
   if (y < 0.001) y = 0.001 ;  if (y > 0.999) y = 0.999 ;  \
   _ifwc = 1

        /*---------------------------------------------------------------------
        - s2w(x,y)                                                                                          - converts x and y from screen coordinates to world coordinates 
        ---------------------------------------------------------------------*/
#define s2w(x,y)  \
   x = _axs2w + _bxs2w*x ; \
   y = _ays2w + _bys2w*y ;
 
        /*---------------------------------------------------------------------
        - s2pix(x,y,ix,iy)
        - converts x and y from screen coordinates to pixel coordinates
        ---------------------------------------------------------------------*/
#define s2pix(x,y,ix,iy)   \
   ix = x*window_width ;   \
   iy = (1. - y)*window_height

        /*---------------------------------------------------------------------
        - p2s(x,y)
        - converts x and y from port coordinates to screen coordinates
        ---------------------------------------------------------------------*/
#define p2s(x,y)   \
  { x = _pxmin + x*(_pxmax - _pxmin) ;   \
    y = _pymin + y*(_pymax - _pymin) ;   }
 

        /*---------------------------------------------------------------------
        - pix2s(ix,iy,x,y)
        - converts ix and iy from pixel coordinates to screen coordinates
        ---------------------------------------------------------------------*/
#define pix2s(ix,iy,x,y)   \
   x = ((double ) ix)/((double) window_width) ;   \
   y = ((double) (window_height - iy))/((double) window_height) 
 
        /*---------------------------------------------------------------------
        - setstr(d,s)
        - sets the VAX FORTRAN descriptor for character strings
        - d is the descriptor structure and s is the "C" string
        ---------------------------------------------------------------------*/
#ifdef MICROVAX

#define setstr(d,s)   	\
   d.len = strlen(s) ;	\
   d.type = 37 ;   	\
   d.class = 2 ;   	\
   d.pnt = s

#endif
 
        /*---------------------------------------------------------------------
	- s2cgm(ix,iy,x,y)
	- converts x and y from screen coordinates to cgm coordinates
        ---------------------------------------------------------------------*/
#define s2cgm(ix,iy,x,y) { ix = x*32767 ; iy = y*32767 ; }
 
        /*---------------------------------------------------------------------
	-  clipchk(x,y)
	-  checks screen coord x and y to see if they are in clip rect
        ---------------------------------------------------------------------*/
#define clipchk(x,y) \
	((_ifclip == 0)|((x >= _sxmin)&(x <= _sxmax)&(y >= _symin)&(y <= _symax)))

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

        /*---------------------------------------------------------------------
        - MICROVAX character descriptor structure
        ---------------------------------------------------------------------*/

#ifdef MICROVAX

struct des
   {
   unsigned short  len ;   /*	length of string in bytes   */
   char	 type ;		   /*	data type code	(37)   */
   char	 class ;	   /*	descriptor class code (2) */
   char *pnt ;		   /*	string pointer	       */
   } dsc1, dsc2 ;
 
extern float _winsz ;
 
#define TXSPAN 80.
 
#include "sys$library:uisentry.h"
#include "sys$library:uisusrdef.h"

#endif

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

        /*---------------------------------------------------------------------
        - bring external graflib routines
        ---------------------------------------------------------------------*/

#ifdef GRAFLIB
 
extern fortran   GSVTCL() ;	/*   set clipping			*/
extern fortran   GSTXNO() ;	/*   set text size			*/
extern fortran   GSMKXX() ;	/*   set marker character		*/
extern fortran   GPMK2D() ;	/*   plot a marker			*/
extern fortran   GPPG2D() ;	/*   polygon shading routine		*/
extern fortran   GSTXJF() ;	/*   set text justification		*/
extern fortran   GSCPVS() ;	/*   set curser in screen coordinates	*/
extern fortran   GSLNSZ() ;	/*   set line size			*/
extern fortran   GPLN2D() ;	/*   plot a line in world coordinates	*/
extern fortran   GSVSFL() ;	/*   set DLI file size			*/
extern fortran   GSVSKP() ;	/*   keep DLI file			*/
extern fortran   GPTX2D() ;	/*   plot text				*/
extern fortran   GSTXCR() ;	/*   set text color			*/
extern fortran   GSTXFT() ;	/*   set color				*/
extern fortran   GSTXMD() ;	/*   set font				*/
extern fortran   GSCRXX() ;	/*   set color				*/
extern fortran   JSCRXX() ;	/*   set color				*/
extern fortran   GSLNST() ;	/*   set line style			*/
extern fortran   GPCV2D() ;	/*   plot a curve			*/
extern fortran   GSGRXM() ;	/*   set x axis grid lines		*/
extern fortran   GSGRYM() ;	/*   set y axis grid lines		*/
extern fortran   GPGR80() ;	/*   plot axis				*/
extern fortran   GEGLXX() ;	/*   end GRAFLIB			*/
extern fortran   GSVP2D() ;	/*   set viewport			*/
extern fortran   GSWD2D() ;	/*   set view window			*/
extern fortran   GNTMDS() ;	/*   initialize TMDS			*/
extern fortran   GSVSMD() ;	/*   set TMDS mode			*/
extern fortran   GNGLXX() ;	/*   initialize GRAFLIB			*/
extern fortran   GXGLFR() ;	/*   clear frame			*/
extern fortran   GXGLUP() ;	/*   update all active view surfaces	*/
extern fortran   GNVSXX() ;	/*   initialize view surface		*/
extern fortran   GSVSFN() ;	/*   set DLI file name			*/
extern fortran   GNDLIX() ;	/*   initialize DLI			*/
extern fortran   GNRJET() ;	/*   initialize RJET			*/
extern fortran   GEVSXX() ;	/*   terminate a single view surface	*/
extern fortran   GCVSXX() ;	/*   connect a view surface		*/
extern fortran   GDVSXX() ;	/*   disconnect a view surface		*/
extern fortran   GSVSRT() ;	/*   rotate RJET output			*/
extern fortran   GSTXLF() ;	/*   set line feed charater		*/
extern fortran   GSPGAN() ;	/*   set polygon shade angle		*/
extern fortran   GSPGSP() ;	/*   set polygon line spacing		*/
extern fortran   GSPGMD() ;	/*   set polygon mode			*/
extern fortran   JSPGED() ;	/*   set polygon edge mode		*/
extern fortran   JSPGST() ;	/*   set polygon fill mode		*/
extern fortran   JPPG2A() ;	/*   shade polygon (GRAFCORE)		*/
extern fortran   JSPGCR() ;	/*   set polygob fill color		*/
extern fortran   JNCRID();
extern fortran   JSCRID();
extern fortran   JPCA2A();
extern fortran   JNCRSZ();
extern fortran   ZPAKCHRZ() ;

#endif

         /*---------------------------------------------------------------------
         - SUN stuff
         ---------------------------------------------------------------------*/
#ifdef SUN

#define TXSPAN 80.
#include <usercore.h>

extern int pixwindd() ;
extern int cgpixwindd() ;
#endif

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern int _ifxlog ; /* HH_INIT 0 */
extern int _ifylog ; /* HH_INIT 0 */
 
extern char cgm_file[20] ; /* HH_INIT "" */

extern int  izero  ; /* HH_INIT 0 */
extern int  ione   ; /* HH_INIT 1 */
extern int  itwo   ; /* HH_INIT 2 */
extern int  ithree ; /* HH_INIT 3 */
extern float fzero ; /* HH_INIT 0.0 */
extern float fone  ; /* HH_INIT 1.0 */
 
extern char dev_name[20] ;

         /*---------------------------------------------------------------------
         - DIGLIB stuff
         ---------------------------------------------------------------------*/
#ifdef DIGLIB
extern float _winsz ;
#endif

         /*---------------------------------------------------------------------
         - XLIB
         ---------------------------------------------------------------------*/
#ifdef XLIB

#define TXSPAN 80.
         
extern   char window_name[20];
extern   char icon_name[20];

#endif
 
/*******************************************************************************
* END OF FILE
*******************************************************************************/

