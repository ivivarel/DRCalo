#ifndef DR_FIBERDIGITIZER
#define DR_FIBERDIGITIZER

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"

#include "DRCalo_FiberType.h"
#include "DR_GeometryHelper.h"

class FiberDigitizer
{
  // This class is made to create a CalorimeterHitCollection starting from a SimCalorimeterHitCollection.
  // At some point it will be replaced by a real digitization.
  
public: 
  FiberDigitizer();
  ~FiberDigitizer();
  
  bool Digitize(const edm4hep::SimCalorimeterHitCollection& i_coll, edm4hep::CalorimeterHitCollection& o_coll);
  bool Calibrate(edm4hep::CalorimeterHitCollection& l_coll, DRCalo_FiberType l_type);
  void setDebug(bool debug = true){m_debug = debug;}
private:
  bool m_debug;
  DR_GeometryHelper m_geomHelper;
 };

#endif
  
  


  
