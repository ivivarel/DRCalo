#include "FiberDigitizeAndCalibrate.h"

#include "DRCalo_FiberType.h"

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CalorimeterHitCollection.h"

#include <iostream>

bool FiberDigitizeAndCalibrate::Process()
{

  unsigned int nevents = m_reader.getEntries();
  podio::EventStore l_store;
  podio::ROOTWriter l_writer("output.root",&l_store);


  auto& s_caloHits = l_store.create<edm4hep::CalorimeterHitCollection>( m_outputScintHitsName );
  l_writer.registerForWrite(m_outputScintHitsName);
    

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

    // Now create the CalorimeterHitCollection and pass them to a (dummy) digitization step that will fill them.
 
    std::cout << "Energy of the first hit = " << s_hitColl[0].getEnergy() << std::endl;


    double energy = -1;
    
    
    for (auto simHit : s_hitColl){
      auto caloHit = s_caloHits.create();
      caloHit.setEnergy(simHit.getEnergy());
    }
     // Calibrate the hits 
    std::cout << s_caloHits.size() << std::endl;
    std::cout << s_hitColl.size() << std::endl;

    l_writer.writeEvent();
    m_read_store.clear();
    m_reader.endOfEvent();
    l_store.clearCollections();
  }
  l_writer.finish();
  return true;
}

FiberDigitizeAndCalibrate::FiberDigitizeAndCalibrate():
  m_inputCherHitsName("C_SimCalorimeterHits"),
  m_inputScintHitsName("S_SimCalorimeterHits"),
  m_outputCherHitsName("C_CalorimeterHits"),
  m_outputScintHitsName("S_CalorimeterHits"),
  m_debug(false)
{
}

FiberDigitizeAndCalibrate::~FiberDigitizeAndCalibrate()
{}

bool FiberDigitizeAndCalibrate::LoadFile(std::string input_file_name)
{
  m_reader.openFile(input_file_name);

  m_read_store.setReader(&m_reader);

  unsigned int nevents = m_reader.getEntries();
  std::cout << "Loaded file " << input_file_name << " with " << nevents << " entries " << std::endl;
  
  return true;
}

bool FiberDigitizeAndCalibrate::CloseFile()
{
  m_reader.closeFile();
  return true;
}
