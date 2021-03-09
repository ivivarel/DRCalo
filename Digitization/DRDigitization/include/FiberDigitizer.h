#ifndef DR_FIBERDIGITIZER
#define DR_FIBERDIGITIZER

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"

#include "DRCalo_FiberType.h"
#include "DR_GeometryHelper.h"

#include "SiPMAnalogSignal.h"
#include "SiPMProperties.h"
#include "SiPMSensor.h"

class FiberDigitizer
{
  // This class is made to create a CalorimeterHitCollection starting from a SimCalorimeterHitCollection.
  // At some point it will be replaced by a real digitization.
  
public: 
  FiberDigitizer();
  ~FiberDigitizer();
  
  void Digitize(const edm4hep::SimCalorimeterHitCollection& i_coll, edm4hep::CalorimeterHitCollection& o_coll);
  bool Calibrate(edm4hep::CalorimeterHitCollection& l_coll, DRCalo_FiberType l_type);
  void SetDebug(bool debug = true){m_debug = debug;}
  sipm::SiPMSensor * GetSensor() {return m_sensor;}
  void SetSiPMSensor(sipm::SiPMSensor * l_sensor) {m_sensor = l_sensor;}
  
private:
  bool m_debug;
  DR_GeometryHelper m_geomHelper;
  sipm::SiPMSensor * m_sensor;
  
 };

#endif
  
  


  
