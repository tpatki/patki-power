#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "transport/TetonInterface/Teton.hh"
#include "transport/TetonInterface/TetonNT.hh"
#include "scstd.h"
#include <sstream>
#include <fstream>
#include <iomanip>
using std::vector;

#undef max

extern "C"
{


#if !(defined LINUX) && !(defined __blrts) && !(defined BGP)
   extern void *
   bsearch (const void *,
            const void *, 
            unsigned long,
            unsigned long,
            int(*) (const void *, const void *));

   extern void 
   qsort (void *, 
          unsigned long, 
          unsigned long,
          int(*) (const void *,const void *));
   
#endif
   extern int 
   MPI_Barrier (MPI_Comm);

   void 
   F77_ID(getedits_, getedits, GETEDITS)
         (void *, void *, void *,
          int *, int *, int *, int *, int *,
          int *, int *, double *,
          double *, double *, double *, double *,
          double *, double *, double *, double *);
   void
   F77_ID(getrunstats_, getrunstats, GETRUNSTATS)
         (void *, void *, void *, void *,
          int *, int *, int *, int *, int *,
          double *, double *, double *, double *, double *,
          double *, double *, double *, double *, double *,
          double *, double *, char *, char *);

   void
   F77_ID(settimestep_, settimestep, SETTIMESTEP)
         (void *, void *, void *, double *, double *, double *, double *,
          double *, double *, double *, double *, double *, double *);

   void
   F77_ID(setsnorder_, setsnorder, SETSNORDER)
         (void *, void *, int *, int *, double *);

   void 
   F77_ID(constructitercontrols_, constructitercontrols, CONSTRUCTITERCONTROLS) 
         (int *, int *, int *,
          double *, double *, double *,
          void *);

   void
   F77_ID(constructdtcontrols_, constructdtcontrols, CONSTRUCTDTCONTROLS)
         (double *, double *, double *, double *, double *,
          void *);

   void
   F77_ID(constructgeometry_, constructgeometry, CONSTRUCTGEOMETRY)
         (void *, void *);

   void
   F77_ID(constructmaterial_, constructmaterial, CONSTRUCTMATERIAL)
         (void *, void *);

   void
   F77_ID(constructprofile_, constructprofile, CONSTRUCTPROFILE)
         (void *, int *);

   void
   F77_ID(addprofile_, addprofile, ADDPROFILE)
         (void *, int *, int *, int *,
                  int *, double *,
                  char *, char *, char *,
                  double *, double *);

   void
   F77_ID(constructquadrature_, constructquadrature, CONSTRUCTQUADRATURE)
         (void *, int *, int *);

   void
   F77_ID(constructsize_, constructsize, CONSTRUCTSIZE)
         (void *,
          int *, int *, int *, int *, int *,
          int *, int *, int *, int *, int *,
          int *, int *, int *, int *,
          double *, double *, char *, char *, char *,
          char *, char *, char *, char *);

   void
   F77_ID(setmaterialmodule_, setmaterialmodule, SETMATERIALMODULE)
         (void *, void *, 
          double *, double *, double *, double *, double *,
          double *, double *, double *, double *, double *, 
          double *, double *, double *, double *, double *, double *); 

   void
   F77_ID(constructeditor_, constructeditor, CONSTRUCTEDITOR)
         (void *, void *);

   void
   F77_ID(setgeometry_, setgeometry, SETGEOMETRY)
         (void *, void *,
          int *, int *,
          int *, int *, int *, int *,
          int *, int *, int *, int *,
          char *, int *, double *);

   void
   F77_ID(resetsize_, resetsize, RESETSIZE)
         (void *, 
          double *, double *, char *, char *, char *,
          char *, char *, char *, char *); 

   void 
   F77_ID(radtr_, radtr, RADTR)
         ( int *,     // ncycle 
           double*,   // omp loop time
           void *,    // IterControls
           void *,    // DtControls
           void *,    // Size
           void *,    // Geometry
           void *,    // Material
           void *,    // Quadrature
           void *,    // Editor
           void *,    // Profile

           double *,  // PSIR
           double *,  // PHIR
           double *   // RadSpecificEnergy 
                   );
}
    
template <typename Mesh>
Teton<Mesh>::Teton():
// Most of these values are crucial for dimensioning,
// make sure that they have reasonable values
   ndim(3), my_node(0), ncycle(0), nbelem(0), nzones(0), 
   ncornr(0), npnts(0), nfaces(0), nbedit(0), ngr(0), 
   noutmx(20), ninmx (1), ngdamx(7), nprof(0),  GTAorder(2), 
   npsi(0), erad(0.0), emat(0.0), eradinct(0.0), 
   eradesct(0.0), eextsrc(0.0), echeck(0.0),
   tfloor(2.5e-5), tmin(5.0e-03), dtrad(1.0e-03),
   epstmp(1.0e-4), epsinr(1.0e-4), epsgda(1.0e-5),
   delte(0.4), deltr(0.4), timerad(0.0),angleLoopTime(0.0),
   dtrmn(1.0e-04), dtrmx(0.1), ncomm(0), nbshare(0)
{
// CharStar8 are structs, not classes!!!  Just do the
// data transfer (blank padded)
   strncpy (ittyp.data,   "timedep ", 8);
   strncpy (iaccel.data,  "gda     ", 8);
   strncpy (imatc.data,   "elec    ", 8);
   strncpy (iscat.data,   "on      ", 8);
   strncpy (itimsrc.data, "exact   ", 8);
   strncpy (decomp_s.data,"off     ", 8);
}


// ------------------------------------------------------------
// resize
//
// Make sure all arrays have a reasonable dimension.  Some
// derived scalars are computed here as well.
// ------------------------------------------------------------

