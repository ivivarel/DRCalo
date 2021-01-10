#ifndef DR_CLUSTERRECSTEER
#define DR_CLUSTERRECSTEER

//std includes

#include <string>

// podio includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

#include "DR_GeometryHelper.h"

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
  
 private:
  DR_GeometryHelper m_geomHelper;
  std::string m_inputCherHitsName;
  std::string m_inputScintHitsName;
  podio::ROOTReader m_reader;
  podio::EventStore m_store;
};

#endif
