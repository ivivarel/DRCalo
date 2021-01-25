#include "DR_CaloGridHelper.h"

#include <TMath.h>

#include <iostream>

DR_CaloGridHelper::DR_CaloGridHelper(double distPar):
  m_rm(distPar), m_caloEffDist(2500.),m_delta(0), m_spacing(1000000)
{
}

void DR_CaloGridHelper::CreateGrid()
{
  m_delta = TMath::Sqrt(TMath::Pi()) * m_rm/m_caloEffDist; // This follows from requiring the area of a circle of radius m_rm being equal to the element of area m_caloEffDist^2 * d cos theta * dphi and setting both d cos theta and dphi equal to m_delta
  std::cout << m_delta << std::endl;
}

unsigned long long DR_CaloGridHelper::GetID(float theta, float phi)
{
  // Make sure that theta and phi are defined between 0 and pi and 0-2pi

  if (phi < 0) phi = phi + 2*TMath::Pi();
  if (theta < 0) {
    std::cerr << "DR_CaloGridHelper::GetID: theta should be positively defined and instead it is " << theta << std::endl;
    std::cerr << "Things are going to go horribly wrong" << std::endl;
    return 0;
  }
  if (m_delta == 0){
    std::cerr << "DR_CaloGridHelper::GetID : m_delta has an illegal value " << m_delta << ". Perhaps you forgot to call CreateGrid?" << std::endl;
    return 0;
  }
  
  //  std::cout << "phi " << phi << " m_delta " << m_delta << " ratio " << phi/m_delta << std::endl;
  unsigned long long   int_phi = static_cast<unsigned long long>(phi/m_delta);  
  unsigned long long  int_costheta = static_cast<unsigned long long>((TMath::Cos(theta)+1.)/m_delta);

  /*std::cout << "int_phi " << int_phi << std::endl;
    std::cout << "int_costheta " << int_costheta << std::endl;*/
  
  return  int_phi + int_costheta*m_spacing;
}

double DR_CaloGridHelper::GetCosTheta(unsigned long long id)
{
  return static_cast<double>((id/m_spacing))*m_delta -1;
}

double DR_CaloGridHelper::GetTheta(unsigned long long id)
{
  return TMath::ACos(GetCosTheta(id));
}

double DR_CaloGridHelper::GetPhi(unsigned long long id)
{
  return (id%m_spacing)*m_delta;
}

double DR_CaloGridHelper::GetEnergy(unsigned long long id)
{
  if (m_caloGrid.find(id) == m_caloGrid.end()) return 0;
  return m_caloGrid[id];
}

double DR_CaloGridHelper::GetEnergy(float theta, float phi)
{
  return GetEnergy(GetID(theta,phi));
}

void DR_CaloGridHelper::Add(float theta, float phi, float energy)
{
  m_caloGrid[GetID(theta,phi)] = energy + GetEnergy(GetID(theta,phi)); // This now assumes that the individual elements of the grid should be massless. I believe this is the right thing to do (for example, it wouldn't make sense to sum the 4-vectors of the individual fiber, if the fibers arise from a single particle). In any case, the effect should be very small for small size of the grid elements
}