template <typename Mesh>
void
Teton<Mesh>::resize() {

   int isSphere = 0, isCylinder = 0, isSlab =0, isXy = 0, isRz = 0;
   int isXyz = 0;
   int D_ncornr, D_nzones,  D_ncornr_npsi;
   int D_ncornr_ngr, D_nbedit1_ngr, D_npnts_ndim;
   int D_nzones_ngr, D_ngr1;
// Set  ndim
   isSphere   = ( strncmp(igeom.data, "sphere  ", 8) == 0 );
   isCylinder = ( strncmp(igeom.data, "cylinder", 8) == 0 );
   isSlab     = ( strncmp(igeom.data, "slab    ", 8) == 0 );
   isXy       = ( strncmp(igeom.data, "xy      ", 8) == 0 );
   isRz       = ( strncmp(igeom.data, "rz      ", 8) == 0 );
   isXyz      = ( strncmp(igeom.data, "xyz     ", 8) == 0 );
   if ( isSphere || isCylinder || isSlab ) {
      ndim  = 1;
   } 
   else if ( isXy || isRz ) {
      ndim  = 2;
      maxcf = 2;
   } 
   else if ( isXyz ) {
      ndim  = 3;
      maxcf = 3;
   } 
   else {
      ndim  = 0;
   }


   D_ncornr            = std::max(ncornr, 0);
   D_nzones            = std::max(nzones, 0);
   D_ncornr_npsi       = std::max(ncornr * npsi, 0);
   D_ncornr_ngr        = std::max(ncornr * ngr, 0);
   D_nbedit1_ngr       = std::max((nbedit+1) * ngr, 0);
   D_npnts_ndim        = std::max(npnts * ndim, 0);
   D_nzones_ngr        = std::max(nzones * ngr, 0);
   D_ngr1              = std::max(ngr+1, 0);

   psir.resize(D_ncornr_npsi);
   phir.resize(D_ncornr_ngr);
   RadSpecificEnergy.resize(D_nzones_ngr);
   tec.resize(D_ncornr);
   tic.resize(D_ncornr);
   curesc.resize(D_nbedit1_ngr);
   curinc.resize(D_nbedit1_ngr);
   eradesc.resize(D_nbedit1_ngr);
   eradinc.resize(D_nbedit1_ngr);
   denez.resize(D_nzones);
   deniz.resize(D_nzones);
   trz.resize(D_nzones);
   tez.resize(D_nzones);
   tiz.resize(D_nzones);
   px.resize(D_npnts_ndim);
   siga.resize(D_nzones_ngr);
   sigt.resize(D_nzones_ngr);
   sigs.resize(D_nzones_ngr);
   cve.resize(D_nzones);
   cvi.resize(D_nzones);
   rho.resize(D_nzones);
   xomei.resize(D_nzones);
   selec.resize(D_nzones);
   sion.resize(D_nzones);
   gnu.resize(D_ngr1);
}

// ------------------------------------------------------------
//   CXX_RADTR  - Control program for radiation transport. 
// ------------------------------------------------------------

template <typename Mesh>
double
Teton<Mesh>::cxxRadtr() {
    
    int myProc=0;
#ifdef USE_MPI
    MPI_Comm_rank(MPI_COMM_WORLD,&myProc);
#endif
// ------------------------------------------------------------
// Move time ahead
// ------------------------------------------------------------
   ncycle ++;
   
   F77_ID(settimestep_, settimestep, SETTIMESTEP)
         (Size, DtControls, Editor, &dtrad, &timerad, &tfloor, &tmin,
          &erad, &emat, &eradinct, &eradesct, &eextsrc, &echeck);


// ------------------------------------------------------------
// Run the step
// ------------------------------------------------------------
   F77_ID(radtr_, radtr, RADTR)
         ( &ncycle,               // int *
           &angleLoopTime,        // double *
           IterControls,          // void * 
           DtControls,            // void *
           Size,                  // void *
           Geometry,              // void *
           Material,              // void *
           Quadrature,            // void *
           Editor,                // void *
           Profile,               // void *
           &psir[0],              // double *
           &phir[0],              // double *
           &RadSpecificEnergy[0]  // double *
                   );

   timerad += dtrad;

   F77_ID(getedits_, getedits, GETEDITS)
        (IterControls, DtControls, Editor,
         &noutrt, &ninrt, &ngdart,
         &TrMaxZone, &TeMaxZone, &TrMaxNode, &TeMaxNode, 
         &dtrad, &TrMax, &TeMax, &erad, &emat,
         &eradinct, &eradesct, &eextsrc, &echeck);

   F77_ID(getrunstats_, getrunstats, GETRUNSTATS)
         (Size, Material, IterControls, DtControls,
          &ConvControlNode, &ConvControlZone,
          &DtControlNode, &DtControlZoneTr4,
          &DtControlZoneTe,
          &ConvControlError, &ConvControlTr,
          &ConvControlTe, &ConvControlRho,
          &ConvControlCve, &ConvControlEdep,
          &DtControlChangeTr4, &DtControlChangeTe, 
          &DtControlTr, &DtControlTe,
          &DtControlTrOld, &DtControlTeOld,
          ConvControlReason.data, DtControlReason.data);

   return dtrad;
}


// ------------------------------------------------------------
// setBCs
//
// Associate boundary conditions with Teton (call only once!)
// ------------------------------------------------------------
template <typename Mesh>
void
Teton<Mesh>::setBCs(std::vector<TetonBoundary> &BCList) {

   int position = 1;
   nbc = BCList.size();

// ------------------------------------------------------------
//  Loop over boundary conditions and build the profile
// list
// ------------------------------------------------------------
   for(int i=0; i<nbc; ++i) {
     setAProfile (BCList[i].profile, position);
   }

}


// ------------------------------------------------------------
// setVSs
//
// Associate volume sources with Teton (call only once!)
// ------------------------------------------------------------
template <typename Mesh>
void
Teton<Mesh>::setVSs(std::vector<TetonVolumeSource> &VSList) {

   int position = 0;
   nvs = VSList.size();

// ------------------------------------------------------------
// Loop over volume sources and build the profile list
// ------------------------------------------------------------
   for(int i=0; i<nvs; ++i) {
     setAProfile (VSList[i].profile, position);
   }

}


// ------------------------------------------------------------
// setAProfile
//
// Unpack a profile's time and value data.  This routine
// builds the Profile Module.
// ------------------------------------------------------------
template <typename Mesh>
void
Teton<Mesh>::setAProfile(TetonProfile &P, int position) {

// If empty, no work
   int noshape = 0, sourceFds = 0, groups, NumTimes, NumValues;
   int i=0, j=0, g=0, NumInterpValues;
   double Multiplier;
   CharStar8 Type, Shape, Location;
   std::vector<double> Times, Values;

   noshape = P.shapeless();
   if ( noshape  ) {
      return;
   }

   P.prof = ++nprof;

   NumTimes = P.tim(ngr);

   sourceFds = P.sourceIs("fds");
   if ( sourceFds ) {
      groups = ngr;
   } 
   else {
      groups = 1;
   }

   if ( position ) {
      strncpy(Location.data,"boundary",8);
   }
   else {
      strncpy(Location.data,"region  ",8);
   }

   NumValues       = NumTimes*groups;
   NumInterpValues = ngr;

   Times.resize(NumTimes);
   Values.resize(NumValues);

   for ( i=0; i<NumTimes; ++i) {
      Times[i] = P.timetemps[j++];
      for( g=0; g<groups; ++g ) {
         Values[i*groups+g] = P.timetemps[j++];
      }
   }

   Multiplier = P.prmult;
   Type       = P.iptyp;
   Shape      = P.pshape;

   F77_ID(addprofile_, addprofile, ADDPROFILE)
         (Profile, &nprof, &NumTimes, &NumValues, 
                   &NumInterpValues, &Multiplier,
                   Location.data, Type.data, Shape.data,
                   &Times[0], &Values[0]);

   return;
}


