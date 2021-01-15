#include "ConvertToEdm4Hep.h"

// edm4hep includes

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/SimCalorimeterHitCollection.h"

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

// root includes 

#include <TTree.h>
#include <TBranch.h>
#include <TLorentzVector.h>

ConvertToEdm4Hep::ConvertToEdm4Hep() :
  m_outFileName("output.podio.root"),
  m_inputSimName(""),
  m_inputTruthName(""),
  m_inputSimTreeName("CollectionTree"),
  m_inputTruthTreeName("truth"),
  m_inputSimFile(0),
  m_inputTruthFile(0),
  m_inputSimTree(0),
  m_inputTruthTree(0),
  m_doTruth(true),
  m_debug(false)
{}

ConvertToEdm4Hep::~ConvertToEdm4Hep()
{}

bool ConvertToEdm4Hep::Convert()
{
  if (m_debug) std::cout << "In ConvertToEdm4Hep::Convert" << std::endl;

  // Step number one: check that the inputs are consistent trees have the same number of entries

  if (!m_inputSimTree){
    std::cerr << "Sim tree pointer is null. Was the corresponding file opened?" << std::endl;
    return false;
  }

  if (m_doTruth && !m_inputTruthTree){
    std::cerr << "Truth tree pointer is null. Was the corresponding file opened?" << std::endl;
    return false;
  }

  Long64_t nevents = m_inputSimTree->GetEntries();

  if (m_doTruth && nevents != m_inputTruthTree->GetEntries()){
    std::cerr << "Error in COnvertToEdm4Hep::Convert(): truth tree in file " << m_inputTruthFile->GetName() << " and sim tree in file " << m_inputSimFile->GetName() << " have different number of entries" << std::endl;
    return false;
  }

  // Step 2: prepare the input reading

  // Preparing sim tree 

   // Declaration of leaf types
  std::vector<float>   *S_x;
  std::vector<float>   *S_y;
  std::vector<float>   *S_z;
  std::vector<float>   *S_e;
  std::vector<int>     *S_ID;
  std::vector<float>   *C_x;
  std::vector<float>   *C_y;
  std::vector<float>   *C_z;
  std::vector<float>   *C_e;
  std::vector<int>     *C_ID;

  S_x = 0;
  S_y = 0;
  S_z = 0;
  S_e = 0;
  S_ID = 0;
  C_x = 0;
  C_y = 0;
  C_z = 0;
  C_e = 0;
  C_ID = 0;

  // List of branches
  TBranch        *b_S_x;   
  TBranch        *b_S_y;   
  TBranch        *b_S_z;   
  TBranch        *b_S_e;   
  TBranch        *b_S_ID;  
  TBranch        *b_C_x;   
  TBranch        *b_C_y;   
  TBranch        *b_C_z;   
  TBranch        *b_C_e;   
  TBranch        *b_C_ID;   

  m_inputSimTree->SetBranchAddress("S_x", &S_x, &b_S_x);
  m_inputSimTree->SetBranchAddress("S_y", &S_y, &b_S_y);
  m_inputSimTree->SetBranchAddress("S_z", &S_z, &b_S_z);
  m_inputSimTree->SetBranchAddress("S_e", &S_e, &b_S_e);
  m_inputSimTree->SetBranchAddress("S_ID", &S_ID, &b_S_ID);
  m_inputSimTree->SetBranchAddress("C_x", &C_x, &b_C_x);
  m_inputSimTree->SetBranchAddress("C_y", &C_y, &b_C_y);
  m_inputSimTree->SetBranchAddress("C_z", &C_z, &b_C_z);
  m_inputSimTree->SetBranchAddress("C_e", &C_e, &b_C_e);
  m_inputSimTree->SetBranchAddress("C_ID", &C_ID, &b_C_ID);

  // If requested prepare truth tree 


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
  
  // Set object pointer
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
  
  // List of branches
  TBranch        *b_mcs_n;   //!
  TBranch        *b_mcs_E;   //!
  TBranch        *b_mcs_pt;   //!
  TBranch        *b_mcs_m;   //!
  TBranch        *b_mcs_eta;   //!
  TBranch        *b_mcs_phi;   //!
  TBranch        *b_mcs_status;   //!
  TBranch        *b_mcs_barcode;   //!
  TBranch        *b_mcs_pdgId;   //!
  TBranch        *b_mcs_charge;   //!
  TBranch        *b_mcs_vx_x;   //!
  TBranch        *b_mcs_vx_y;   //!
  TBranch        *b_mcs_vx_z;   //!

  if (m_doTruth){
    m_inputTruthTree->SetBranchAddress("mcs_n", &mcs_n, &b_mcs_n);
    m_inputTruthTree->SetBranchAddress("mcs_E", &mcs_E, &b_mcs_E);
    m_inputTruthTree->SetBranchAddress("mcs_pt", &mcs_pt, &b_mcs_pt);
    m_inputTruthTree->SetBranchAddress("mcs_m", &mcs_m, &b_mcs_m);
    m_inputTruthTree->SetBranchAddress("mcs_eta", &mcs_eta, &b_mcs_eta);
    m_inputTruthTree->SetBranchAddress("mcs_phi", &mcs_phi, &b_mcs_phi);
    m_inputTruthTree->SetBranchAddress("mcs_status", &mcs_status, &b_mcs_status);
    m_inputTruthTree->SetBranchAddress("mcs_barcode", &mcs_barcode, &b_mcs_barcode);
    m_inputTruthTree->SetBranchAddress("mcs_pdgId", &mcs_pdgId, &b_mcs_pdgId);
    m_inputTruthTree->SetBranchAddress("mcs_charge", &mcs_charge, &b_mcs_charge);
    m_inputTruthTree->SetBranchAddress("mcs_vx_x", &mcs_vx_x, &b_mcs_vx_x);
    m_inputTruthTree->SetBranchAddress("mcs_vx_y", &mcs_vx_y, &b_mcs_vx_y);
    m_inputTruthTree->SetBranchAddress("mcs_vx_z", &mcs_vx_z, &b_mcs_vx_z);
  }

  // Now prepare to do the conversion

  podio::EventStore store;
  podio::ROOTWriter l_writer(m_outFileName,&store);

  auto & mcpColl = store.create<edm4hep::MCParticleCollection>("MCParticles");
  if (m_doTruth){
    l_writer.registerForWrite("MCParticles");
  }
  // This will be used later to convert from pt,eta,phi to px,py,pz
  TLorentzVector TLV_temp;

  // Store the scintillation hits

  auto& schsColl = store.create<edm4hep::SimCalorimeterHitCollection>("S_SimCalorimeterHits");
  l_writer.registerForWrite("S_SimCalorimeterHits");

  // Store the cherenkov hits

  auto& schcColl = store.create<edm4hep::SimCalorimeterHitCollection>("C_SimCalorimeterHits");
  l_writer.registerForWrite("C_SimCalorimeterHits");


  for (unsigned i_evt = 0; i_evt < nevents; ++i_evt){
    if (i_evt % 100) std::cout << "Processing event " << i_evt << std::endl;

    m_inputSimTree->GetEntry(i_evt);

    unsigned int nhits = S_x->size();
    std::cout << "Entry " << i_evt << " sci fibers " << nhits << std::endl;
    for (unsigned int i_hit = 0; i_hit < nhits; ++i_hit){

      // Now deal with the simulation hits

      auto schs = schsColl.create();
      schs.setCellID(S_ID->at(i_hit));
      schs.setEnergy(S_e->at(i_hit));
      schs.setPosition({S_x->at(i_hit),S_y->at(i_hit),S_z->at(i_hit)});
    }

    nhits = C_x->size();
    for (unsigned int i_hit = 0; i_hit < nhits; ++i_hit){

      auto schc = schcColl.create();
      schc.setCellID(C_ID->at(i_hit));
      schc.setEnergy(C_e->at(i_hit));
      schc.setPosition({C_x->at(i_hit),C_y->at(i_hit),C_z->at(i_hit)});

    }

    // Now deal with the MC hits (if requested)

    if (m_doTruth){

      m_inputTruthTree->GetEntry(i_evt);

      for (unsigned int i_mc = 0; i_mc < mcs_n; ++i_mc){
	auto mcp1 = mcpColl.create();
	mcp1.setPDG(mcs_pdgId->at(i_mc));
	mcp1.setGeneratorStatus(mcs_status->at(i_mc));
	mcp1.setCharge(mcs_charge->at(i_mc));
	mcp1.setMass(mcs_m->at(i_mc));
	mcp1.setVertex({mcs_vx_x->at(i_mc),mcs_vx_y->at(i_mc),mcs_vx_z->at(i_mc)});
	TLV_temp.SetPtEtaPhiE(mcs_pt->at(i_mc),mcs_eta->at(i_mc),mcs_phi->at(i_mc),mcs_E->at(i_mc));
	mcp1.setMomentum( {float(TLV_temp.Px()), float(TLV_temp.Py()), float(TLV_temp.Pz())});
      }

    }

    l_writer.writeEvent();
	
    store.clearCollections();
  }
  
  l_writer.finish();

  return true;
  
}
  
bool ConvertToEdm4Hep::OpenInputFiles()
{
  m_inputSimFile = TFile::Open(m_inputSimName.c_str());
  if (!m_inputSimFile->IsOpen()) return false;
  m_inputSimTree = (TTree*) m_inputSimFile->Get(m_inputSimTreeName.c_str());
  if (!m_inputSimTree){
    std::cerr << "Cannot find tree " << m_inputSimTreeName << " in file " << m_inputSimFile->GetName() << std::endl;
    return false;
  }
  if (m_doTruth){
    m_inputTruthFile = TFile::Open(m_inputTruthName.c_str());
    if (!m_inputTruthFile->IsOpen()) return false;
    m_inputTruthTree = (TTree*) m_inputTruthFile->Get(m_inputTruthTreeName.c_str());
    if (!m_inputTruthTree){
      std::cerr << "Cannot find tree " << m_inputTruthTreeName << " in file " << m_inputTruthFile->GetName() << std::endl;
      return false;
    }
  }
  return true;
}
