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
  int EvtID, Flagt, slicet, towert;
  float FiberID, Et, Xt, Yt, Zt;

  std::ifstream ifile(s_ifile.c_str());
  if (!ifile.is_open()) {
    std::cerr << "Cannot find file " << s_ifile << std::endl;
    return -1;
  }

  TFile o_file(s_ofile.c_str(),"recreate");
  o_file.cd();
  TTree * t_tree = new TTree("CollectionTree","Tree with detailed simulation output information");

  // Define variables for new tree

  std::vector<float> v_s_phi;
  std::vector<float> v_s_theta;
  std::vector<int> v_s_tower;
  std::vector<int> v_s_slice;
  std::vector<float> v_s_e;

  std::vector<float> v_c_phi;
  std::vector<float> v_c_theta;
  std::vector<int> v_c_tower;
  std::vector<int> v_c_slice;
  std::vector<float> v_c_e;

  t_tree->Branch("S_phi",&v_s_phi);
  t_tree->Branch("S_theta",&v_s_theta);
  t_tree->Branch("S_tower",&v_s_tower);
  t_tree->Branch("S_slice",&v_s_slice);
  t_tree->Branch("S_e",&v_s_e);
  t_tree->Branch("C_phi",&v_s_phi);
  t_tree->Branch("C_theta",&v_s_theta);
  t_tree->Branch("C_tower",&v_s_tower);
  t_tree->Branch("C_slice",&v_s_slice);
  t_tree->Branch("C_e",&v_s_e);

  // Start looping over lines

  int last_EvtID = -1;

  TVector3 temp_fiber;

  while (ifile >> s_EvtID >> s_FiberID >> s_Et >> s_Xt  >> s_Yt >> s_Zt >> s_Flagt >> s_slicet >> s_towert){

    std::cout << "s: " << s_towert << std::endl;

    if (s_EvtID == "EvtID") continue; // skip the first line that is just a heading
    EvtID = atoi(s_EvtID.c_str());



    if (EvtID != last_EvtID /* we are now looking at another event */){
      if (EvtID % 100 == 0) std::cout << EvtID << " events processed" << std::endl;
      // first thing: write the event to the tree 
      t_tree->Fill();
      last_EvtID=EvtID;

      // Prepare the vectors to store a new event
      
      v_s_phi.clear();
      v_s_theta.clear();
      v_s_tower.clear();
      v_s_slice.clear();
      v_s_e.clear();
      v_c_phi.clear();
      v_c_theta.clear();
      v_c_tower.clear();
      v_c_slice.clear();
      v_c_e.clear();

      v_s_phi.reserve(1000);
      v_s_theta.reserve(1000);
      v_s_tower.reserve(1000);
      v_s_slice.reserve(1000);
      v_s_e.reserve(1000);
      v_c_phi.reserve(1000);
      v_c_theta.reserve(1000);
      v_c_tower.reserve(1000);
      v_c_slice.reserve(1000);
      v_c_e.reserve(1000);
    }

    FiberID = atof(s_FiberID.c_str());
    
    Et = atof(s_Et.c_str());
    Xt = atof(s_Xt.c_str());
    Yt = atof(s_Yt.c_str());
    Zt = atof(s_Zt.c_str());
    
    Flagt = atoi(s_Flagt.c_str());
    slicet = atoi(s_slicet.c_str());
    towert = atoi(s_towert.c_str());

    std::cout << "I: " << towert << std::endl;
  
    // convert X,Y,Z in theta and phi --- no R information, although we may need it for fibers starting within teh calorimeter volume. 

    temp_fiber.SetX(Xt);
    temp_fiber.SetY(Yt);
    temp_fiber.SetZ(Zt);

    if (Flagt == 1){ // then it is scintillation
      v_s_phi.push_back(temp_fiber.Phi());
      v_s_theta.push_back(temp_fiber.Theta());
      v_s_tower.push_back(towert);
      v_s_slice.push_back(slicet);
      v_s_e.push_back(Et);
    } else if (Flagt == 0){
      v_c_phi.push_back(temp_fiber.Phi());
      v_c_theta.push_back(temp_fiber.Theta());
      v_c_tower.push_back(towert);
      v_c_slice.push_back(slicet);
      v_c_e.push_back(Et);
    } else {
      std::cerr << "Flagt = " << Flagt << " not recognised, please double check!!!!\n";
      std::cout << "Full line: " <<  s_EvtID << " " << s_FiberID << " " <<  s_Et << " " <<  s_Xt  << " " <<  s_Yt<< " " <<  s_Zt << " " <<  s_Flagt << " " <<  s_slicet << " " <<  s_towert << std::endl;
    }    
  }


  t_tree->Write();

  o_file.Close();

  return 0;
}