// ------------------------------------------------------------
// setGroups
//
// Associate frequency group info with Teton (call once)
// ------------------------------------------------------------
template <typename Mesh>
void
Teton<Mesh>::setGroups(const std::vector<TetonFreq>& groups) {

   int group = 0,  offset = 0;
   int D_ngr6;

   ngr = groups.size();
   D_ngr6 = std::max(6 * (ngr+1), 0);

// Make sure there is room for this group
   gnu.resize(ngr+1);
   quaddef.resize(D_ngr6);

   for (group = 0; group < ngr; ++group) {
      gnu[group]        = groups[group].bot;
      gnu[group+1]      = groups[group].top;
      quaddef[offset]   = groups[group].qtype;
      quaddef[offset+1] = groups[group].qorder;
      quaddef[offset+2] = groups[group].npolar;
      quaddef[offset+3] = groups[group].nazimu;
      quaddef[offset+4] = groups[group].paxis;
      offset            = offset + 6;
   }

// Set quadrature definition for acceleration
   quaddef[offset]   = 1;
   quaddef[offset+1] = GTAorder;
   quaddef[offset+2] = 1;
   quaddef[offset+3] = 1;
   quaddef[offset+4] = 1;

// Construct the quadrature module

   void *CQuadrature;

   F77_ID(constructquadrature_, constructquadrature, CONSTRUCTQUADRATURE)
         (&CQuadrature, &ngr, &quaddef[0]);
   Quadrature = CQuadrature;

}

template <typename Mesh>
void Teton<Mesh>::setMeshSizeAndPositions(typename Teton<Mesh>::MeshType &M,
                                          std::vector<int> &tmpnode) {

   int i = 0, Ti = 0;
   px.resize(ndim*npnts);

   for( i=0; i<npnts; ++i) {
      Ti = tmpnode[i];
      if ( ndim == 1 ) {
         px[i] = (M.nodeBegin() + Ti)->getPosition()[0];
      }
      else if ( ndim == 2 ) {
         px[ndim*i]   = (M.nodeBegin() + Ti)->getPosition()[0];
         px[ndim*i+1] = (M.nodeBegin() + Ti)->getPosition()[1];
      }
      else if ( ndim == 3 ) {
         px[ndim*i]   = (M.nodeBegin() + Ti)->getPosition()[0];
         px[ndim*i+1] = (M.nodeBegin() + Ti)->getPosition()[1];
         px[ndim*i+2] = (M.nodeBegin() + Ti)->getPosition()[2];
      }
   }

}

template <typename Mesh>
void Teton<Mesh>::setCommunication(typename Teton<Mesh>::MeshType &M,
                                   std::vector<int> &bdytof) {

   int i = 0, j = 0, k = 0;

   CommMapType  sendMap    = M.getCommAgent().getFaceNeighborMap().sendMap();
   CommMapType  receiveMap = M.getCommAgent().getFaceNeighborMap().receiveMap();
                   
   typename CommMapType::const_iterator iter;
   typename CommMapType::const_iterator Riter,Siter;
   typename Teton<Mesh>::MeshType::FaceIterator Fi;
   typename Teton<Mesh>::MeshType::FaceIterator FiR;
   typename Teton<Mesh>::MeshType::FaceIterator FiS;
   typename Teton<Mesh>::MeshFCiF FaceDomainLookup(M);

   typename Teton<Mesh>::Edge::CornerIterator CorI;

   int faceID = -1, GfaceID = -1, cornerID = -1, nodeID = -1, bdyElem = -1;
   int cfID = -1, ID1 = -1, stride = -1, maxFace = -1, oppC = -1;
   int CNRfaceCtr = -1, faceCtr = -1, nodeCtr = -1, sharedCtr = -1;
   int neighbor = -1, neighborCtr = -1, domainID = -1;
   int maxNode, index;

   std::vector<int> listFaces;
   std::vector<int> cnrFace1;
   std::vector<int> listNodes;
   std::vector<int> listCorners; 
   std::vector<int> numCNRface;
   std::vector<int> bdyID;

   listFaces.reserve( nbshare );
   cnrFace1.reserve( nbshare );
   listNodes.reserve( nbshare );
   listCorners.reserve( nbshare );
   numCNRface.reserve( nbshare );
   bdyID.reserve( nbshare );
                   
   stride      = 4*maxcf;
   sharedCtr   = 0;
   neighborCtr = 0;

   for (Riter = receiveMap.begin(); Riter != receiveMap.end(); ++Riter) {
      domainID = Riter->first;
      for(FiR = Riter->second.begin(); FiR != Riter->second.end(); FiR++) {
         if (FiR->getOppositeFace().isSend() == 1) {
//------------------------------UMT-CMG------------------------------
//  removed getOppositeFace() since global face IDs are the same on different
//  parallel domains.
//------------------------------UMT-CMG------------------------------
            FaceDomainLookup[*FiR] = domainID;
         }
      }
   }

// Iterate over all neighbors 
   for (i=0,iter = sendMap.begin(); iter != sendMap.end(); ++iter, i++) {
      CNRfaceCtr = 0;
      faceCtr    = 0;
      neighbor   = iter->first;                 // process ID
      for (Fi = iter->second.begin(); Fi < iter->second.end(); Fi++) {

//       Find all communicate faces
         if ( (Fi->getOppositeFace().isReceive() ==1) && (FaceDomainLookup[*Fi] == neighbor)) {
            faceID  = M.getLocalID(*Fi);
            if (my_node < neighbor) {
              GfaceID  = M.getGlobalID(*Fi);
            } else if (my_node > neighbor) {
//------------------------------UMT-CMG------------------------------
//  removed getOppositeFace() since global face IDs are the same on different
//  parallel domains and the OppositeFace in CMG for COMM faces is degenerate.
//------------------------------UMT-CMG------------------------------
//               GfaceID  = M.getGlobalID(Fi->getOppositeFace());
                GfaceID  = M.getGlobalID(*Fi);  // same ID for CMG mesh
            } 
            listFaces.push_back( GfaceID );
            cnrFace1.push_back( CNRfaceCtr );

            nodeCtr = 0;
            for (CorI = Fi->cornerBegin(); CorI < Fi->cornerEnd(); CorI++) {
               nodeID   = M.getGlobalID(CorI->getNode());
               cornerID = M.getLocalID(*CorI);
               listNodes.push_back( nodeID );
               listCorners.push_back( cornerID );
               nodeCtr++;
            }

            listNodes.resize( nodeCtr );
            listCorners.resize( nodeCtr );
            maxNode = (*( std::max_element(listNodes.begin(),listNodes.end()) ));

            for (j=0; j<nodeCtr; j++) {
               index    = std::distance( listNodes.begin(), std::min_element(listNodes.begin(),listNodes.end()) );
               cornerID = listCorners[index]; 
               cfID     = cornerID*stride;
               for (k=0; k<maxcf; k++) {
                  oppC    = connect[cfID+4*k];
                  bdyElem = connect[cfID+4*k+1];
                  if ( (oppC == 0) && (bdytof[bdyElem-1] == faceID) ) {
                     bdyID[CNRfaceCtr] = bdyElem;
                  }
               }
               listNodes[index] = maxNode+1;
               CNRfaceCtr++;
            }
            numCNRface[faceCtr] = nodeCtr;
            faceCtr++;
         }
            listNodes.resize(0);
            listCorners.resize(0);
      }

// Now order in increasing face ID and node ID

      if (CNRfaceCtr > 0) {

         nodecomm.push_back( neighbor );     // neighbor process ID
         nodecomm.push_back( CNRfaceCtr );   // shared corner-faces with this process
         neighborCtr++;

         listFaces.resize( faceCtr );
         cnrFace1.resize( faceCtr );
         maxFace = (*( std::max_element(listFaces.begin(),listFaces.end()) )); 
     
         for (j=0; j<faceCtr; j++) {
            index = std::distance( listFaces.begin(), std::min_element(listFaces.begin(),listFaces.end()) );
            ID1   = cnrFace1[index];
            for (k=0; k<numCNRface[index]; k++) {
               cbdycomm[sharedCtr+k] = bdyID[ID1+k]; 
            }
            listFaces[index] = maxFace+1;
            sharedCtr = sharedCtr + numCNRface[index];
         }

      }

      listFaces.resize(0);
      cnrFace1.resize(0);
   }

   ncomm = neighborCtr;
   if( ncomm>0)
       nodecomm.resize(2*ncomm);

// Release memory
   listFaces.resize(0);
   cnrFace1.resize(0);
   listNodes.resize(0);
   listCorners.resize(0);
   numCNRface.resize(0);
   bdyID.resize(0);

}

