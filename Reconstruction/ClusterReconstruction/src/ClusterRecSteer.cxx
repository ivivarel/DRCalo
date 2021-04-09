#include "ClusterRecSteer.h"

#include "DRCalo_FiberType.h"

#include "edm4hep/CalorimeterHitCollection.h"
#include "edm4hep/ClusterCollection.h"

#include "podio/ROOTWriter.h"

#include <iostream>

bool ClusterRecSteer::Process()
{
  
  //  podio::EventStore l_store;                                                                                 
  //  podio::ROOTWriter l_writer("output.root",&l_store);
  
  unsigned int nevents = m_reader.getEntries();
  
  //    edm4hep::CalorimeterHitCollection s_recoCaloHits;

  m_grid.CreateGrid();
  
  // main loop over events
  
  //  for (unsigned int i_evt = 0; i_evt < nevents; ++i_evt){
  for (unsigned int i_evt = 0; i_evt < 2; ++i_evt){

    // reset the grid
    m_grid.Reset();
    
    // retrieve the simulation hits
    
    auto & s_hitColl = m_read_store.get<edm4hep::CalorimeterHitCollection>(m_inputScintHitsName);
    
    auto & c_hitColl = m_read_store.get<edm4hep::CalorimeterHitCollection>(m_inputCherHitsName);
    
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

    // prepare the grid

    for (auto & hit : s_hitColl){
      m_grid.Add(hit);
    }

    TString filename = "evt_display_";
    filename += i_evt;
    filename += ".pdf";
    m_grid.EventDisplay(filename);
    
    
    // Final cleanup

   
   
    m_read_store.clear();
    m_reader.endOfEvent();
    //l_store.clearCollections();
  }
  //l_writer.finish();
  return true;
}

ClusterRecSteer::ClusterRecSteer():
  m_inputCherHitsName("C_CalorimeterHits"),
  m_inputScintHitsName("S_CalorimeterHits"),
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
