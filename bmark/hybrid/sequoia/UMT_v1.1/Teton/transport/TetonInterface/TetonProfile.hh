//---------------------------------*-C++-*----------------------------------//
// Copyright 1998 The Regents of the University of California.
// All rights reserved.
//--------------------------------------------------------------------------//

#ifndef __TETON_TETONPROFILE_HH__
#define __TETON_TETONPROFILE_HH__

#include "utilities/KullTypes/CharStar8.hh"
#include <cstring>
#include <vector>

class TetonProfile {
//-----------------------------------------------------------
//  Teton Sn Radiation Transport source and boundary profile
//  Module
//-----------------------------------------------------------
public:
   ~TetonProfile() {}

   // ------------------------------------------------------------
   // An empty profile
   // ------------------------------------------------------------
   TetonProfile()
      : 
      prmult(0.0),
      prof(0)
   {
      strncpy(iptyp.data,  "none    ", 8);
      strncpy(pshape.data, "none    ", 8);
      timetemps.resize(0);
   }

   // ------------------------------------------------------------
   // No shape, just a type
   // ------------------------------------------------------------
   TetonProfile(const CharStar8& _iptyp)
       : iptyp(_iptyp),
         prmult(0.0),
         prof(0){
      strncpy(pshape.data, "none    ", 8);
      timetemps.resize(0);
   }

   // ------------------------------------------------------------
   // Add type (refl,vac,temp) and shape (none,iso,fds) info
   // ------------------------------------------------------------
   TetonProfile(const CharStar8& _iptyp,
                const CharStar8& _pshape,
                double _prmult,
                const std::vector<double> &_timetemps)
       : iptyp(_iptyp),
         pshape(_pshape),
         prmult(_prmult),
         timetemps(_timetemps),
         prof(0)
   {
   }

   // ------------------------------------------------------------
   // Does it lack type
   // ------------------------------------------------------------
   int 
   typeless() {
      printf("Check type of %c%c%c%c%c\n",
              iptyp.data[0], iptyp.data[1], iptyp.data[2],
              iptyp.data[3], iptyp.data[4]);
      return ( strncmp(iptyp.data, "none    ", 8) == 0 );
   }

   // ------------------------------------------------------------
   // Does it lack shape
   // ------------------------------------------------------------
   int 
   shapeless() {
      return ( strncmp(pshape.data, "none    ", 8) == 0 );
   }

   // ------------------------------------------------------------
   // How many time fields
   // ------------------------------------------------------------
   int 
   tim(int ngr) {
      int isSourceFds = 0;
      char buf[9];
      strncpy(buf, iptyp.data, 8);
      buf[8] = 0;
      isSourceFds = sourceIs("fds");
      if ( isSourceFds ) {
         return (timetemps.size()/(ngr+1));
      } 
      else {
         return (timetemps.size()/2);
      }
   }

   int 
   sourceIs(const char *source) {
      int l;      
      l = strlen(source);
      if ( l >= 8 ) {
         return ( strncmp(source, iptyp.data, 8) == 0 );
      } 
      else {
         return ( strncmp(source, iptyp.data, l) == 0 
               && iptyp.data[l] == ' ');
      }
   }


   CharStar8            iptyp;
   CharStar8            pshape;
   double               prmult;
   std::vector<double>  timetemps;
   int                  prof;
};

#endif
