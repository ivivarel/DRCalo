#ifndef DR_CALOGRIDHELPER_H
#define DR_CALOGRIDHELPER_H

#include <map>

class DR_CaloGridHelper
{
  // The idea of this class is to create a grid to aid the reconstruction with an easy and efficient way
  // to establish topologies and distances between energy deposits.
  // This class defines a grid in theta and phi given a distance parameter assumed to be the radius of a circle
  // at a distance of 2.5 m from the collision points.

 public: 
  DR_CaloGridHelper(double distPar = 5.);
  ~DR_CaloGridHelper() {};

  double GetCosTheta(unsigned long long id);
  double GetTheta(unsigned long long id);
  double GetPhi(unsigned long long id);
  unsigned long long GetID(float theta, float phi);
  double GetEnergy(unsigned long long id);
  double GetEnergy(float theta, float phi);
  void SetDistanceParameter(double dp) {m_rm = dp;};
  void CreateGrid();
  double GetDelta() {return m_delta;}
  void Add(float theta, float phi, float energy);
  
 private:
  std::map<unsigned long long, double> m_caloGrid;
  double m_rm; // Distance parameter that generates the grid
  double m_caloEffDist; // Effective distance of the calorimeter (assumed to be spherical). This parameter is hard coded (no accessor for it).
  double m_delta;
  unsigned int m_spacing;
};

#endif // ifndef DR_CALOGRIDHELPER_H   