// ------------------------------------------------------------
// linkKull -- Kull to Teton
//
// Grab stuff from Kull structures, stuff into Teton, and
// ready a step
// ------------------------------------------------------------
template <typename Mesh>
void
Teton<Mesh>::linkKull(typename Teton<Mesh>::MeshType &M,
                      const std::vector<TetonFreq> &GList,
                      std::vector<TetonBoundary> &BCList,
		      std::vector<TetonVolumeSource> &VSList,
                      std::vector<int> &PXlookup) {
                                                                                             
   int i = 0, j = 0, k = 0, faceno = 0, point0 = 0;
   int cid = -1, fid = -1, beCtr = 0, stride = -1;
   int corner1= -1, corner2 = -1, Ocorner1 = -1;
   int  Onode1 = -1, c1 = -1, Ofid = -1, face = -1;
   int cfID1 = -1, cfID2 = -1, ez1 = -1, faceCtr = 0;
   int Ocorner2 = -1, Onode2 = -1, node2 = -1;
   int  zid = -1, node1 = -1, totfaces = 0;
   int CID = 0, SID = 0, isRecv=0;
   int isTimeDep = 0, isExact = 0;
   int maxprof = 0, numBC = 0;
   int nintsides = 0, nodeSize = 0, cornerSize = 0; 

   CharStar8 shared;

   std::vector<int>  bdytof;
   vector< int > tmpnode, tmpcorner, faceMap;
   vector< int > testcomm, cfaceID1, cfaceID2;
   vector< int > cfaceNext1, cfaceNext2;

// Define Iterators
   typename Teton<Mesh>::MeshType::ZoneIterator zidP;
   typename Teton<Mesh>::MeshType::ZoneHandle::CornerIterator cidP;
   typename Teton<Mesh>::MeshType::CornerHandle::SideIterator sidP;
   typename Teton<Mesh>::MeshType::CornerHandle::FaceIterator fidP;

// Determine various problem parameters
   maxprof   = std::max(BCList.size(),VSList.size());
   nintsides = M.getNumberOfInternalSides();
   nzones    = M.getNumberOfOwnedZones();
   nfaces    = M.getNumberOfOwnedFaces();
   nbshare   = 0;
   ncomm     = 0;
   totfaces  = M.getNumberOfFaces();

   nodeSize   = nintsides;
   cornerSize = nintsides;

   strncpy(shared.data,"shared  ",8);

   tmpnode.resize(nintsides);
   tmpcorner.resize(nintsides);

   for( i=0; i<nintsides; i++){
      tmpnode[i]   = -1;
      tmpcorner[i] = -1;
   }

   typename Teton<Mesh>::MeshType::SideIterator Si;

   for(SID=1,Si = M.ownedSideBegin(); Si != M.ownedSideEnd(); Si++,SID++){
      const typename Teton<Mesh>::Zone &Z = Si->getZone();
      isRecv = Z.isReceive();
      if( isRecv ){
         continue;
      }
      tmpnode[SID-1]   = M.getLocalID(Si->getRightCorner().getNode());
      tmpcorner[SID-1] = 0;
   }

   rmdupsort(&tmpnode[0],&nodeSize);
    
   for( i=0; i<nodeSize; i++){
      PXlookup[tmpnode[i]] = i;
   }
    
   typename Teton<Mesh>::MeshType::CornerIterator Ci;
   for(CID=1, Ci =M.ownedCornerBegin(); Ci != M.ownedCornerEnd(); Ci++,CID++){
      const typename Teton<Mesh>::Zone &Z = Ci->getZone();
      isRecv = Z.isReceive();
      if( isRecv ) {
         continue;
      }
      tmpcorner[CID-1] = M.getLocalID(*Ci);
   }
    
   rmdupsort(&tmpcorner[0],&cornerSize);

// Set various mesh parameters
   ncornr = cornerSize;
   npnts  = nodeSize;

// Find the number of faces per corner (nfpc) and the maximum number (maxcf)
   nfpc.resize(ncornr);
   faceMap.resize(totfaces);
    
    
   for( i=0;i<ncornr;i++) {
      nfpc[i] = 0;
   }
    
   for( i=0;i<totfaces;i++) {
      faceMap[i] = 0;
   }
    
   for(zidP=M.ownedZoneBegin();zidP != M.ownedZoneEnd(); ++zidP) {
      for(cidP=zidP->cornerBegin();cidP != zidP->cornerEnd(); ++cidP) {
         corner1 = M.getLocalID(*cidP);
         if (corner1 < ncornr) {
            for(fidP= cidP->faceBegin();fidP != cidP->faceEnd();fidP++) {
               fid           = M.getLocalID(*fidP);
               faceMap[fid]  = faceMap[fid]  + 1;
               nfpc[corner1] = nfpc[corner1] + 1;
            }
         }
      }
   }

   maxcf = (*( std::max_element(nfpc.begin(),nfpc.end()) ));
    
   faceCtr = 0;
   for( i=0;i<totfaces;i++) {
      if (faceMap[i] > 0) {
         faceCtr++;
         faceMap[i] = faceCtr;
      }
   }
    
// Allocate persistant arrays
   resize();

   void *CProfile;
   F77_ID(constructprofile_, constructprofile, CONSTRUCTPROFILE)
         (&CProfile, &maxprof);
   Profile = CProfile;
    
    
   setBCs(BCList);
   setVSs(VSList);

// -------------------------------------------------------------------
// Go through the BC's and build up Teton BC arrays Based on Corners
// -------------------------------------------------------------------
   for(zidP=M.ownedZoneBegin();zidP != M.ownedZoneEnd(); ++zidP) {
      for(cidP=zidP->cornerBegin();cidP != zidP->cornerEnd(); ++cidP) {
         for(fidP= cidP->faceBegin();fidP != cidP->faceEnd();fidP++) {
            if( (fidP->isSend()) && (fidP->getOppositeFace().isReceive()) ) {
                numBC++;
            } else if ( (fidP->isReceive()) && (fidP->getOppositeFace().isSend()) ) {
                numBC++;
            } else if(M.isExternal(*fidP)) {
                numBC++;
            } else if(M.isSurface(*fidP)) {
                numBC++;
            }
         }
      }
   }


   nbelem  = numBC;

// Set the node positions
   setMeshSizeAndPositions(M, tmpnode);

// Allocate arrays to construct the mesh connectivity
   connect.resize(4*maxcf*ncornr);
   ctozone.resize(ncornr);
   ctopoint.resize(ncornr);
   bdytoc.resize(2*nbelem);
   bdytof.resize(nbelem);
   bdytosrc.resize(nbelem);
   bdytoedit.resize(nbelem);
   bdytobc.resize(nbelem);
   testcomm.resize(nbelem);
   cfaceNext1.resize(ncornr);
   cfaceNext2.resize(ncornr);
   cfaceID1.resize(maxcf*ncornr);
   cfaceID2.resize(maxcf*ncornr);
   ctoface.resize(maxcf*ncornr);
   std::vector<int> ctoZoneFace(maxcf*ncornr);
   zonetosrc.resize(nzones);

// For now, the building of connect is geometry specific. Hopefully,
// it can be generalized in the near future

   beCtr = 0;
   stride = 4*maxcf;

   if (ndim == 2) {

      for(zidP=M.ownedZoneBegin();zidP != M.ownedZoneEnd(); ++zidP) {
         for(sidP= zidP->sideBegin();sidP != zidP->sideEnd();sidP++) {
            corner1  = M.getLocalID(sidP->getRightCorner());
            corner2  = M.getLocalID(sidP->getLeftCorner());
            Ocorner1 = M.getLocalID(sidP->getOppositeSide().getLeftCorner());
            Onode1   = M.getLocalID(sidP->getOppositeSide().getLeftCorner().getNode());
            Ocorner2 = M.getLocalID(sidP->getOppositeSide().getRightCorner());
            Onode2   = M.getLocalID(sidP->getOppositeSide().getRightCorner().getNode());
            node1    = M.getLocalID(sidP->getRightCorner().getNode());
            node2    = M.getLocalID(sidP->getLeftCorner().getNode());
            zid      = M.getLocalID(sidP->getRightCorner().getZone());
            fid      = M.getLocalID(sidP->getFace());
    
            ctopoint[corner1] = PXlookup[node1] + 1;
            ctozone[corner1]  = zid + 1;
// Set the "EZ" corner faces shared by corner1/corner2
            connect[corner1*stride + 2] = corner2 + 1;
            connect[corner1*stride + 3] = 2;
            connect[corner2*stride + 6] = corner1 + 1;
            connect[corner2*stride + 7] = 1;
// Set the "FP" corner faces
            if (Onode1 == node1) {
               if (Ocorner1 < ncornr) {
                  connect[corner1*stride + 0] = Ocorner1 + 1;
                  connect[corner1*stride + 1] = 2;
               } else {
                  bdytof[beCtr]               = fid;
                  bdytoc[beCtr*2]             = corner1 + 1;
                  bdytoc[beCtr*2 + 1]         = 1;
                  connect[corner1*stride + 0] = 0;
                  connect[corner1*stride + 1] = beCtr + 1;
                  beCtr++;
               }
            }
            if (Onode2 == node2) {
               if (Ocorner2 < ncornr) {
                  connect[corner2*stride + 4] = Ocorner2 + 1;
                  connect[corner2*stride + 5] = 1;
               } else {
                  bdytof[beCtr]               = fid;
                  bdytoc[beCtr*2]             = corner2 + 1;
                  bdytoc[beCtr*2 + 1]         = 2;
                  connect[corner2*stride + 4] = 0;
                  connect[corner2*stride + 5] = beCtr + 1;
                  beCtr++;
               }
            }
         }
      }

   } else if (ndim == 3) {

      for( i=0;i<ncornr;i++) {
         cfaceNext1[i] = 0;
         cfaceNext2[i] = 0;
      }

      for(zidP=M.ownedZoneBegin();zidP != M.ownedZoneEnd(); ++zidP) {
         for(sidP= zidP->sideBegin();sidP != zidP->sideEnd();sidP++) {
            corner1  = M.getLocalID(sidP->getRightCorner());
            corner2  = M.getLocalID(sidP->getLeftCorner());
            if ( (corner1 < ncornr) && (corner2 < ncornr) ) {
               fid = M.getLocalID(sidP->getFace());
               j   = cfaceNext2[corner1];
               k   = cfaceNext1[corner2];

               ctoface[corner2*maxcf+k]  = fid;
               ctoZoneFace[corner2*maxcf+k]  = fid;
               cfaceID1[corner2*maxcf+k] = corner1;
               cfaceID2[corner1*maxcf+j] = corner2;
               cfaceNext1[corner2]       = cfaceNext1[corner2] + 1;
               cfaceNext2[corner1]       = cfaceNext2[corner1] + 1;
            }
         }
      }

      for( i=0;i<ncornr;i++) {
         for( j=1;j<maxcf-1;j++) {
            cfID1 = cfaceID1[i*maxcf+j];
            cfID2 = cfaceID2[i*maxcf+j];
            fid   = ctoface[i*maxcf+j];
            if (cfID1 != cfaceID2[i*maxcf+j-1]) {
              cfaceID1[i*maxcf+j]   = cfaceID1[i*maxcf+j+1];
              cfaceID2[i*maxcf+j]   = cfaceID2[i*maxcf+j+1];
              ctoface[i*maxcf+j]    = ctoface[i*maxcf+j+1];
              cfaceID1[i*maxcf+j+1] = cfID1;
              cfaceID2[i*maxcf+j+1] = cfID2;
              ctoface[i*maxcf+j+1]  = fid;
            }
         }
      }

      for(zidP=M.ownedZoneBegin();zidP != M.ownedZoneEnd(); ++zidP) {
         for(sidP= zidP->sideBegin();sidP != zidP->sideEnd();sidP++) {
            corner1  = M.getLocalID(sidP->getRightCorner());
            Ocorner1 = M.getLocalID(sidP->getOppositeSide().getLeftCorner());
            Onode1   = M.getLocalID(sidP->getOppositeSide().getLeftCorner().getNode());
            node1    = M.getLocalID(sidP->getRightCorner().getNode());
            zid      = M.getLocalID(sidP->getRightCorner().getZone());
            fid      = M.getLocalID(sidP->getFace());
            Ofid     = M.getLocalID(sidP->getOppositeSide().getFace());

            c1       = corner1*stride;
 
            for( j=0;j<maxcf;j++) {
               if (ctoface[corner1*maxcf + j] == fid) {
                 cfID1   = j;
                 corner2 = cfaceID1[corner1*maxcf + j];
               }
            }

            for( j=0;j<maxcf;j++) {
               if (cfaceID1[corner2*maxcf + j] == corner1) {
                 cfID2 = j;
               }
            }

            ctopoint[corner1] = PXlookup[node1] + 1;
            ctozone[corner1]  = zid + 1;

// Set the "EZ" corner faces shared by corner1/corner2
            ez1 = 4*cfID1 + 2;

            connect[c1 + ez1]     = corner2 + 1;
            connect[c1 + ez1 + 1] = cfID2   + 1;

// Set the "FP" corner faces
            if (Ocorner1 > -1) {

                for( j=0;j<maxcf;j++) {
                    if (ctoface[Ocorner1*maxcf + j] == Ofid) {
                        cfID2 = j;
                    }
                }

                connect[c1  + 4*cfID1]     = Ocorner1 + 1;
                connect[c1  + 4*cfID1 + 1] = cfID2 + 1;
            } else {
                bdytof[beCtr]             = fid;
                bdytoc[beCtr*2]           = corner1 + 1;
                bdytoc[beCtr*2 + 1]       = cfID1 + 1;
                connect[c1 + 4*cfID1]     = 0;
                connect[c1 + 4*cfID1 + 1] = beCtr + 1;
                beCtr++;
            }
         }
      }

// The Sn package expects the faces to be numbered 1 to nfaces.
      for(i=0; i<maxcf*ncornr; ++i) {
         j          = ctoface[i];
         fid        = faceMap[j]; 
         ctoface[i] = fid;
      }

   }

//    connectCheck(M,PXlookup,ctoZoneFace);
   
// -------------------------------------------------------------------
// Go through the BC's and build up Teton BC arrays Based on Corners
// -------------------------------------------------------------------

   for(j=0; j < nbelem; j++){
      bdytobc[j]  = shared;
      testcomm[j] = 1;
   }

   for( i=0; i<nbc; ++i) {
      TetonBoundary &BC = BCList[i];
    
      for( faceno=0; faceno < BC.faceids.size(); ++faceno) {
         fid = BC.faceids[faceno];
         typename Teton<Mesh>::Face::CornerIterator CPnt;
         for(CPnt = (M.faceBegin() + fid)->cornerBegin();
             CPnt != (M.faceBegin() + fid)->cornerEnd();
             ++CPnt) 
         {
            point0 = M.getLocalID(*CPnt) + 1;
    
            for(j=0; j < nbelem; j++){
               cid = bdytoc[2*j];
               if (point0 == cid) {
                  face = bdytof[j];
                  if (face == fid) {
                     bdytobc[j]   = BC.profile.iptyp;
                     bdytosrc[j]  = BC.profile.prof;
                     bdytoedit[j] = 0;
                     testcomm[j]  = 0;
                     j = nbelem;
                  }
               }
            }
         }
      }
   }

// -------------------------------------------------------------------
// Go through the VS's and build up Teton VS array (ZoneToSrc)
// -------------------------------------------------------------------

   // Initialize all elements of 'zone ID' to 'VSP ID' mapping to zero
   // (NULL volume source profile)
   for ( i=0; i<nzones; ++i ) zonetosrc[i] = 0;

   // Loop over all volume source profiles
   // NOTE: We start the VSP index at one since zero refers to a NULL
   // volume source profile (convention defined by FORTRAN code)
   for ( i=1; i<=nvs; ++i ) {
     const TetonVolumeSource &TVS = VSList[i-1];
     // Loop over all zones associated with i-th volume source profile
     for ( j=0; j<TVS.zoneids.size(); ++j ) {
       // Set VSP associated with zone
       zonetosrc[TVS.zoneids[j]] = i;
     }
   }

// Set communication information for parallel runs
// The value of "ncomm" here may include domains connected only by nodes
// "ncomm" will be resized to the correct length in setCommunication

   ncomm   = M.getCommAgent().getFaceNeighborMap().numberOfSendProcesses();
   my_node = M.getCommAgent().getRank();
   n_Procs = M.getCommAgent().getNumberOfProcessors();

   nbshare = 0;
   for( i =0; i < nbelem ; i++) {
      if( testcomm[i] == 1 ) {
         nbshare++;
      }
   }
                                                                                       
   nodecomm.reserve(ncomm*2);
   cbdycomm.resize(nbshare);

// Set nodecomm and cbdycomm
   if (n_Procs > 1) {
      strncpy(decomp_s.data,"on      ",8);
      setCommunication(M, bdytof);
   }

// Construct Teton Modules
                                                                                       
   void *CSize;
   void *CGeometry;
   void *CMaterial;
   void *CEditor;

   setGroups(GList);
                                                                                       
   F77_ID(constructsize_, constructsize, CONSTRUCTSIZE)
         (&CSize,
          &my_node, &nzones, &ncornr, &nfaces, &npnts,
          &nbelem, &ndim, &maxcf, &ngr,
          &nangsn, &npsi, &ncomm, &nbshare, &nbedit,
          &tfloor, &tmin, igeom.data, ittyp.data, iaccel.data,
          imatc.data, iscat.data, itimsrc.data, decomp_s.data);
   Size = CSize;
                                                                                       
// Set the Quadrature module and resize arrays
   F77_ID(setsnorder_, setsnorder, SETSNORDER)
         (Size, Quadrature, &nangsn, &quaddef[0], &gnu[0]);
                                                                                       
   isTimeDep = ( strncmp(ittyp.data,  "timedep ",8) == 0);
   isExact   = ( strncmp(itimsrc.data,"exact   ",8) == 0);
   if ( isTimeDep && isExact ) {
      npsi = nangsn*ngr;
   }
   else {
      npsi = 1;
   }
                                                                                       
   resize();

   F77_ID(constructmaterial_, constructmaterial, CONSTRUCTMATERIAL)
         (Size, &CMaterial);
   Material = CMaterial;
                                                                                       
   F77_ID(constructeditor_, constructeditor, CONSTRUCTEDITOR)
         (Size, &CEditor);
   Editor = CEditor;

   F77_ID(constructgeometry_, constructgeometry, CONSTRUCTGEOMETRY)
         (Size, &CGeometry);
   Geometry = CGeometry;

   F77_ID(setgeometry_, setgeometry, SETGEOMETRY)
         (Size, Geometry,
          &nodecomm[0], &cbdycomm[0],
          &connect[0], &ctozone[0], &ctopoint[0], &ctoface[0], 
          &nfpc[0], &bdytoc[0], &bdytosrc[0], &bdytoedit[0],
          bdytobc[0].data, &zonetosrc[0], &px[0]);

// Release temporary variables
   tmpnode.resize(0);
   tmpcorner.resize(0);
   nfpc.resize(0);
   faceMap.resize(0);
   connect.resize(0);
   ctozone.resize(0);
   ctopoint.resize(0);
   bdytoc.resize(0);
   bdytof.resize(0);
   bdytosrc.resize(0);
   bdytoedit.resize(0);
   bdytobc.resize(0);
   testcomm.resize(0);
   cfaceNext1.resize(0);
   cfaceNext2.resize(0);
   cfaceID1.resize(0);
   cfaceID2.resize(0);
   ctoface.resize(0);
   cbdycomm.resize(0);
   zonetosrc.resize(0);
    
}

