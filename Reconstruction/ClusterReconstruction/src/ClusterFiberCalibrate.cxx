#include "ClusterFiberCalibrate.h"

#include "TVector3.h"

#include "edm4hep/Vector3f.h"
#include "edm4hep/CalorimeterHitCollection.h"

ClusterFiberCalibrate::ClusterFiberCalibrate():
  m_caloHitCollectionName("s_recCalorimeterHits")
{}

ClusterFiberCalibrate::~ClusterFiberCalibrate()
{}

void ClusterFiberCalibrate::Calibrate(const edm4hep::SimCalorimeterHitCollection& l_coll, DRCalo_FiberType l_type)
{
  float l_cal = 0;
  TVector3 t_vec;
  edm4hep::Vector3f t_edm_vec;

  auto& caloHits = m_store->create<edm4hep::CalorimeterHitCollection>(m_caloHitCollectionName);
  
  for (auto& s_hit : l_coll){
    t_edm_vec = s_hit.getPosition();
    t_vec.SetXYZ(t_edm_vec.x,t_edm_vec.y,t_edm_vec.z);
    l_cal = m_geomHelper.GetCalibrationConstant(t_vec,l_type);
    auto caloHit = caloHits.create();
    caloHit.setPosition(t_edm_vec);
    if (l_cal != 0) caloHit.setEnergy(s_hit.getEnergy()/l_cal);
    else {
      std::cerr << "ClusterFiberCalibrate: calibration constant 0 for direction (x,y,z) " << t_vec.X() << " " << t_vec.Y() << " " << t_vec.Z() << std::endl;
      caloHit.setEnergy(0);
    }
  }
}


  
  


  
