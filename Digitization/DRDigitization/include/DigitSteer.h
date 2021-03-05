#ifndef DR_DIGITSTEER
#define DR_DIGITSTEER

//std includes

#include <string>

// podio includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

#include "FiberDigitizer.h"

class sipm::SiPMSensor;

class DigitSteer
{
 public:
  DigitSteer();
  ~DigitSteer();
  bool Process();
  bool LoadFile(std::string input_file_name);
  bool CloseFile();
  void SetScintInputHitsName(std::string input_hits_name) {m_inputScintHitsName=input_hits_name;}
  void SetCherInputHitsName(std::string input_hits_name) {m_inputCherHitsName=input_hits_name;}
  void SetAuxInputHitsName(std::string input_hits_name) {m_inputScintHitsName=input_hits_name;}
  void SetScintOutputHitsName(std::string hits_name) {m_outputScintHitsName=hits_name;}
  void SetCherOutputHitsName(std::string hits_name) {m_outputCherHitsName=hits_name;}
  void SetAuxOutputHitsName(std::string hits_name) {m_outputCherHitsName=hits_name;}
  void SetOutputFileName(std::string filename) {m_outputFileName = filename;}
  void SetDebug(bool debug = true) {m_debug = debug;}
  void DoCalibration(bool doCal = true) {m_doCalibration = doCal;}
  void SetSiPMSensor(sipm::SiPMSensor * l_sensor = NULL);
  
  
 private:
  std::string m_inputCherHitsName;
  std::string m_inputScintHitsName;
  std::string m_inputAuxHitsName;
  std::string m_outputCherHitsName;
  std::string m_outputScintHitsName;
  std::string m_outputAuxHitsName;
  std::string m_outputFileName;
  bool m_debug;
  bool m_doCalibration;
  podio::ROOTReader m_reader;
  podio::EventStore m_read_store;
  FiberDigitizer m_digitizer;
  sipm::SiPMSensor m_sensor;
};

#endif