template <typename Mesh>
void
Teton<Mesh>::CInitMaterial (PartList<Mesh>  &realPartList) {
   int  nZones, zid , lenRho;
   double radcon;
   std::vector<double> volume;
   PartList<Mesh> *partList;
   size_t materialIndex = 0;

//   int elecion  = ( strncmp(imatc.data,"elec+ion",8) == 0 );
//   When we add ions, we will also need to initialize:
//   tiz, cvi, xomei, deniz, sion

   partList = &realPartList;
   lenRho   = rho.size();
   radcon   = 0.0137215980748942;
   erad     = 0.0;
   emat     = 0.0;

   volume.resize(lenRho);

// Initialize arrays to handle multi-material zones
   for(zid=0; zid<lenRho; zid++){
      rho[zid] = 0.0;
      cve[zid] = 0.0;
      tez[zid] = 0.0;
   }

   typename PartList<Mesh>::Iterator partPtr;
   for(partPtr =  partList->begin(); partPtr !=  partList->end(); partPtr++) {
// Go to the next material.
      ++materialIndex;
      const Region<Mesh> &r = partPtr->getRegion();
      const MeshType   &m = r.getMesh();
      typename Region<Mesh>::ZoneIterator zidP = r.internalZoneBegin();
      nZones = r.getNumberOfZones();
      if(nZones == 0){
          continue;
      }
      partPtr->setSpecificHeatCV ();
      const typename Part<Mesh>::ZonalScalarFieldType &SH = partPtr->getSpecificHeatCV ();
      const typename Part<Mesh>::ZonalScalarFieldType &MD = partPtr->getMassDensity ();
      const typename Part<Mesh>::ZonalScalarFieldType &T  = partPtr->getTemperature ();
      const typename Part<Mesh>::ZonalScalarFieldType &SE = partPtr->getSpecificEnergy ();
      for(; zidP != r.internalZoneEnd(); ++zidP) {
         zid  = m.getLocalID(*zidP);
         if (zid < lenRho) {
            rho[zid]    = rho[zid] + MD[*zidP];
            cve[zid]    = cve[zid] + MD[*zidP]*SH[*zidP];
            tez[zid]    = tez[zid] + MD[*zidP]*SH[*zidP]*T[*zidP];
            volume[zid] = zidP->getVolume();
            emat        = emat     + zidP->getVolume()*MD[*zidP]*SE[*zidP]; 
         }
      }
   }
       
   for(zid=0; zid<lenRho; zid++){
      tez[zid]   = tez[zid]/cve[zid];
      cve[zid]   = cve[zid]/rho[zid];
      trz[zid]   = tez[zid];
      denez[zid] = 0.0;
      selec[zid] = 0.0;
      erad       = erad + radcon*trz[zid]*trz[zid]*trz[zid]*trz[zid]*volume[zid];
   }

   F77_ID(setmaterialmodule_, setmaterialmodule, SETMATERIALMODULE)
         (Size, Material, 
          &siga[0], &sigs[0], &sigt[0], &cve[0], &rho[0],
          &selec[0], &denez[0], &trz[0], &tez[0], &tec[0], 
          &cvi[0], &xomei[0], &sion[0], &deniz[0], &tiz[0], &tic[0]);

                       
}

