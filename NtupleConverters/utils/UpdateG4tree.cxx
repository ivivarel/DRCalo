
// std library includes
#include <iostream>
#include <vector>
//ROOT includes 
#include <TString.h>
#include <TFile.h> 
#include <TTree.h>

void help();

bool UpdateG4tree(TString G4file, TString Truthfile, TString Newfile, TString G4treename, TString Truthtreename, TString Newtreename);

int main(int argc, char **argv)
{
  std::cout << "***********************************\n";
  std::cout << "    " << argv[0] << "    \n";
  std::cout << "***********************************\n";
  
  if (argc < 3 || argc > 7) {
    help();
    return -1;
  }

  TString G4file = argv[1];
  TString Truthfile = argv[2];
  TString Newfile; 
  if (argc >= 4) Newfile = argv[3];
  else Newfile = "output.root";
  TString G4treename;
  if (argc >= 5) G4treename = argv[4];
  else G4treename = "B4";
  TString Truthtreename;
  if (argc >= 6) Truthtreename = argv[5];
  else Truthtreename = "truth";
  TString Newtreename;
  if (argc == 7) Newtreename = argv[6];
  else Newtreename = "B4merge";

  bool retval = UpdateG4tree(G4file, Truthfile, Newfile, G4treename, Truthtreename, Newtreename);

  return retval;

}


void help(){
  std::cout << "USAGE: UpdateG4tree [G4file - c] [Truthfile - c] [Newfile - o] [G4treename - o] [Truthtreename - o] [Newtreename - o]\n";
  std::cout << "All arguments flagged with 'o' are optional\n";
  std::cout << "\n\n This piece of code merges the G4 and truth root trees that come as default output in the Pavia G4 simulation\n\n";
  std::cout << "Arguments are as follows: \n";
  std::cout << "G4file - G4 Pavia ntuple file name\n";
  std::cout << "Truthfile - root file containing truth ntuple\n";
  std::cout << "Newfile - file name of the merged tree. Default: output.root\n";
  std::cout << "G4treename - tree name for the G4 tree. Default: B4\n";
  std::cout << "Truthtreename - tree name for the truth tree. Default: truth\n";
  std::cout << "Newtreename - tree name for the merged tree. Default: B4merge\n";
}

