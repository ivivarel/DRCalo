#ifndef DRCALO_CONVERTTOEDMHEP
#define DRCALO_CONVERTTOEDMHEP

// std library includes

#include <iostream>
#include <vector>
#include <string>

// root includes

#include <TFile.h>
#include <TTree.h>

class ConvertToEdm4Hep
{
public:
  ConvertToEdm4Hep();
  ~ConvertToEdm4Hep();

  void SetOutputFileName(std::string filename) {m_outFileName = filename;}
  void SetInputSimName(std::string filename) {m_inputSimName = filename;}
  void SetInputTruthName(std::string filename) {m_inputTruthName = filename;}
  void SetInputSimTreeName(std::string treename) {m_inputSimTreeName = treename;}
  void SetInputTruthTreeName(std::string treename) {m_inputTruthTreeName = treename;}
  void SetDebug(bool debug=true) {m_debug = debug;}
  void DoTruth(bool dotruth=true){m_doTruth=dotruth;}
  bool OpenInputFiles();
  bool Convert();
  
private:
  std::string m_outFileName;
  std::string m_inputSimName;
  std::string  m_inputTruthName;
  std::string m_inputSimTreeName;
  std::string m_inputTruthTreeName;
  TFile * m_inputSimFile;
  TFile * m_inputTruthFile;
  TTree * m_inputSimTree;
  TTree * m_inputTruthTree;
  bool m_doTruth;
  bool m_debug;
};

#endif
