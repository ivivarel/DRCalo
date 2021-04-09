#ifndef DR_CALOGRIDHELPER_H
#define DR_CALOGRIDHELPER_H

#include "edm4hep/ClusterCollection.h"
#include "edm4hep/CalorimeterHit.h"

#include <TString.h>
#include <TH2F.h>

#include <map>
#include <memory>

typedef   std::map<unsigned long long, double > DR_CaloGrid;
typedef unsigned long long DR_GridID;

class DR_CaloGridHelper
{
  // The idea of this class is to create a grid to aid the reconstruction with an easy and efficient way
  // to establish topologies and distances between energy deposits.
  // This class defines a grid in theta and phi given a distance parameter assumed to be the radius of a circle
  // at a distance of 2.5 m from the collision points.

 public: 
  DR_CaloGridHelper(double distPar = 5.);
  ~DR_CaloGridHelper() {};

  double GetCosTheta(DR_GridID id);
  double GetTheta(DR_GridID id);
  double GetPhi(DR_GridID id);
  DR_GridID GetID(float theta, float phi);
  double GetEnergy(DR_GridID id);
  double GetEnergy(float theta, float phi);
  void SetDistanceParameter(double dp) {m_rm = dp;};
  void CreateGrid();
  double GetDelta() {return m_delta;}
  void Add(float theta, float phi, float energy);
  void Add(const edm4hep::CalorimeterHit & caloHit); 
  void Reset();
  DR_CaloGrid &  GetGrid() {return m_caloGrid;}
  void EventDisplay(TString filename);
  void Print();
 
  
 private:
  DR_CaloGrid m_caloGrid;
  double m_rm; // Distance parameter that generates the grid
  double m_caloEffDist; // Effective distance of the calorimeter (assumed to be spherical). This parameter is hard coded (no accessor for it).
  double m_delta;
  unsigned int m_spacing; // Parameter used to encode eta and phi in the ID
  void CreateEntry(DR_GridID gridID);
};

#endif // ifndef DR_CALOGRIDHELPER_H   
