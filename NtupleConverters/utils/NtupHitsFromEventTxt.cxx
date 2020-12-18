#include <iostream>
#include <TString.h>
#include <string>
#include <fstream>


int main(int argc, char **argv)
{

  TString tree_name = "DRCalo_HitsFromFiber";
  
  std::cout << "*********************************\n";
  std::cout << "     " << argv[0] << "       \n"; 
  std::cout << "*********************************\n";
  std::cout << "\n\n" << std::endl;

  if (argc != 4) {
    std::cout << "USAGE: " << argv[0] << " [INPUTFILE] [OUTPUTFILE] [DOCAL]\n";
    std::cout << "where [INPUTFILE] is the Event.txt file coming out of the G4 simulation containing the number of photons fiber per fiber\n"; 
    std::cout << "[OUTPUTFILE] is the name of the output root file\n";
    std::cout << "[DOCAL] is 0 if the calibration should not be applied, any other integer otherwise" << std::endl;
    return -1;
  }

  std::string s_ifile = argv[1];
  std::string s_ofile = argv[2];
  int i_docal = atoi(argv[3]);

  // check that the input file is there 

  std::ifstream ifile(s_ifile.c_str());
  if (!ifile.good()) {
    std::cerr << "Cannot find file " << s_ifile << std::endl;
    return -1;
  }
  
  

  return 0;
}