bool UpdateG4tree(TString G4file, TString Truthfile, TString Newfile="output.root", TString G4treename = "B4", TString Truthtreename = "truth", TString Newtreename = "B4merge" )
{

  std::cout << "Running with the following paarameters:\n";
  
  std::cout << "G4file: " << G4file << std::endl;
  std::cout << "Truthfile: " << Truthfile << std::endl;
  std::cout << "Newfile: " << Newfile << std::endl;
  std::cout << "G4treename: " << G4treename << std::endl;
  std::cout << "Truthtreename: " << Truthtreename << std::endl;
  std::cout << "Newtreename: " << Newtreename << std::endl;
  
  TFile * truthfile = TFile::Open(Truthfile);
  if (!truthfile->IsOpen()) {
    std::cout << "Cannot find file " << Truthfile << std::endl;
    return false;
  }
  TFile * recfile = TFile::Open(G4file);
  if (!recfile->IsOpen()){
    std::cout << "Cannot find file " << G4file << std::endl;
    return false;
  }
  TFile * newfile = TFile::Open(Newfile,"recreate");
  if (!newfile->IsOpen()){
    std::cout << "Cannot open file " << Newfile << std::endl;
    return false;
  }

  TTree * T_truth = (TTree *) truthfile->Get(Truthtreename);
  if (!T_truth) {
    std::cout << "Cannot find TTree with name " << Truthtreename << " in file " << truthfile->GetName() << std::endl;
    return false;
  }
  TTree * T_reco = (TTree*)recfile->Get(G4treename);
  if (!T_reco) {
    std::cout << "Cannot find TTree with name " << G4treename << " in file " << recfile->GetName() << std::endl;
    return false;
  }
  newfile->cd();
  TTree * T_new = new TTree(Newtreename,"Merged pythia/G4 truth");

  // Reco variables 
  
  Double_t        Energyem;
  Double_t        EnergyScin;
  Double_t        EnergyCher;
  Double_t        NofCherenkovDetected;
  Double_t        EnergyTot;
  Double_t        PrimaryParticleEnergy;
  Char_t          PrimaryParticleName[6];
  Double_t        neutrinoleakage;
  Double_t        leakage;
  std::vector<double>  *VectorSignalsR;
  std::vector<double>  *VectorSignalsL;
  std::vector<double>  *VectorSignalsCherR;
  std::vector<double>  *VectorSignalsCherL;
  std::vector<double>  *VectorL;
  std::vector<double>  *VectorR;
  std::vector<double>  *VectorL_loop;
  std::vector<double>  *VectorR_loop;

  VectorSignalsR = 0;
  VectorSignalsL = 0;
  VectorSignalsCherR = 0;
  VectorSignalsCherL = 0;
  VectorL = 0;
  VectorR = 0;
  VectorL_loop = 0;
  VectorR_loop = 0;

  T_reco->SetBranchAddress("Energyem", &Energyem);
  T_reco->SetBranchAddress("EnergyScin", &EnergyScin);
  T_reco->SetBranchAddress("EnergyCher", &EnergyCher);
  T_reco->SetBranchAddress("NofCherenkovDetected", &NofCherenkovDetected);
  T_reco->SetBranchAddress("EnergyTot", &EnergyTot);
  T_reco->SetBranchAddress("PrimaryParticleEnergy", &PrimaryParticleEnergy);
  T_reco->SetBranchAddress("PrimaryParticleName", PrimaryParticleName);
  T_reco->SetBranchAddress("neutrinoleakage", &neutrinoleakage);
  T_reco->SetBranchAddress("leakage", &leakage);
  T_reco->SetBranchAddress("VectorSignalsR", &VectorSignalsR);
  T_reco->SetBranchAddress("VectorSignalsL", &VectorSignalsL);
  T_reco->SetBranchAddress("VectorSignalsCherR", &VectorSignalsCherR);
  T_reco->SetBranchAddress("VectorSignalsCherL", &VectorSignalsCherL);
  T_reco->SetBranchAddress("VectorL", &VectorL);
  T_reco->SetBranchAddress("VectorR", &VectorR);
  T_reco->SetBranchAddress("VectorL_loop", &VectorL_loop);
  T_reco->SetBranchAddress("VectorR_loop", &VectorR_loop);
  
  T_new->Branch("Energyem", &Energyem,"Energyem/D");
  T_new->Branch("EnergyScin", &EnergyScin,"EnergyScin/D");
  T_new->Branch("EnergyCher", &EnergyCher,"EnergyCher/D");
  T_new->Branch("NofCherenkovDetected", &NofCherenkovDetected,"NofCherenkovDetected/D");
  T_new->Branch("EnergyTot", &EnergyTot,"EnergyTot/D");
  T_new->Branch("PrimaryParticleEnergy", &PrimaryParticleEnergy,"PrimaryParticleEnergy/D");
  T_new->Branch("PrimaryParticleName", &PrimaryParticleName,"PrimaryParticleName[6]/B");
  T_new->Branch("neutrinoleakage", &neutrinoleakage,"neutrinoleakage/D");
  T_new->Branch("leakage", &leakage,"leakage/D");
  T_new->Branch("VectorSignalsR", &VectorSignalsR);
  T_new->Branch("VectorSignalsL", &VectorSignalsL);
  T_new->Branch("VectorSignalsCherR", &VectorSignalsCherR);
  T_new->Branch("VectorSignalsCherL", &VectorSignalsCherL);
  T_new->Branch("VectorL", &VectorL);
  T_new->Branch("VectorR", &VectorR);
  T_new->Branch("VectorL_loop", &VectorL_loop);
  T_new->Branch("VectorR_loop", &VectorR_loop);

  // now starting with the truth variables

  UInt_t          mcs_n;
  std::vector<float>   *mcs_E;
  std::vector<float>   *mcs_pt;
  std::vector<float>   *mcs_m;
  std::vector<float>   *mcs_eta;
  std::vector<float>   *mcs_phi;
  std::vector<int>     *mcs_status;
  std::vector<int>     *mcs_barcode;
  std::vector<int>     *mcs_pdgId;
  std::vector<float>   *mcs_charge;
  std::vector<float>   *mcs_vx_x;
  std::vector<float>   *mcs_vx_y;
  std::vector<float>   *mcs_vx_z;

  mcs_E = 0;          
  mcs_pt = 0;                                           
  mcs_m = 0;                                                
  mcs_eta = 0;                                         
  mcs_phi = 0;                                        
  mcs_status = 0;              
  mcs_barcode = 0;                            
  mcs_pdgId = 0;                     
  mcs_charge = 0;                                   
  mcs_vx_x = 0;                                       
  mcs_vx_y = 0;                                    
  mcs_vx_z = 0;                                                     
  
  // branches in the truth branch

  T_truth->SetBranchAddress("mcs_n", &mcs_n);
  T_truth->SetBranchAddress("mcs_E", &mcs_E);
  T_truth->SetBranchAddress("mcs_pt", &mcs_pt);
  T_truth->SetBranchAddress("mcs_m", &mcs_m);
  T_truth->SetBranchAddress("mcs_eta", &mcs_eta);
  T_truth->SetBranchAddress("mcs_phi", &mcs_phi);
  T_truth->SetBranchAddress("mcs_status", &mcs_status);
  T_truth->SetBranchAddress("mcs_barcode", &mcs_barcode);
  T_truth->SetBranchAddress("mcs_pdgId", &mcs_pdgId);
  T_truth->SetBranchAddress("mcs_charge", &mcs_charge);
  T_truth->SetBranchAddress("mcs_vx_x", &mcs_vx_x);
  T_truth->SetBranchAddress("mcs_vx_y", &mcs_vx_y);      
  T_truth->SetBranchAddress("mcs_vx_z", &mcs_vx_z);

  T_new->Branch("mcs_n", &mcs_n,"mcs_n/I");          
  T_new->Branch("mcs_E", &mcs_E);
  T_new->Branch("mcs_pt", &mcs_pt);
  T_new->Branch("mcs_m", &mcs_m);
  T_new->Branch("mcs_eta", &mcs_eta);
  T_new->Branch("mcs_phi", &mcs_phi);
  T_new->Branch("mcs_status", &mcs_status);
  T_new->Branch("mcs_barcode", &mcs_barcode);
  T_new->Branch("mcs_pdgId", &mcs_pdgId);
  T_new->Branch("mcs_charge", &mcs_charge);
  T_new->Branch("mcs_vx_x", &mcs_vx_x);
  T_new->Branch("mcs_vx_y", &mcs_vx_y);
  T_new->Branch("mcs_vx_z", &mcs_vx_z);
  
  Long64_t nentries = T_reco->GetEntries(); 
  for (Long64_t i=0;i<nentries;i++) { 
    T_reco->GetEntry(i);
    T_truth->GetEntry(i);
    T_new->Fill();
  }
  T_new->Write("",TObject::kOverwrite);

  newfile->Close();
  truthfile->Close();
  recfile->Close();

  return true;
}
