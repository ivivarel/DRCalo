#include "DigitSteer.h"
#include "FiberDigitizer.h"
#include "SiPMSensor.h"
#include "SiPMProperties.h"

int main(int argc, char **argv)
{
  std::cout << "*********************************\n";
  std::cout << "     " << argv[0] << "       \n"; 
  std::cout << "*********************************\n";
  std::cout << "\n\n" << std::endl;
  
  if (argc != 3) {
    std::cout << "USAGE: " << argv[0] << " [INPUTFILE] [OUTPUTFILE]\n";
    std::cout << "where [INPUTFILE] is the podio file containing simulation hits\n";
    return -1;
  }

  DigitSteer l_steer;
  l_steer.SetDebug(false);
  
  std::cout << "Loading input file " << std::endl;
  if (!l_steer.LoadFile(argv[1])) return -1;

  std::cout << "Setting output  file name to " << argv[2] << std::endl;
  l_steer.SetOutputFileName(argv[2]);

  // Now configuring the SiPM sensor
  sipm::SiPMProperties l_properties;
  sipm::SiPMSensor l_sensor (l_properties);

  FiberDigitizer l_digitizer;
  l_digitizer.SetSiPMSensor(&l_sensor);
  
  std::cout << "Starting process" << std::endl;
  l_steer.SetFiberDigitizer(&l_digitizer);
  l_steer.Process();
  std::cout << "Closing file and exiting" << std::endl;
  l_steer.CloseFile();
  return 0;

}

