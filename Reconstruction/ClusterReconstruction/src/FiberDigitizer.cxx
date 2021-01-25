#include "FiberDigitizer.h"

#include "edm4hep/Vector3f.h"

FiberDigitizer::FiberDigitizer():
  m_debug(false)
{}

FiberDigitizer::~FiberDigitizer()
{}

bool FiberDigitizer::Digitize(const edm4hep::SimCalorimeterHitCollection& i_coll, edm4hep::CalorimeterHitCollection& o_coll)
{
  
  for (auto& sim_hit : i_coll){
    auto o_coll_elem = o_coll.create();
    o_coll_elem.setEnergy(sim_hit.getEnergy());
    o_coll_elem.setTime(0); // No real time information to be set for the moment --> TO BE UNDERSTOOD
    o_coll_elem.setEnergyError(0); // don't really know what to use for the energy error
    o_coll_elem.setCellID(sim_hit.getCellID());
    o_coll_elem.setPosition(sim_hit.getPosition());
    o_coll_elem.setType(0); // Not clear what the type is for the moment, setting it here to remember to set it to something sensible at some point
  }

  return true;
}

bool FiberDigitizer::Calibrate(edm4hep::CalorimeterHitCollection& l_coll, DRCalo_FiberType l_type)
{
  static float l_cal;
  l_cal = 0;
  static edm4hep::Vector3f t_edm_vec;
  static TVector3 t_vec;

  for (unsigned int i = 0; i < l_coll.size(); ++ i){ //auto& s_hit : l_coll){
    t_edm_vec = l_coll.at(i).getPosition();
    t_vec.SetXYZ(t_edm_vec.x,t_edm_vec.y,t_edm_vec.z);
    if (m_debug){
      std::cout << "Hit position (theta, phi)" << t_vec.Theta() << "\t" << t_vec.Phi() << std::endl;
      std::cout << "Hit energy before calibration" << l_coll.at(i).getEnergy() << std::endl;
    }
    l_cal = m_geomHelper.GetCalibrationConstant(t_vec,l_type);
    if (l_cal != 0) {
      l_coll.at(i).setEnergy(l_coll.at(i).getEnergy()/l_cal);
    } else {
      std::cerr << "ClusterFiberCalibrate: calibration constant 0 for direction (x,y,z) " << t_vec.X() << " " << t_vec.Y() << " " << t_vec.Z() << std::endl;
      l_coll.at(i).setEnergy(0);
    }
    if (m_debug) std::cout << "Hit energy after calibration " << l_coll.at(i).getEnergy() << std::endl;

  }
  return true;
}


  
  


  

