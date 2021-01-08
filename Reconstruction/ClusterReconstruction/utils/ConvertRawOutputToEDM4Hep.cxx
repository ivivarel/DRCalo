#include <ConvertToEdm4Hep.h>
#include <string>

int main(int argc, char **argv)
{
  std::cout << "*********************************\n";
  std::cout << "     " << argv[0] << "       \n"; 
  std::cout << "*********************************\n";
  std::cout << "\n\n" << std::endl;
  
  if (argc != 4) {
    std::cout << "USAGE: " << argv[0] << " [OUTPUTFILE] [INPUTSIMFILE] [INPUTTRUTHFILE]\n";
    std::cout << "where [OUTPUTFILE] is the name of teh output file\n";
    std::cout << " [INPUTSIMFILE] is the file containing the G4 ntuple\n";
    std::cout << " [INPUTTRUTHFILE] is the file containing the truth ntuple (give 0 if you do not want the truth)\n"; 
    return -1;
  }
  
  std::string s_ofile = argv[1];  
  std::string s_ifilesim = argv[2];
  std::string s_ifiletruth = argv[3];

  ConvertToEdm4Hep l_convert;

  l_convert.SetOutputFileName(s_ofile);
  l_convert.SetInputSimName(s_ifilesim);
  l_convert.SetInputTruthName(s_ifiletruth);
  l_convert.SetDebug();

  bool success = l_convert.Convert();

  int retval = -1;

  if (success) retval = 0;
 
  return retval;

}
