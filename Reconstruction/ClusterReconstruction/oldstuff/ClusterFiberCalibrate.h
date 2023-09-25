#ifndef DR_CLUSTERFIBERCALIBRATE
#define DR_CLUSTERFIBERCALIBRATE

#include "edm4hep/SimCalorimeterHitCollection.h"

#include "DRCalo_FiberType.h"
#include "DR_GeometryHelper.h"

#include "podio/EventStore.h"

class ClusterFiberCalibrate
{
  // The objective of this class is to get a collection of uncalibrated fibers and calibrated it
 public: 
  ClusterFiberCalibrate();
  ~ClusterFiberCalibrate();
  
  void SetCaloHitCollectionName(std::string l_name){m_caloHitCollectionName = l_name;}
  void Calibrate(const edm4hep::SimCalorimeterHitCollection& l_coll, DRCalo_FiberType l_type);
  void SetStore(podio::EventStore * l_eventStore){m_store = l_eventStore;}

 private:
  DR_GeometryHelper m_geomHelper;
  std::string m_caloHitCollectionName;
  podio::EventStore * m_store; 
};

#endif
  
  


  
