#include <iostream>
#include <TString.h>
#include <TFile.h> 
#include <TTree.h>

bool UpdateG4tree(TString G4file, TString Truthfile, TString Newfile="output.root", TString G4treename = "B4", TString Truthtreename = "truth", TString Newtreename = "B4merge" )
{
  
  std::cout << G4file << std::endl;
  std::cout << Truthfile << std::endl;
  
  TFile * truthfile = TFile::Open(Truthfile);
  TFile * recfile = TFile::Open(G4file);
  TFile * newfile = TFile::Open(Newfile,"recreate");

  TTree * T_truth = (TTree *) truthfile->Get(Truthtreename);
  TTree * T_reco = (TTree*)recfile->Get(G4treename);
  newfile->cd();
  TTree * T_new = new TTree(Newtreename,"Merged pythia/G4 truth");

  /*  TFile * f_output = new TFile("newfile.root","recreate");
      TTree * T_newtree = T->CloneTree();*/

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
  vector<double>  *VectorSignalsR;
  vector<double>  *VectorSignalsL;
  vector<double>  *VectorSignalsCherR;
  vector<double>  *VectorSignalsCherL;
  vector<double>  *VectorL;
  vector<double>  *VectorR;
  vector<double>  *VectorL_loop;
  vector<double>  *VectorR_loop;

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
  vector<float>   *mcs_E;
  vector<float>   *mcs_pt;
  vector<float>   *mcs_m;
  vector<float>   *mcs_eta;
  vector<float>   *mcs_phi;
  vector<int>     *mcs_status;
  vector<int>     *mcs_barcode;
  vector<int>     *mcs_pdgId;
  vector<float>   *mcs_charge;
  vector<float>   *mcs_vx_x;
  vector<float>   *mcs_vx_y;
  vector<float>   *mcs_vx_z;

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
