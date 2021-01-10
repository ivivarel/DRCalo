// std includes 

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// root includes

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>

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

  std::string line; 
  std::string s_EvtID, s_FiberID, s_Et, s_Xt, s_Yt, s_Zt, s_Flagt, s_slicet, s_towert;
  int EvtID, Flagt, slicet, towert,ID;
  float FiberID, Et, Xt, Yt, Zt;

  std::ifstream ifile(s_ifile.c_str());
  if (!ifile.is_open()) {
    std::cerr << "Cannot find file " << s_ifile << std::endl;
    return -1;
  }


  TTree * t_tree = new TTree("CollectionTree","Tree with detailed simulation output information");

  // Define variables for new tree

  std::vector<float> v_s_x;
  std::vector<float> v_s_y;
  std::vector<float> v_s_z;
  std::vector<float> v_s_e;
  std::vector<int> v_s_ID;


  std::vector<float> v_c_x;
  std::vector<float> v_c_y;
  std::vector<float> v_c_z;
  std::vector<float> v_c_e;
  std::vector<int> v_c_ID;

  t_tree->Branch("S_x",&v_s_x);
  t_tree->Branch("S_y",&v_s_y);
  t_tree->Branch("S_z",&v_s_z);
  t_tree->Branch("S_e",&v_s_e);
  t_tree->Branch("S_ID",&v_s_ID);
  t_tree->Branch("C_x",&v_c_x);
  t_tree->Branch("C_y",&v_c_y);
  t_tree->Branch("C_z",&v_c_z);
  t_tree->Branch("C_e",&v_c_e);
  t_tree->Branch("C_ID",&v_c_ID);

  // Start looping over lines

  int last_EvtID = -1;

  TVector3 temp_fiber;

  unsigned int nevents = 0; 

  while (ifile >> s_EvtID >> s_FiberID >> s_Et >> s_Xt  >> s_Yt >> s_Zt >> s_Flagt >> s_slicet >> s_towert){

    if (s_EvtID == "EvtID") continue; // skip the first line that is just a heading
    EvtID = atoi(s_EvtID.c_str());

    if (EvtID != last_EvtID /* we are now looking at another event */){
      std::cout << "EvtID = " << EvtID << " nevents = " << nevents << std::endl;
      if (EvtID % 100 == 0) std::cout << EvtID << " events processed" << std::endl;
      // first thing: write the event to the tree 
      t_tree->Fill();
      last_EvtID=EvtID;

      // Prepare the vectors to store a new event
      
      v_s_x.clear();
      v_s_y.clear();
      v_s_z.clear();
      v_s_e.clear();
      v_s_ID.clear();

      v_c_x.clear();
      v_c_y.clear();
      v_c_z.clear();
      v_c_e.clear();
      v_c_ID.clear();

      v_s_x.reserve(1000);
      v_s_y.reserve(1000);
      v_s_z.reserve(1000);
      v_s_e.reserve(1000);
      v_s_ID.reserve(1000);
      v_c_x.reserve(1000);
      v_c_y.reserve(1000);
      v_c_z.reserve(1000);
      v_c_e.reserve(1000);
      v_c_ID.reserve(1000);


      ++nevents;
    }

    FiberID = atof(s_FiberID.c_str());
    ID = int(FiberID);
    Et = atof(s_Et.c_str());
    Xt = atof(s_Xt.c_str());
    Yt = atof(s_Yt.c_str());
    Zt = atof(s_Zt.c_str());
    
    Flagt = atoi(s_Flagt.c_str());
    slicet = atoi(s_slicet.c_str());
    towert = atoi(s_towert.c_str());

    // convert X,Y,Z in theta and phi --- no R information, although we may need it for fibers starting within teh calorimeter volume. 

    if (Flagt == 1){ // then it is scintillation
      v_s_x.push_back(Xt);
      v_s_y.push_back(Yt);
      v_s_z.push_back(Zt);
      v_s_e.push_back(Et);
      v_s_ID.push_back(ID);
    } else if (Flagt == 0){
      v_c_x.push_back(Xt);
      v_c_y.push_back(Yt);
      v_c_z.push_back(Zt);
      v_c_e.push_back(Et);
      v_c_ID.push_back(ID);
    } else {
      std::cerr << "Flagt = " << Flagt << " not recognised, please double check!!!!\n";
      std::cout << "Full line: " <<  s_EvtID << " " << s_FiberID << " " <<  s_Et << " " <<  s_Xt  << " " <<  s_Yt<< " " <<  s_Zt << " " <<  s_Flagt << " " <<  s_slicet << " " <<  s_towert << std::endl;
    }    
  }

  TFile o_file(s_ofile.c_str(),"recreate");
  o_file.cd();

  t_tree->Write();

  o_file.Close();

  return 0;
}
