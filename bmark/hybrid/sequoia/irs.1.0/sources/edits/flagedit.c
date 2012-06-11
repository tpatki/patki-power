#include "irs.h"
#include "irsedits.h"
#include "irsparm.h"
int flagedit( void )
{
   char msg[256];
   ctlmsg("-------------------------------------------------------------------------------"); 
   sprintf(msg,"Flag edit:  Cycle: %i   Time step: %e\n",cycle,ttime);	ctlmsg(msg);
   ctlmsg("-------------------------------------------------------------------------------"); 
   sprintf(msg,"ifplane = %i",ifplane); 	ctlmsg(msg);
   sprintf(msg,"iftmode = %i",iftmode); 	ctlmsg(msg);
   sprintf(msg,"iftion = %i",iftion); 		ctlmsg(msg);
   sprintf(msg,"ifpolar = %i",ifpolar); 	ctlmsg(msg);
   ctlmsg("-------------------------------------------------------------------------------\n"); 
    return(0);
}
