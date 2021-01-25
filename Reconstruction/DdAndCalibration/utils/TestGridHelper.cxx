#include "DR_CaloGridHelper.h"

#include <iostream>

int main()
{
  DR_CaloGridHelper mygrid(2.5);
  mygrid.CreateGrid();
  std::cout << "m_delta = " << mygrid.GetDelta() << std::endl;
  std::cout << "GetId (1.6,0) " << mygrid.GetID(1.6,0) << std::endl;
  std::cout << "GetPhi(1) " << mygrid.GetPhi(1) << std::endl;
  std::cout << "GetPhi(5000) " << mygrid.GetPhi(5000) << std::endl;
  std::cout << "GetCosTheta(5000) " << mygrid.GetCosTheta(5000) << std::endl;
  std::cout << "GetCosTheta(5000000) " << mygrid.GetCosTheta(5000000) << std::endl;
  std::cout << "GetTheta(5000000) " << mygrid.GetTheta(5000000) << std::endl;
  std::cout << "GetID(3.00836,0)" << mygrid.GetID(3.00836,0) << std::endl;
  mygrid.Add(1.6,0,10000);
  std::cout << "GetEnergy(0.1,0.1) " << mygrid.GetEnergy(0.1,0.1) << std::endl;
  std::cout << "GetEnergy(1.6,0)" << mygrid.GetEnergy(1.6,0) << std::endl;
  mygrid.Add(1.6,0,10000);
  std::cout << "GetEnergy(1.6,0)" << mygrid.GetEnergy(1.6,0) << std::endl;
  return 0;
}
  
  
