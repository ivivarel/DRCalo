#ifndef DR_FIBERDIGITIZEANDCALIBRATE
#define DR_FIBERDIGITIZEANDCALIBRATE

//std includes

#include <string>

// podio includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"
#include "podio/ROOTWriter.h"


class FiberDigitizeAndCalibrate
{
 public:
  FiberDigitizeAndCalibrate();
  ~FiberDigitizeAndCalibrate();
  bool Process();
  bool LoadFile(std::string input_file_name);
  bool CloseFile();
  void SetScintInputHitsName(std::string input_hits_name="S_SimCalorimeterHits") {m_inputScintHitsName=input_hits_name;}
  void SetScintOutputHitsName(std::string output_hits_name="S_CalorimeterHits") {m_outputScintHitsName=output_hits_name;}
  void SetCherInputHitsName(std::string input_hits_name="C_SimCalorimeterHits") {m_inputCherHitsName=input_hits_name;}
  void SetCherOutputHitsName(std::string output_hits_name="C_CalorimeterHits") {m_outputCherHitsName=output_hits_name;}
  void SetDebug(bool debug = true) {m_debug = debug;}
  
 private:
  std::string m_inputCherHitsName;
  std::string m_inputScintHitsName;
  std::string m_outputCherHitsName;
  std::string m_outputScintHitsName;
  bool m_debug;
  podio::ROOTReader m_reader;
  podio::EventStore m_read_store;
  //  FiberDigitizer m_digitizer;
  //  ClusterFiberCalibrate m_calibrator;
};

#endif
