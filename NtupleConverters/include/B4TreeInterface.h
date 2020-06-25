#ifndef DRCalo_B4TreeInterface_h
#define DRCalo_B4TreeInterface_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class B4TreeInterface {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Energyem;
   Double_t        EnergyScin;
   Double_t        EnergyCher;
   Double_t        NofCherenkovDetected;
   Double_t        EnergyTot;
   Double_t        PrimaryParticleEnergy;
   Char_t          PrimaryParticleName;
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

   // List of branches
   TBranch        *b_Energyem;   //!
   TBranch        *b_EnergyScin;   //!
   TBranch        *b_EnergyCher;   //!
   TBranch        *b_NofCherenkovDetected;   //!
   TBranch        *b_EnergyTot;   //!
   TBranch        *b_PrimaryParticleEnergy;   //!
   TBranch        *b_PrimaryParticleName;   //!
   TBranch        *b_neutrinoleakage;   //!
   TBranch        *b_leakage;   //!
   TBranch        *b_VectorSignalsR;   //!
   TBranch        *b_VectorSignalsL;   //!
   TBranch        *b_VectorSignalsCherR;   //!
   TBranch        *b_VectorSignalsCherL;   //!
   TBranch        *b_VectorL;   //!
   TBranch        *b_VectorR;   //!
   TBranch        *b_VectorL_loop;   //!
   TBranch        *b_VectorR_loop;   //!

   B4TreeInterface(TTree *tree=0);
   ~B4TreeInterface();
   Int_t    GetEntry(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void     Init(TTree *tree);

};

#endif
