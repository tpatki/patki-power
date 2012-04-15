#include "irs.h"
#include "irsgen.h"
void tagvoid( Domain_t *domain )
{
   int i, itest ;
   int *ireg1, *ireg2, *ireg3, *ireg4, *ireg5, *ireg6, *ireg7, *ireg8 ;
   if ( ndims == 2 ) {
      ZNSET2D(domain->ireg,ireg1,ireg2,ireg3,ireg4) ;
      for ( i = domain->frn ; i <= domain->lrn ; i++ ) {
         itest = 1 ;
         if ( (ireg1[i] != irvoid) & (ireg1[i] != 0) ) itest = 0 ;
         if ( (ireg2[i] != irvoid) & (ireg2[i] != 0) ) itest = 0 ;
         if ( (ireg3[i] != irvoid) & (ireg3[i] != 0) ) itest = 0 ;
         if ( (ireg4[i] != irvoid) & (ireg4[i] != 0) ) itest = 0 ;
      }
   }
   if ( ndims == 3 ) {
      ZNSET3D(domain->ireg,ireg1,ireg2,ireg3,ireg4,ireg5,ireg6,ireg7,ireg8) ;
      for ( i = domain->frn ; i <= domain->lrn ; i++ ) {
         itest = 1 ;
         if ( (ireg1[i] != irvoid) & (ireg1[i] != 0) ) itest = 0 ;
         if ( (ireg2[i] != irvoid) & (ireg2[i] != 0) ) itest = 0 ;
         if ( (ireg3[i] != irvoid) & (ireg3[i] != 0) ) itest = 0 ;
         if ( (ireg4[i] != irvoid) & (ireg4[i] != 0) ) itest = 0 ;
         if ( (ireg5[i] != irvoid) & (ireg5[i] != 0) ) itest = 0 ;
         if ( (ireg6[i] != irvoid) & (ireg6[i] != 0) ) itest = 0 ;
         if ( (ireg7[i] != irvoid) & (ireg7[i] != 0) ) itest = 0 ;
         if ( (ireg8[i] != irvoid) & (ireg8[i] != 0) ) itest = 0 ;
      }
   }
}
