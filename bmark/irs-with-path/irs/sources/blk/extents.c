#include "irs.h"
#include "irsblk.h"
#include "Extents.h"
int extents_overlap(Extents_t *ext1, Extents_t *ext2, Extents_t *ext3) {
   int len;
   int i, j, k;
   len = 0;
   if (ext1->imin >= ext2->imin) {
      ext3->imin = ext1->imin;
   } else {
      ext3->imin = ext2->imin;
   }
   if (ext1->jmin >= ext2->jmin) {
      ext3->jmin = ext1->jmin;
   } else {
      ext3->jmin = ext2->jmin;
   }
   if (ext1->kmin >= ext2->kmin) {
      ext3->kmin = ext1->kmin;
   } else {
      ext3->kmin = ext2->kmin;
   }
   if (ext1->imax >= ext2->imax) {
      ext3->imax = ext2->imax;
   } else {
      ext3->imax = ext1->imax;
   }
   if (ext1->jmax >= ext2->jmax) {
      ext3->jmax = ext2->jmax;
   } else {
      ext3->jmax = ext1->jmax;
   }
   if (ext1->kmax >= ext2->kmax) {
      ext3->kmax = ext2->kmax;
   } else {
      ext3->kmax = ext1->kmax;
   }
   j = ext3->jmax - ext3->jmin;
   i = ext3->imax - ext3->imin;
   if (ndims == 2) {
      k = 0;
   } else {
      k = ext3->kmax - ext3->kmin;
   } 
   if ( (i < 0) || (j < 0) || (k < 0) ) {
      len = 0;
   } else {
      len = (i+1)*(j+1)*(k+1);
   } 
   return(len);
}
void extents_getndx( Extents_t ext, int jp, int kp, int* ndx)
{
   int i,j,k;
   int count,ip;
   count = 0;
   if (ndims == 2) {
      for (j = ext.jmin; j <= ext.jmax; j++) {
         for (i = ext.imin; i <= ext.imax; i++) {
            ip = i + j*jp;
            ndx[count] = ip;
            count++;
         }
      }
   } else {
      for (k = ext.kmin; k <= ext.kmax; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               ip = i + j*jp + k*kp;
               ndx[count] = ip;
               count++;
            }
         }
      }
   }
}
int extents_redext( Extents_t* extout, Extents_t extin, int type) 
{
   int iside; 
   int jside; 
   int kside; 
   int number; 
   int imin,jmin,kmin;
   int imax,jmax,kmax;
   number = 0;
   iside = 0;
   jside = 0;
   kside = 0;
   if (extin.imax != extin.imin) iside = 1;
   if (extin.jmax != extin.jmin) jside = 1;
   if (extin.kmax != extin.kmin) kside = 1;
   imax = extin.imax;
   jmax = extin.jmax;
   kmax = extin.kmax;
   imin = extin.imin;
   jmin = extin.jmin;
   kmin = extin.kmin;
   if (ndims == 2) {
      if (type == EDGE) {
         if (iside && jside) {
            SETEXT(extout[0],imin,imin,jmin,jmax,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmax,kmin,kmin);
            SETEXT(extout[2],imin,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[3],imin,imax,jmax,jmax,kmin,kmin);
            number = 4;
         }
      } else if (type == CORNER) {
         if (iside && jside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[2],imax,imax,jmax,jmax,kmin,kmin);
            SETEXT(extout[3],imin,imin,jmax,jmax,kmin,kmin);
            number = 4;
         } else if (iside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmin,kmin,kmin);
            number = 2;
         } else if (jside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmax,jmax,kmin,kmin);
            number = 2;
         } 
      } 
   } else {
      if (type == FACE) {
         if (iside && jside && kside) {
            SETEXT(extout[0],imin,imin,jmin,jmax,kmin,kmax);
            SETEXT(extout[1],imax,imax,jmin,jmax,kmin,kmax);
            SETEXT(extout[2],imin,imax,jmin,jmin,kmin,kmax);
            SETEXT(extout[3],imin,imax,jmax,jmax,kmin,kmax);
            SETEXT(extout[4],imin,imax,jmin,jmax,kmin,kmin);
            SETEXT(extout[5],imin,imax,jmin,jmax,kmax,kmax);
            number = 6;
         } 
      } else if (type == EDGE) {
         if (iside && jside && kside) {
            SETEXT(extout[0],imin,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imax,jmin,jmin,kmax,kmax);
            SETEXT(extout[2],imin,imax,jmax,jmax,kmin,kmin);
            SETEXT(extout[3],imin,imax,jmax,jmax,kmax,kmax);
            SETEXT(extout[4],imin,imin,jmin,jmax,kmin,kmin);
            SETEXT(extout[5],imin,imin,jmin,jmax,kmax,kmax);
            SETEXT(extout[6],imax,imax,jmin,jmax,kmin,kmin);
            SETEXT(extout[7],imax,imax,jmin,jmax,kmax,kmax);
            SETEXT(extout[8],imin,imin,jmin,jmin,kmin,kmax);
            SETEXT(extout[9],imin,imin,jmax,jmax,kmin,kmax);
            SETEXT(extout[10],imax,imax,jmin,jmin,kmin,kmax);
            SETEXT(extout[11],imax,imax,jmax,jmax,kmin,kmax);
            number = 12;
         } else if (iside && jside) {
            SETEXT(extout[0],imin,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imax,jmax,jmax,kmin,kmin);
            SETEXT(extout[2],imin,imin,jmin,jmax,kmin,kmin);
            SETEXT(extout[3],imax,imax,jmin,jmax,kmin,kmin);
            number = 4;
         } else if (iside && kside) {
            SETEXT(extout[0],imin,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imax,jmin,jmin,kmax,kmax);
            SETEXT(extout[2],imin,imin,jmin,jmin,kmin,kmax);
            SETEXT(extout[3],imax,imax,jmin,jmin,kmin,kmax);
            number = 4;
         } else if (jside && kside) {
            SETEXT(extout[0],imin,imin,jmin,jmax,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmin,jmax,kmax,kmax);
            SETEXT(extout[2],imin,imin,jmin,jmin,kmin,kmax);
            SETEXT(extout[3],imin,imin,jmax,jmax,kmin,kmax);
            number = 4;
         } 
      } else if (type == CORNER) {
         if (iside && jside && kside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmin,jmin,kmax,kmax);
            SETEXT(extout[2],imin,imin,jmax,jmax,kmin,kmin);
            SETEXT(extout[3],imin,imin,jmax,jmax,kmax,kmax);
            SETEXT(extout[4],imax,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[5],imax,imax,jmin,jmin,kmax,kmax);
            SETEXT(extout[6],imax,imax,jmax,jmax,kmin,kmin);
            SETEXT(extout[7],imax,imax,jmax,jmax,kmax,kmax);
            number = 8;
         } else if (iside && jside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[2],imax,imax,jmax,jmax,kmin,kmin);
            SETEXT(extout[3],imin,imin,jmax,jmax,kmin,kmin);
            number = 4;
         } else if (iside && kside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmin,kmin,kmin);
            SETEXT(extout[2],imax,imax,jmin,jmin,kmax,kmax);
            SETEXT(extout[3],imin,imin,jmin,jmin,kmax,kmax);
            number = 4;
         } else if (jside && kside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmax,jmax,kmin,kmin);
            SETEXT(extout[2],imin,imin,jmax,jmax,kmax,kmax);
            SETEXT(extout[3],imin,imin,jmin,jmin,kmax,kmax);
            number = 4;
         } else if (iside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imax,imax,jmin,jmin,kmin,kmin);
            number = 2;
         } else if (jside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmax,jmax,kmin,kmin);
            number = 2;
         } else if (kside) {
            SETEXT(extout[0],imin,imin,jmin,jmin,kmin,kmin);
            SETEXT(extout[1],imin,imin,jmin,jmin,kmax,kmax);
            number = 2;
         } 
      } 
   }
   return(number);
}
int extents_gettype(Extents_t extin) {
   int iside;
   int jside;
   int kside;
   iside = 0;
   jside = 0;
   kside = 0;
   if (extin.imax != extin.imin) iside = 1;
   if (extin.jmax != extin.jmin) jside = 1;
   if (extin.kmax != extin.kmin) kside = 1;
   if (ndims == 2) {
      if ( (iside) && (jside) ) {
         return(AREA);
      } 
      if ( (iside) || (jside) ) {
         return(FACE);
      } else {
         return(CORNER);
      }
   } else {
      if ((iside) && (jside) && (kside)) {
         return(VOLUME);
      }
      if ( ((iside) && (jside)) ||
           ((iside) && (kside)) ||
           ((jside) && (kside)) ) {
         return(FACE);
      }
      if ((iside) || (jside) || (kside)) {
         return(EDGE);
      } else {
         return(CORNER);
      } 
   } 
}
void extents_transform(Extents_t ext1, Extents_t ext2, int orient[3], Extents_t extin,
                      Extents_t *extout) 
{
   Extents_t ext;
   int imin,jmin,kmin;
   int imax,jmax,kmax;
   ext.imin = extin.imin - ext1.imin;
   ext.jmin = extin.jmin - ext1.jmin;
   ext.kmin = extin.kmin - ext1.kmin;
   ext.imax = extin.imax - ext1.imin;
   ext.jmax = extin.jmax - ext1.jmin;
   ext.kmax = extin.kmax - ext1.kmin;
   if (abs(orient[0]) == 1) {
      imin = ext.imin;
      imax = ext.imax;
   }
   if (abs(orient[0]) == 2) {
      imin = ext.jmin;
      imax = ext.jmax;
   }
   if (abs(orient[0]) == 3) {
      imin = ext.kmin;
      imax = ext.kmax;
   }
   if (abs(orient[1]) == 1) {
      jmin = ext.imin;
      jmax = ext.imax;
   }
   if (abs(orient[1]) == 2) {
      jmin = ext.jmin;
      jmax = ext.jmax;
   }
   if (abs(orient[1]) == 3) {
      jmin = ext.kmin;
      jmax = ext.kmax;
   }
   if (abs(orient[2]) == 1) {
      kmin = ext.imin;
      kmax = ext.imax;
   }
   if (abs(orient[2]) == 2) {
      kmin = ext.jmin;
      kmax = ext.jmax;
   }
   if (abs(orient[2]) == 3) {
      kmin = ext.kmin;
      kmax = ext.kmax;
   }
   SETEXT(ext,imin,imax,jmin,jmax,kmin,kmax);
   if (orient[0] < 0) {
      imin = ext2.imax - ext.imin;
      imax = ext2.imax - ext.imax;
   } else {
      imin = ext.imin + ext2.imin;
      imax = ext.imax + ext2.imin;
   } 
   if (orient[1] < 0) {
      jmin = ext2.jmax - ext.jmin;
      jmax = ext2.jmax - ext.jmax;
   } else {
      jmin = ext.jmin + ext2.jmin;
      jmax = ext.jmax + ext2.jmin;
   } 
   if (orient[2] < 0) {
      kmin = ext2.kmax - ext.kmin;
      kmax = ext2.kmax - ext.kmax;
   } else {
      kmin = ext.kmin + ext2.kmin;
      kmax = ext.kmax + ext2.kmin;
   } 
   extout->imin = MIN(imin,imax);
   extout->imax = MAX(imin,imax);
   extout->jmin = MIN(jmin,jmax);
   extout->jmax = MAX(jmin,jmax);
   extout->kmin = MIN(kmin,kmax);
   extout->kmax = MAX(kmin,kmax);
}
void extents_getndx_orient( Extents_t ext, int jp, int kp, int *orient, int* ndx)
{
   int i,j,k;
   int id;
   int imin[3];
   int imax[3];
   int istride[3];
   int ip[3];
   for (i = 0; i < 3; i++) {
      if (abs(orient[i]) == 1) {
         if (orient[i] < 0) {
            imin[i] = ext.imax;
            imax[i] = ext.imin;
            istride[i] = -1;
            ip[i] = 1;
         } else {
            imin[i] = ext.imin;
            imax[i] = ext.imax;
            istride[i] = 1;
            ip[i] = 1;
         } 
      } else if (abs(orient[i]) == 2) {
         if (orient[i] < 0) {
            imin[i] = ext.jmax;
            imax[i] = ext.jmin;
            istride[i] = -1;
            ip[i] = jp;
         } else {
            imin[i] = ext.jmin;
            imax[i] = ext.jmax;
            istride[i] = 1;
            ip[i] = jp;
         }
      } else if (abs(orient[i]) == 3) {
         if (orient[i] < 0) {
            imin[i] = ext.kmax;
            imax[i] = ext.kmin;
            istride[i] = -1;
            ip[i] = kp;
         } else {
            imin[i] = ext.kmin;
            imax[i] = ext.kmax;
            istride[i] = 1;
            ip[i] = kp;
         }
      }  else {
         ctlerror("extents_getndx_orient","Bad block orientation while setting index list");
      } 
      if (imin[i] == imax[i]) istride[i] = 1;
   }
   id = 0;
   if (ndims == 3) {
      for (k = 0; k <= abs(imax[2] - imin[2]); k++) {
         for (j = 0; j <= abs(imax[1] - imin[1]); j++) {
            for (i = 0; i <= abs(imax[0] - imin[0]); i++) {
               ndx[id++] = ((i*istride[0] + imin[0])*ip[0]) + 
                           ((j*istride[1] + imin[1])*ip[1]) + 
                           ((k*istride[2] + imin[2])*ip[2]);
            }
         }
      }
   } else {
      for (j = 0; j <= abs(imax[1] - imin[1]); j++) {
         for (i = 0; i <= abs(imax[0] - imin[0]); i++) {
            ndx[id++] = ((i*istride[0] + imin[0])*ip[0]) +
                        ((j*istride[1] + imin[1])*ip[1]);
         }
      }
   } 
}
void extents_shift(Extents_t gext, Extents_t ext, int jp, int kp, int *pn, 
                   int dir, Extents_t *extout) 
{
   pn[0] = 0;
   pn[1] = 0;
   pn[2] = 0;
   CPYEXT((*extout),ext);
   if ((ext.imin == ext.imax) && (ext.imin == gext.imin)) {
      pn[0] = -1 ;
      extout->imin = extout->imin - dir;
      extout->imax = extout->imax - dir;
   }
   if ((ext.imin == ext.imax) && (ext.imax == gext.imax)) {
      pn[0] =  1 ;
      extout->imin = extout->imin + dir;
      extout->imax = extout->imax + dir;
   }
   if ((ext.jmin == ext.jmax) && (ext.jmin == gext.jmin)) {
      pn[1] = -jp;
      extout->jmin = extout->jmin - dir;
      extout->jmax = extout->jmax - dir;
   }
   if ((ext.jmin == ext.jmax) && (ext.jmax == gext.jmax)) {
      pn[1] =  jp;
      extout->jmin = extout->jmin + dir;
      extout->jmax = extout->jmax + dir;
   }
   if ((ext.kmin == ext.kmax) && (ext.kmin == gext.kmin)) {
      pn[2] = -kp;
      extout->kmin = extout->kmin - dir;
      extout->kmax = extout->kmax - dir;
   }
   if ((ext.kmin == ext.kmax) && (ext.kmax == gext.kmax)) {
      pn[2] =  kp;
      extout->kmin = extout->kmin + dir;
      extout->kmax = extout->kmax + dir;
   }
}
int extents_xor(Extents_t ext1, Extents_t ext2, int jp, int kp, int *ndx) {
   int len;
   int i,j,k;
   int id;
   Extents_t oext;
   len = extents_overlap(&ext1, &ext2, &oext);
   len = 0;
   if (ndims == 2)  {
      for (j = ext1.jmin; j <= ext1.jmax; j++) {
         for (i = ext1.imin; i <= ext1.imax; i++) {
            if ((i < oext.imin) || (i > oext.imax) ||
                (j < oext.jmin) || (j > oext.jmax)) {
               id = i + jp * j;
               ndx[len++] = id;
            }
         }
      }
      for (j = ext2.jmin; j <= ext2.jmax; j++) {
         for (i = ext2.imin; i <= ext2.imax; i++) {
            if ((i < oext.imin) || (i > oext.imax) ||
                (j < oext.jmin) || (j > oext.jmax)) {
               id = i + jp * j;
               ndx[len++] = id;
            }
         }
      }
   } else {
      for (k = ext1.kmin; k <= ext1.kmax; k++) {
         for (j = ext1.jmin; j <= ext1.jmax; j++) {
            for (i = ext1.imin; i <= ext1.imax; i++) {
               if ((i < oext.imin) || (i > oext.imax) ||
                   (j < oext.jmin) || (j > oext.jmax) ||
                   (k < oext.kmin) || (k > oext.kmax)) {
                  id = i + jp * j + kp * k;
                  ndx[len++] = id;
               }
            }
         }
      }
      for (k = ext2.kmin; k <= ext2.kmax; k++) {
         for (j = ext2.jmin; j <= ext2.jmax; j++) {
            for (i = ext2.imin; i <= ext2.imax; i++) {
               if ((i < oext.imin) || (i > oext.imax) ||
                   (j < oext.jmin) || (j > oext.jmax) ||
                   (k < oext.kmin) || (k > oext.kmax)) {
                  id = i + jp * j + kp * k;
                  ndx[len++] = id;
               }
            }
         }
      }
   } 
   return(len);
}
int extents_aggregate(Extents_t *subext, int nsubext, Extents_t supext, int flag) {
    int i,j;
    int len;
    int len_super;
    int len_sub;
    Extents_t ext1;
    Extents_t ext2;
    Extents_t ext3;
    len_sub = 0;
    len_super = 0;
    CPYEXT(ext1,supext);
    if (ext1.imin != ext1.imax) ext1.imax--;
    if (ext1.jmin != ext1.jmax) ext1.jmax--;
    if ((ndims == 3) && (ext1.kmin != ext1.kmax)) ext1.kmax--;
    len_super = LENEXT(ext1);
    for (i = 0; i < nsubext - 1; i++) {
       CPYEXT(ext1,subext[i]);
       if (ext1.imin != ext1.imax) ext1.imax--;
       if (ext1.jmin != ext1.jmax) ext1.jmax--;
       if ((ndims == 3) && (ext1.kmin != ext1.kmax)) ext1.kmax--;
       len_sub += extents_overlap(&ext1,&supext,&ext3);
       for (j = i+1; j < nsubext; j++) {
          CPYEXT(ext2,subext[j]);
          if (ext2.imin != ext2.imax) ext2.imax--;
          if (ext2.jmin != ext2.jmax) ext2.jmax--;
          if ((ndims == 3) && (ext2.kmin != ext2.kmax)) ext2.kmax--;
	  len = extents_overlap(&ext1,&ext2,&ext3);
	  if ((flag == 1) && (len > 0)) return(-1);
          len_sub = len_sub - len;	   
       }
    }
    CPYEXT(ext1,subext[nsubext - 1]);
    if (ext1.imin != ext1.imax) ext1.imax--;
    if (ext1.jmin != ext1.jmax) ext1.jmax--;
    if ((ndims == 3) && (ext1.kmin != ext1.kmax)) ext1.kmax--;
    len_sub += extents_overlap(&ext1,&supext,&ext3);
    if (len_sub != len_super) return(-1);
    return(0);
}
void extents_getlogical( Extents_t *ext, int logical, int *min, int *max) 
{
   if (logical == 0) {
      *min = ext->imin;
      *max = ext->imax;
   } else if (logical == 1) {
      *min = ext->jmin;
      *max = ext->jmax;
   } else if (logical == 2) {
      *min = ext->kmin;
      *max = ext->kmax;
   } else {
      *min = 0;
      *max = 0;
   } 
}
void extents_setlogical( Extents_t *ext, int logical, int *min, int *max) 
{
   if (logical == 0) {
      ext->imin = *min;
      ext->imax = *max;
   } else if (logical == 1) {
      ext->jmin = *min;
      ext->jmax = *max;
   } else if (logical == 2) {
      ext->kmin = *min;
      ext->kmax = *max;
   } 
}
