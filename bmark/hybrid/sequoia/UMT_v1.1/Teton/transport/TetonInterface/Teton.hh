//---------------------------------*-C++-*----------------------------------//
// Copyright 1998 The Regents of the University of California.
// All rights reserved.
//
// Created on: May 1998
// Created by:  Pat Miller
// Also maintained by: Michael Nemanic
//--------------------------------------------------------------------------//

#ifndef __TETON_TETON_HH__
#define __TETON_TETON_HH__

#include "utilities/KullTypes/CharStar8.hh"
#include "transport/TetonInterface/TetonFreq.hh"
#include "transport/TetonInterface/TetonBoundary.hh"
#include "transport/TetonInterface/TetonVolumeSource.hh"
#include "transport/TetonInterface/TetonProfile.hh"
#include <vector>

#include "geom/Field/Field.hh"
#include "part/PartList.hh"
#include "geom/Region/PolyhedralRegion.hh"
#include "geom/Region/PolygonalRZRegion.hh"
#include "part/Part.hh"

using namespace Geometry;

// used in linkKull to hold the boundry condition and side mappings.
typedef struct BChold {
     int kface;
     CharStar8 iptype;
     int prof;
} BCH;
typedef struct BCside {
     int side;
     int kface;
} BCS;


template <typename Mesh>
class Teton {
//--------------------------------------------------------------------------//
//  Teton Sn Radiation Transport Module
//    The class provides the methods, variables, and interfaces to support
//   the SN module for KULL.
//------------------------------------------------------------------------ -//
public:
   // Just 3D arbitraries for now....
   typedef  Mesh       MeshType;
   typedef  typename MeshType::SideHandle   Side;
   typedef  typename MeshType::FaceHandle   Face;
   typedef  typename MeshType::ZoneHandle   Zone;
   typedef  typename MeshType::CornerHandle Corner;
   typedef  typename MeshType::EdgeHandle   Edge;
   typedef  typename MeshType::NodeHandle   Node;
   typedef  typename MeshType::ScalarType   Scalar;

   typedef Field<MeshType, Zone, Scalar> MeshZCSF;
   typedef Field<MeshType, Face, int>    MeshFCiF;

   typedef Region<Mesh>   RegionType;

   typedef std::map<size_t, std::vector<Face> > CommMapType;

   Teton();
   ~Teton() {}

   void resize();

   // routines wrapped to call fortran.  Radtr is interface
   // into Teton.
   double cxxRadtr();

   // used to setup Teton region, group and boundary condition vars.
   void setBCs( std::vector<TetonBoundary> &);
   void setVSs( std::vector<TetonVolumeSource> &);
   void setAProfile( TetonProfile &, int);
   void setGroups(const std::vector<TetonFreq> &);

   // set Teton node positions 
   void setMeshSizeAndPositions(MeshType &,
                                std::vector<int> &);

   // communication
   void setCommunication(MeshType &,
                         std::vector<int> &);

   // set up the mesh connectivity arrays used in Teton.
   void linkKull(MeshType &,
                 const std::vector<TetonFreq> &,
                 std::vector<TetonBoundary> &,
                 std::vector<TetonVolumeSource> &,
                 std::vector<int> &);
    
   // update opacity, density etc following Hydro prior to SN step.
   void CInitMaterial(PartList<Mesh> &);

   // update opacity, density etc following Hydro prior to SN step.
   void CupdateSn(PartList<Mesh> &);

   // update Hydro var as a result of the Teton step
   void CupdateSpecificEnergy(std::vector<double> &,
                              MeshType &,
                              PartList<Mesh> &);

   // create IterControl/DtControl object used in Teton for
   // iteration/time-step control etc.  called from shadowteton.py
   void CsetControls();


