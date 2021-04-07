#include <iostream>

#include <TFile.h>
#include <TH1F.h>

#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CaloHitContributionCollection.h"

#include <map>
#include <vector>

void doCollection(std::string collectionName, std::map< std::vector<TH1F *> > l_histos, bool verbose);

int main()
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
  
  podio::EventStore store;
  podio::ROOTReader l_reader;
  l_reader.openFile(argv[1]);
  if (! l_reader.isValid()){
    std::cerr << "Cannot find file " << argv[1] << std::endl;
    return -1;
  }
  store.setReader(&l_reader);

  unsigned int nentries = l_reader.getEntries();

  std::cout << "Number of entries " << nentries << std::endl;

  if (nentries <=0){
    std::cout << "Sorry, don't know what to do with a file with zero entries" << std::endl;
    return -1;
  }
  
  std::cout << "\nThe code will produce a detailed printout of the first event, and an output file called hist_output.root containing some validation histograms\n" << std::endl;

  bool verbose = true;
  
  for (unsigned int i_evt = 0; i_evt < nentries; ++i_evt){
    
    if (i_evt > 0) verbose = false;

    if (verbose) std::cout << "Retrieving collection " << 
    
    auto & s_hitColl = store.get<edm4hep::SimCalorimeterHitCollection>("test_Sim_CaloHitContribution");

    
    std::cout << "Is Valid? " << s_hitColl.isValid() << std::endl;
  // For testing of SimCalorimeterHits

    std::cout << "Number of hits " << s_hitColl.size();
    for (auto&  hit : s_hitColl){
      std::cout << "energy " << hit.getEnergy() << std::endl;
      std::cout << "This hit has " << hit.contributions_size() << std::endl;
      std::cout << "Now looping over the CaloHitContributions " << std::endl;
      for (std::vector<::edm4hep::ConstCaloHitContribution>::const_iterator itr = hit.contributions_begin(); itr != hit.contributions_end(); ++itr){
	std::cout << "In loop " << std::endl;
	std::cout << itr->getTime() << std::endl;
      }
    }
    store.clear();
    l_reader.endOfEvent();
  }

  return 0;
}
