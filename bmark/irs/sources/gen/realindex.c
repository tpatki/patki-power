#include "irs.h"
#include "irsgen.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"
int  realindex( void )
{
   char *me = "realindex";
   char msg[MAXLINE];
   char aname[MAXWORD];
   int gblk;
   int len;
   int ip;
   int error = 0 ;
   Extents_t uext;
   Extents_t gext;
   Extents_t ext;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   ndxin = NULL;
   ndxptr = NULL;
   strcpy(aname,"") ;
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      CPYEXT(uext,(*ndxptr));
      for (gblk = 0; gblk < gnblk; gblk++) {
          if (gmap[gblk].ublk != ndxptr->ublk) continue;
          CPYEXT(gext,gmap[gblk]);
          if ((len = extents_overlap(&uext, &gext, &ext)) > 0) {
             TRSEXT(ext,ext,gext);
             if (ndims == 3) {
                if (len > 1) {
                   sprintf(msg,"%i:(%i:%i,%i:%i,%i:%i) proc = %i",gblk,
                                        ext.imin, ext.imax,
                                        ext.jmin, ext.jmax,
                                        ext.kmin, ext.kmax,
                                        gmap[gblk].proc);
                } else {
                   ip = ext.imin + ext.jmin * gmap[gblk].jp + 
		                              ext.kmin * gmap[gblk].kp;
                   sprintf(msg,"%i:(%i,%i,%i)  proc = %i   ndx = %i",gblk,
		                          ext.imin,ext.jmin,ext.kmin,
					  gmap[gblk].proc,ip);
                } 
             } else {
                if (len > 1) {
                   sprintf(msg,"%i:(%i:%i,%i:%i)",gblk,
                                        ext.imin, ext.imax,
                                        ext.jmin, ext.jmax);
                } else {
                   ip = ext.imin + ext.jmin * gmap[gblk].jp; 
                   sprintf(msg,"%i:(%i,%i)  proc = %i  ndx = %i ",gblk,
		                      ext.imin,ext.jmin,gmap[gblk].proc,ip);
                } 
             } 
             ctlmsg(msg);
          }
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin);
   return(error) ;
}