   // ------------------------------------------------------------
   // Computed from other inputs (in resize)
   // ------------------------------------------------------------
   int          ndim;           // number of spatial dimensions (1,2, or 3)
   // ------------------------------------------------------------
   // Need these to get going
   // ------------------------------------------------------------
   int          nbc;            // number of boundary condition profiles
   int          nvs;            // number of volume source profiles
   // ------------------------------------------------------------
   int          my_node;        // Node number (set to 0 for a serial)
   int          n_Procs;        // number of MPI processes (set to 1 for a serial)
   // ------------------------------------------------------------
   int          ncycle;         // radiation cycle number (host increment)
   int          nbelem;         // number of boundary elements 
   int          nzones;         // number of spatial zones
   int          ncornr;         // number of corners
   int          npnts;          // number of points
   int          nfaces;         // number of faces
   int          nbedit;         // number of boundary edits
   int          ngr;            // number of radiation groups
   int          nangsn;         //
   int          noutmx;         // max number of outer (temperature) iterations
   int          ninmx;          // max number of inner (intensity) per outer iter
   int          ngdamx;         // max number of grey-acceleration iterations per inner iter
   // ------------------------------------------------------------
   int          nprof;          // total number of profiles
   int          GTAorder;       // quadrature order used for grey transport acceleration (def=2 for s2 acc)
   int          npsi;           // second dimension of psir (nangsn*ngr if storing angle dependent intensity, else 1)
   int          noutrt;         // Number of temperature (outer) iterations performed this cycle
   int          ninrt;          // Number of radiation intensity (inner) iterations performed this cycle
   int          ngdart;         // Number of grey-acceleration iterations performed this cycle
   int          TrMaxZone;      // Zone with the largest radiation temperature
   int          TeMaxZone;      // Zone with the largest electron temperature
   int          TiMaxZone;      // Zone with the largest ion temperature
   int          TrMaxNode;      // NodeID with the largest radiation temperature
   int          TeMaxNode;      // NodeID with the largest electron temperature
   int          TiMaxNode;      // NodeID with the largest ion temperature
   // ------------------------------------------------------------
   int          ConvControlNode;   // NodeID controlling convergence
   int          ConvControlZone;   // Zone controlling convergence
   int          DtControlNode;     // NodeID controlling the time step
   int          DtControlZoneTr4;  // Zone with max Tr4 change on DtControlNode
   int          DtControlZoneTe;   // Zone with max Te change on DtControlNode
   // ------------------------------------------------------------
   double       ConvControlError;   // Max relative error
   double       ConvControlTr;      // Radiation temperature of controlling zone 
   double       ConvControlTe;      // Electron temperature of controlling zone
   double       ConvControlRho;     // Density of controlling zone
   double       ConvControlCve;     // Specific heat of controlling zone
   double       ConvControlEdep;    // External energy deposition rate
   double       DtControlChangeTr4; // Max change in Tr4 of controlling zone
   double       DtControlChangeTe;  // Max change in Te of controlling zone
   double       DtControlTr;        // Radiation temperature of controlling zone
   double       DtControlTe;        // Electron temperature of controlling zone
   double       DtControlTrOld;     // Previous Radiation temperature of controlling zone
   double       DtControlTeOld;     // Previous Electron temperature of controlling zone
   // ------------------------------------------------------------
   double       erad;           // (E) Total energy in the radiation field
   double       emat;           // (E) Total energy in the material
   double       eradinct;       // (E) Total energy incident on the problem
   double       eradesct;       // (E) Total energy that escaped the problem
   double       eextsrc;        // (E) External energy source
   double       echeck;         // (E) Energy error
   double       TrMax;          // (T) Maximum zonal radiation temperature
   double       TeMax;          // (T) Maximum zonal electron temperature
   double       TiMax;          // (T) Maximum zonal ion temperature
   double       tfloor;         // (T) Temperature floor
   double       tmin;           // (T) Minimum temperature for time step/convergence control
   double       dtrad;          // (t) Radiation timestep
   double       epstmp;         // Convergence criterion for the temperature (outer) iteration
   // ------------------------------------------------------------
   double       epsinr;         // Convergence criterion for the intensity (inner) iteration
   double       epsgda;         // Convergence criterion for the grey-acceleration calculation
   double       delte;          // Maximum fractional change allowed per cycle in the material temperature
   double       deltr;          // Maximum fractional change allowed per cycle in the radiation energy density
   double       timerad;        // (t) Problem time
   double       angleLoopTime;  // (t) time spent in loop over angles in snflwxyz.F90
   double       dtrmn;          // (t) Minimum allowed radiation timestep
   double       dtrmx;          // (t) Maximum allowed radiation timestep
   CharStar8    igeom;          // Geometry flag (1D--slab, sphere, cylinder; 2D--rz; 3D--xyz)
   CharStar8    ittyp;          // Time-dependence flag (timedep, stdyst)
   CharStar8    iaccel;         // Iterative acceleration flag (gda,off)
   CharStar8    imatc;          // Material coupling flag (elec, elec+ion, off)
   CharStar8    iscat;          // Scattering treatment flag (on,off)
   CharStar8    itimsrc;        // Treatment of the time-dependent source (exact, moments, zonal)
   CharStar8    decomp_s;       //
   CharStar8    ConvControlReason;  // What's controlling convergence
   CharStar8    DtControlReason;    // What's controlling the time step
   // ---------------  Teton Modules  ----------------------------
   void *       IterControls;   // iteration control list module   
   void *       DtControls;     // time step controls module
   void *       Size;           // run parameters module
   void *       Geometry;       // geometry and connectivity module
   void *       Material;       // material properties module 
   void *       Quadrature;     // quadrature module
   void *       Editor;         // edit module
   void *       Profile;        // source profile module
   // ------------------------------------------------------------
   std::vector<int>  quaddef;        // [ngr] Sn order for each group
   // ------------------------------------------------------------
   std::vector<double> psir;         // [nangsn,ncornr,ngr] (E/A/t/ster) Angle-dependent flux
   std::vector<double> phir;         // [ngr,ncornr] (E/A/t) Flux moments
   std::vector<double> RadSpecificEnergy; // [nzones,ngr] the zone-averaged flux by Enrgy group
   std::vector<double> tec;          // [ncornr] (T) Corner electron temperature
   std::vector<double> tic;          // [ncornr] (T) Corner ion temperature
   std::vector<double> curesc;       // [nbedit+1,ngr] (E/t) instantanious rate of radiation energy escaping
   // ------------------------------------------------------------
   std::vector<double> curinc;       // [nbedit+1,ngr] (E/t) instantanious rate of radiation energy incident
   std::vector<double> eradesc;      // [nbedit+1,ngr] (E) Time-integrated radiation energy escaping
   std::vector<double> eradinc;      // [nbedit+1,ngr] (E)Time-integrated radiation energy incident
   std::vector<double> denez;        // [nzones] (E/m) Zone-average specific electron energy change
   std::vector<double> deniz;        // [nzones] (E/m) Zone-average specific ion energy change
   std::vector<double> trz;          // [nzones] (T) Zone-average radation temperature
   std::vector<double> tez;          // [nzones] (T) Zone-average energy temperature
   std::vector<double> tiz;          // [nzones] (T) Zone-average ion temperature
   std::vector<double> px;           // [ndim,npnts] (L) Point coordinates 1d-r or x 2d-r,z 3d-x,y,z
   // ------------------------------------------------------------
   std::vector<double> siga;         // [nzones,ngr] (1/L) Absorption cross section
   std::vector<double> sigt;         // [nzones,ngr] (1/L) Total cross section
   std::vector<double> sigs;         // [nzones,isctp1,ngr] (1/L) Scattering cross section
   std::vector<double> cve;          // [nzones] (E/m/T) Electron specific heat
   std::vector<double> cvi;          // [nzones] (E/m/T) Ion specific heat
   std::vector<double> rho;          // [nzones] (m/V) Material density
   std::vector<double> xomei;        // [nzones] (E/m/T/t) Electron/ion Coulomb coupling coefficient
   std::vector<double> selec;        // [nzones] (E/m/t) Specific energy rate to electrons
   std::vector<double> sion;         // [nzones] (E/m/t) Specific energy rate to ions
   std::vector<double> gnu;          // [ngr+1] (e) Photon energy group boundaries
   // ------------------------------------------------------------
   int          ncomm;               // number of communication neighbors
   int          nbshare;             // tot num of shared boundary elements.
   int          maxcf;               // maximum number of corner faces
   std::vector<int>  nodecomm;       // [2*ncomm] neighbor#,#shared bdyelems.
   std::vector<int>  cbdycomm;       // boundary comms - (nbshare)
   std::vector<int>  nfpc;           // number of corner faces per corner [ncornr]
   std::vector<int>  connect;        // corner to corner connectivity - (4,maxcf,ncornr)
   std::vector<int>  ctoface;        // corner to face -  (maxcf,ncornr)
   std::vector<int>  ctozone;        // corner to zone - (ncornr)
   std::vector<int>  ctopoint;       // corner to point - (ncornr)
   std::vector<int>  bdytoc;         // boundary to corner - (2,nbelem)
   std::vector<int>  bdytosrc;       // boundary to source - (nbelem)
   std::vector<int>  bdytoedit;      // boundary to edit - (nbelem)
   std::vector<CharStar8>  bdytobc;  // boundary to boundary condition (nbelem)
   std::vector<int>  zonetosrc;      // zone to source - (nzones)
};  

#endif                   // __TETON_TETON_HH__
