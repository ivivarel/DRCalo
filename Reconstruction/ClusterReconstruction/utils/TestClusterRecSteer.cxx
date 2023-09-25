#include "ClusterRecSteer.h"

#include <iostream>

int main(int argc, char **argv)
{

  std::cout << "*********************************\n";
  std::cout << "     " << argv[0] << "       \n"; 
  std::cout << "*********************************\n";
  std::cout << "\n\n" << std::endl;

  if (argc != 3) {
    std::cout << "USAGE: " << argv[0] << " [INPUTFILE] [OUTPUTFILE]\n";
    std::cout << "where [INPUTFILE] is the podio file containing simulation hits\n";
    std::cout << "and [OUTPUTFILE] is the output podio file containing the clusters\n";
    return -1;
  }

  ClusterRecSteer l_steer;
  l_steer.SetDebug(true);
  l_steer.SetOutputFileName(argv[2]);
  std::cout << "Loading input file " << std::endl;
  if (!l_steer.LoadFile(argv[1])) return -1;
  std::cout << "Starting process" << std::endl;
  l_steer.Process();
  std::cout << "Closing file and exiting" << std::endl;
  l_steer.CloseFile();
  return 0;
}
