#ifndef DR_CLUSTERRECSTEER
#define DR_CLUSTERRECSTEER

//std includes

#include <string>

// podio includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

#include "ClusterFiberCalibrate.h"

class ClusterRecSteer
{
 public:
  ClusterRecSteer();
  ~ClusterRecSteer();
  bool Process();
  bool LoadFile(std::string input_file_name);
  bool CloseFile();
  void SetScintInputHitsName(std::string input_hits_name="S_SimCalorimeterHits") {m_inputScintHitsName=input_hits_name;}
  void SetCherInputHitsName(std::string input_hits_name="C_SimCalorimeterHits") {m_inputCherHitsName=input_hits_name;}
  void SetDebug(bool debug = true) {m_debug = debug;}
  
 private:
  std::string m_inputCherHitsName;
  std::string m_inputScintHitsName;
  bool m_debug;
  podio::ROOTReader m_reader;
  podio::EventStore m_read_store;
  podio::EventStore m_store;
  ClusterFiberCalibrate m_calibrator;
  
};

#endif
