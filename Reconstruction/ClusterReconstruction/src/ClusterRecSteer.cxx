#include "ClusterRecSteer.h"

#include "DRCalo_FiberType.h"

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"

#include <iostream>

bool ClusterRecSteer::Process()
{

  unsigned int nevents = m_reader.getEntries();

  // main loop over events

  for (unsigned int i_evt = 0; i_evt < nevents; ++i_evt){

    // retrieve the simulation hits
    
    auto & s_hitColl = m_read_store.get<edm4hep::SimCalorimeterHitCollection>(m_inputScintHitsName);

    auto & c_hitColl = m_read_store.get<edm4hep::SimCalorimeterHitCollection>(m_inputCherHitsName);

    if (!s_hitColl.isValid()){
      std::cerr << "Cannot read S simulation hits with name " << m_inputScintHitsName << std::endl;
      return false;
    }

    if (!c_hitColl.isValid()){
      std::cerr << "Cannot read C simulation hits with name " << m_inputCherHitsName << std::endl;
      return false;
    }

    if (m_debug) {
      std::cout << "Number of s fibers fired " << s_hitColl.size() << std::endl;
      std::cout << "Number of c fibers fired " << c_hitColl.size() << std::endl;
    }

    // Now create the CalorimeterHits. This should actually be a digitisation step at some point, but for the moment it is dummy

 
    std::cout << "Energy of the first hit = " << s_hitColl[0].getEnergy() << std::endl;

    auto& caloHits = m_store.create<edm4hep::CalorimeterHitCollection>("s_recoCaloHits");
    auto caloHit = caloHits.create();
    caloHit.setEnergy(1000);

    /*    m_calibrator.SetStore(&m_store);
    m_calibrator.SetCaloHitCollectionName("s_recoCaloHits");
    m_calibrator.Calibrate(s_hitColl,DRCalo_FiberType::S);
    // Now retrieve the calibrated collection
    */

    auto& caloHitCollection = m_store.get<edm4hep::CalorimeterHitCollection>("s_recoCaloHits");
 
    if (caloHitCollection.isValid()){
      std::cout << "After calibration = " << caloHitCollection[0].getEnergy() << std::endl;
    } else {
      std::cout << "WTF????" << std::endl;
    }
    
    // Calibrate the hits 
    
    /*    for (auto s_hit : s_hitColl){
      std::cout << s_hit.getEnergy() << std::endl;
      }*/
    m_read_store.clear();
    m_store.clear();
    m_reader.endOfEvent();
  }
  
  return true;
}

ClusterRecSteer::ClusterRecSteer():
  m_inputCherHitsName("C_SimCalorimeterHits"),
  m_inputScintHitsName("S_SimCalorimeterHits"),
  m_debug(false)
{
}

ClusterRecSteer::~ClusterRecSteer()
{}

bool ClusterRecSteer::LoadFile(std::string input_file_name)
{
  m_reader.openFile(input_file_name);

  m_read_store.setReader(&m_reader);

  unsigned int nevents = m_reader.getEntries();
  std::cout << "Loaded file " << input_file_name << " with " << nevents << " entries " << std::endl;
  
  return true;
}

bool ClusterRecSteer::CloseFile()
{
  m_reader.closeFile();
  return true;
}