template <typename Mesh>
void
Teton<Mesh>::CupdateSn (PartList<Mesh>  &realPartList) {
   int  ig, nZones, zid , rzid, lenRho;
   int isScat = 0;
   double savecve;
   const double cvefloor=0.001;
   std::vector<double> opacA, opacS, rhoH, tempH;
   PartList<Mesh> *partList;
   size_t materialIndex = 0;

   partList = &realPartList;
   lenRho   = rho.size();

   isScat = ( strncmp(iscat.data,   "on      ", 8) == 0);

// Initialize opacities to handle multi-material zones
   for(zid=0; zid<lenRho; zid++){
      rho[zid]   = 0.0;
      cve[zid]   = 0.0;
      tez[zid]   = 0.0;
      selec[zid] = 0.0;
      for(ig=0; ig<ngr; ig++){
         siga[zid*ngr + ig] = 0.0;
         sigt[zid*ngr + ig] = 0.0;
         sigs[zid*ngr + ig] = 0.0;
      }
   }

   typename PartList<Mesh>::Iterator partPtr;
   for(partPtr =  partList->begin(); partPtr !=  partList->end(); partPtr++) {
// Go to the next material.
      ++materialIndex;
      const Region<Mesh> &r = partPtr->getRegion();
      const MeshType &m = r.getMesh();
      typename Region<Mesh>::ZoneIterator zidP = r.internalZoneBegin();
      nZones = r.getNumberOfZones();
      if(nZones == 0){
          continue;
      }
      opacA.resize(nZones*ngr);
      opacS.resize(nZones*ngr);
      rhoH.resize(nZones);
      tempH.resize(nZones);
      partPtr->setSpecificHeatCV ();
      typename Part<Mesh>::ZonalScalarFieldType &SH = partPtr->getSpecificHeatCV ();
      typename Part<Mesh>::ZonalScalarFieldType &MD = partPtr->getMassDensity ();
      typename Part<Mesh>::ZonalScalarFieldType &ET = partPtr->getElectronTemperature ();
      for(; zidP != r.internalZoneEnd(); ++zidP) {
         zid  = m.getLocalID(*zidP);
         rzid = r.getLocalID(*zidP);
         if (zid < lenRho) {
            rho[zid] = rho[zid] + MD[*zidP];
            cve[zid] = cve[zid] + MD[*zidP]*SH[*zidP];
            tez[zid] = tez[zid] + MD[*zidP]*SH[*zidP]*ET[*zidP];
         }
         rhoH[rzid]  = MD[*zidP];
         tempH[rzid] = ET[*zidP];
         for(ig=0; ig < ngr; ig++){
           opacS[rzid*ngr +ig] = 0.0;
         }
      }

      partPtr->getMaterial().getOpacity().getAbsorption (opacA, rhoH, tempH);
      if ( isScat ) {
        partPtr->getMaterial().getOpacity().getScattering (opacS, rhoH, tempH, tempH);
      }

      for(zidP=r.internalZoneBegin(); zidP != r.internalZoneEnd(); ++zidP) {
         zid = m.getLocalID(*zidP);
         rzid = r.getLocalID(*zidP);
         if (zid < lenRho) {
          for(ig=0; ig < ngr; ig++){
           siga[zid*ngr +ig] = siga[zid*ngr +ig] + MD[*zidP]*opacA[rzid*ngr +ig];
           sigs[zid*ngr +ig] = sigs[zid*ngr +ig] + MD[*zidP]*opacS[rzid*ngr +ig];
           sigt[zid*ngr +ig] = sigt[zid*ngr +ig] + MD[*zidP]*(opacA[rzid*ngr +ig] + opacS[rzid*ngr +ig]);
          }
         }
      }
   }

   for(zid=0; zid<lenRho; zid++){
      savecve  = cve[zid];
      tez[zid] = tez[zid]/savecve;
      cve[zid] = cve[zid]/rho[zid];
      if (cve[zid] < cvefloor) {
         cve[zid] = cvefloor;
      }
   }

}

