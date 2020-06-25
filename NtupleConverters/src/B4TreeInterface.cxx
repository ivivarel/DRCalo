#include "B4TreeInterface.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

B4TreeInterface::B4TreeInterface(TTree *tree) : fChain(0) 
{
   Init(tree);
}

B4TreeInterface::~B4TreeInterface()
{
}

Int_t B4TreeInterface::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

void B4TreeInterface::Init(TTree *tree)
{
   // Set object pointer
   VectorSignalsR = 0;
   VectorSignalsL = 0;
   VectorSignalsCherR = 0;
   VectorSignalsCherL = 0;
   VectorL = 0;
   VectorR = 0;
   VectorL_loop = 0;
   VectorR_loop = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;

   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Energyem", &Energyem, &b_Energyem);
   fChain->SetBranchAddress("EnergyScin", &EnergyScin, &b_EnergyScin);
   fChain->SetBranchAddress("EnergyCher", &EnergyCher, &b_EnergyCher);
   fChain->SetBranchAddress("NofCherenkovDetected", &NofCherenkovDetected, &b_NofCherenkovDetected);
   fChain->SetBranchAddress("EnergyTot", &EnergyTot, &b_EnergyTot);
   fChain->SetBranchAddress("PrimaryParticleEnergy", &PrimaryParticleEnergy, &b_PrimaryParticleEnergy);
   fChain->SetBranchAddress("PrimaryParticleName", &PrimaryParticleName, &b_PrimaryParticleName);
   fChain->SetBranchAddress("neutrinoleakage", &neutrinoleakage, &b_neutrinoleakage);
   fChain->SetBranchAddress("leakage", &leakage, &b_leakage);
   fChain->SetBranchAddress("VectorSignalsR", &VectorSignalsR, &b_VectorSignalsR);
   fChain->SetBranchAddress("VectorSignalsL", &VectorSignalsL, &b_VectorSignalsL);
   fChain->SetBranchAddress("VectorSignalsCherR", &VectorSignalsCherR, &b_VectorSignalsCherR);
   fChain->SetBranchAddress("VectorSignalsCherL", &VectorSignalsCherL, &b_VectorSignalsCherL);
   fChain->SetBranchAddress("VectorL", &VectorL, &b_VectorL);
   fChain->SetBranchAddress("VectorR", &VectorR, &b_VectorR);
   fChain->SetBranchAddress("VectorL_loop", &VectorL_loop, &b_VectorL_loop);
   fChain->SetBranchAddress("VectorR_loop", &VectorR_loop, &b_VectorR_loop);
}

