#include "ClusterRecSteer.h"

#include "edm4hep/SimCalorimeterHitCollection.h"

#include <iostream>

bool ClusterRecSteer::Process()
{

  unsigned int nevents = m_reader.getEntries();

  // main loop over events

  for (unsigned int i_evt = 0; i_evt < nevents; ++i_evt){

    auto & s_hitColl = m_store.get<edm4hep::SimCalorimeterHitCollection>(m_inputScintHitsName);

    auto & c_hitColl = m_store.get<edm4hep::SimCalorimeterHitCollection>(m_inputCherHitsName);

    if (!s_hitColl.isValid()){
      std::cerr << "Cannot read S simulation hits with name " << m_inputScintHitsName << std::endl;
      return false;
    }

    if (!c_hitColl.isValid()){
      std::cerr << "Cannot read C simulation hits with name " << m_inputCherHitsName << std::endl;
      return false;
    }

    for (auto s_hit : s_hitColl){
      std::cout << s_hit.getEnergy() << std::endl;
    }
    
    m_store.clear();
    m_reader.endOfEvent();
  }
  
  return true;
}

ClusterRecSteer::ClusterRecSteer():
  m_inputCherHitsName("C_SimCalorimeterHits"),
  m_inputScintHitsName("S_SimCalorimeterHits")
{
}

ClusterRecSteer::~ClusterRecSteer()
{}

bool ClusterRecSteer::LoadFile(std::string input_file_name)
{
  m_reader.openFile(input_file_name);

  m_store.setReader(&m_reader);

  unsigned int nevents = m_reader.getEntries();
  std::cout << "Loaded file " << input_file_name << " with " << nevents << " entries " << std::endl;
  
  return true;
}

bool ClusterRecSteer::CloseFile()
{
  m_reader.closeFile();
}
