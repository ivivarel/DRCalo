#ifndef DRCALO_CONVERTTOEDMHEP
#define DRCALO_CONVERTTOEDMHEP

// std library include

#include <iostream>
#include <vector>
#include <string>

class ConvertToEdm4Hep
{
public:
  ConvertToEdm4Hep();
  ~ConvertToEdm4Hep();

  void SetOutputFileName(std::string filename) {m_outFileName = filename;}
  void SetInputSimName(std::string filename) {m_inputSimName = filename;}
  void SetInputTruthName(std::string filename) {m_inputTruthName = filename;}
  void SetDebug(bool debug=true) {m_debug = debug;}
  bool Convert();
  
private:
  std::string m_outFileName;
  std::string m_inputSimName;
  std::string  m_inputTruthName;
  bool m_debug;
};

#endif
