#include "ClusterRecSteer.h"

#include <iostream>

int main(int argc, char **argv)
{

  std::cout << "*********************************\n";
  std::cout << "     " << argv[0] << "       \n"; 
  std::cout << "*********************************\n";
  std::cout << "\n\n" << std::endl;

  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << " [INPUTFILE] \n";
    std::cout << "where [INPUTFILE] is the podio file containing simulation hits\n";
    return -1;
  }

  ClusterRecSteer l_steer;
  std::cout << "Loading input file " << std::endl;
  if (!l_steer.LoadFile(argv[1])) return -1;
  std::cout << "Starting process" << std::endl;
  l_steer.Process();
  std::cout << "Closing file and exiting" << std::endl;
  l_steer.CloseFile();
  return 0;
}
