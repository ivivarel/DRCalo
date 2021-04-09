#ifndef DR_CLUSTERRECSTEER
#define DR_CLUSTERRECSTEER

//std includes

#include <string>

// podio includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

#include "DR_CaloGridHelper.h"

/*** 

The idea of this piece of code is to be the driver of the reconstruction of clusters starting from CalorimeterHit collections. The input to it is pointers to hit collections. The output is a list of clusters. An option should be available to make the intermediate grid also available in some form

***/


class ClusterRecSteer
{
 public:
  ClusterRecSteer();
  ~ClusterRecSteer();
  bool Process();
  bool LoadFile(std::string input_file_name);
  bool CloseFile();
  void SetScintInputHitsName(std::string input_hits_name="S_CalorimeterHits") {m_inputScintHitsName=input_hits_name;}
  void SetCherInputHitsName(std::string input_hits_name="C_CalorimeterHits") {m_inputCherHitsName=input_hits_name;}
  void SetDebug(bool debug = true) {m_debug = debug;}
  void SetGridSpacing(double spacing) {m_grid.SetDistanceParameter(spacing);}
  
 private:
  std::string m_inputCherHitsName;
  std::string m_inputScintHitsName;
  bool m_debug;
  podio::ROOTReader m_reader;
  podio::EventStore m_read_store;
  DR_CaloGridHelper m_grid;
};

#endif
