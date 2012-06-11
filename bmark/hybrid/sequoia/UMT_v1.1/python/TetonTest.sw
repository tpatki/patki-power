#ifndef __SWIG_TetonTest_
#define __SWIG_TetonTest_
%module TetonTest

%include "std_vector.i"
%include "std_string.i"

%include "utilities/KullTypes/swig/CharStar8.sw"
%include "geom/CMI/swig/MeshBase.sw"
%include "geom/CMI/swig/ZoneBase.sw"
%include "transport/TetonInterface/swig/Teton.sw"
%include "transport/TetonInterface/swig/TetonFreq.sw"
%include "transport/TetonInterface/swig/TetonBoundary.sw"
%include "transport/TetonInterface/swig/TetonVolumeSource.sw"
%include "part/swig/Part.sw"
%include "part/swig/OpacityBase.sw"
%include "part/swig/Material.sw"

%template(TimeTempsVector) std::vector<double>;
%template(Teton_MeshBase) Teton<Geometry::MeshBase>;
%template(TetonBoundaryVector) std::vector<TetonBoundary>;
%template(TetonFreqVector) std::vector<TetonFreq>; 
%template(TetonVolumeSourceVector) std::vector<TetonVolumeSource>; 
%template(Region_MeshBase) Geometry::Region<Geometry::MeshBase>;
%template(Part_MeshBase) Part<Geometry::MeshBase>; 
%template(PartList_MeshBase) PartList<Geometry::MeshBase>;
%template (IntVector) std::vector<int> ;
%template (ZoneVector) std::vector<ZoneBase> ;
%template (StringVector) std::vector<std::string> ;

%{
#include "TetonUtils.hh"
%}

%include "TetonUtils.hh"

#endif