template <typename Mesh>
void
Teton<Mesh>::CupdateSpecificEnergy(std::vector<double> &deltaEnergy,
                                   MeshType &psurface,
                                   PartList<Mesh>  &realPartList) {

   int  zid, nZones, ownedZones;
   double deltaSE, totalME, delME, oldSE, frac, VFmult;
   std::vector<double> tempSE, Edep;

   PartList<Mesh> *partList;
   partList = &realPartList;

   totalME      = 0.0;
   delME        = 0.0;

   ownedZones = psurface.getNumberOfOwnedZones();
   tempSE.resize(ownedZones);
   Edep.resize(ownedZones);

   for(zid=0; zid<ownedZones; zid++){
      tempSE[zid] = 0.0;
      Edep[zid]   = rho[zid]*(denez[zid] - deltaEnergy[zid]);
   }

   typename PartList<Mesh>::Iterator partPtr;
   for(partPtr =  partList->begin(); partPtr !=  partList->end(); partPtr++) {
      const Region<Mesh> &r = partPtr->getRegion();
      const MeshType     &m = r.getMesh();
      typename Region<Mesh>::ZoneIterator zidP =r.internalZoneBegin();
      nZones = r.getNumberOfZones();
      if(nZones == 0){
         continue;
      }
      typename Part<Mesh>::ZonalScalarFieldType &SH = partPtr->getSpecificHeatCV ();
      typename Part<Mesh>::ZonalScalarFieldType &T  = partPtr->getTemperature ();
      typename Part<Mesh>::ZonalScalarFieldType &MD = partPtr->getMassDensity ();
      typename Part<Mesh>::ZonalScalarFieldType &VF = partPtr->getVolumeFraction ();
      for(; zidP != r.internalZoneEnd(); ++zidP) {
         zid         = m.getLocalID(*zidP);
         if (Edep[zid] < 0.0) {
            VFmult = 0.5*(1.0 + VF[*zidP]);
         }
         else {
            VFmult = 1.0;
         }
         tempSE[zid] = tempSE[zid] + VFmult*MD[*zidP]*SH[*zidP]*T[*zidP];
      }
   }

   for(partPtr =  partList->begin(); partPtr !=  partList->end(); partPtr++) {
      const Region<Mesh> &r = partPtr->getRegion();
      const MeshType     &m = r.getMesh();
      typename Region<Mesh>::ZoneIterator zidP =r.internalZoneBegin();
      nZones = r.getNumberOfZones();
      if(nZones == 0){
         continue;
      }
      typename Part<Mesh>::ZonalScalarFieldType &SH = partPtr->getSpecificHeatCV ();
      typename Part<Mesh>::ZonalScalarFieldType &T  = partPtr->getTemperature ();
      typename Part<Mesh>::ZonalScalarFieldType &SE = partPtr->getSpecificEnergy ();
      typename Part<Mesh>::ZonalScalarFieldType &MD = partPtr->getMassDensity ();
      typename Part<Mesh>::ZonalScalarFieldType &ET = partPtr->getElectronTemperature ();
      typename Part<Mesh>::ZonalScalarFieldType &RT = partPtr->getRadiationTemperature ();
      typename Part<Mesh>::ZonalScalarFieldType &VF = partPtr->getVolumeFraction ();
      for(; zidP != r.internalZoneEnd(); ++zidP) {
         zid       = m.getLocalID(*zidP);
         if (Edep[zid] < 0.0) {
            VFmult = 0.5*(1.0 + VF[*zidP]);
         }
         else {
            VFmult = 1.0;
         }
         deltaSE   = VFmult*SH[*zidP]*T[*zidP]*Edep[zid]/tempSE[zid];
         SE[*zidP] = SE[*zidP] + deltaSE;

         totalME   = totalME + zidP->getVolume()*MD[*zidP]*SE[*zidP];
         delME     = delME   + zidP->getVolume()*MD[*zidP]*deltaSE;
         RT[*zidP] = trz[zid];
      }

      partPtr->setTemperature();

      for(zidP=r.internalZoneBegin(); zidP != r.internalZoneEnd(); ++zidP) {
         zid           = m.getLocalID(*zidP);
          T[*zidP]     = std::max(T[*zidP], tfloor);
         ET[*zidP]     = T[*zidP];
      }
        
      partPtr->setPressure();
      partPtr->setSoundSpeed();
      partPtr->setGamma();
   }

}

template <typename Mesh>
void
Teton<Mesh>::CsetControls() {

   void *CIterControls;
   void *CDtControls;

   F77_ID(resetsize_, resetsize, RESETSIZE)
         (Size,
          &tfloor, &tmin, igeom.data, ittyp.data, iaccel.data,
          imatc.data, iscat.data, itimsrc.data, decomp_s.data);

   F77_ID(constructitercontrols_, constructitercontrols, CONSTRUCTITERCONTROLS)
         (&noutmx, &ninmx, &ngdamx,
          &epstmp, &epsinr, &epsgda,
          &CIterControls);

   F77_ID(constructdtcontrols_, constructdtcontrols, CONSTRUCTDTCONTROLS)
         (&dtrad, &dtrmn, &dtrmx, &delte, &deltr,
          &CDtControls);

   IterControls = CIterControls;
   DtControls   = CDtControls;

}


