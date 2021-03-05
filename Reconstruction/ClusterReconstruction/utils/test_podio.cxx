#include <iostream>

#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

#include "edm4hep/SimCalorimeterHitCollection.h"
#include "edm4hep/CaloHitContributionCollection.h"

int main()
{
  std::cout << "In main" << std::endl;
  
  podio::EventStore store;
  podio::ROOTWriter l_writer("pippo.root",&store);

  // For testing of SimCalorimeterHits
  
  edm4hep::SimCalorimeterHitCollection * pippo = new edm4hep::SimCalorimeterHitCollection();
  store.registerCollection("somecollection",pippo);
  l_writer.registerForWrite("somecollection");

  // For testing of connections between SimCalorimeterHits and CaloHitContributions

  edm4hep::SimCalorimeterHitCollection * test_Sim_CaloHitContribution = new edm4hep::SimCalorimeterHitCollection();
  store.registerCollection("test_Sim_CaloHitContribution",test_Sim_CaloHitContribution);
  l_writer.registerForWrite("test_Sim_CaloHitContribution");

    edm4hep::CaloHitContributionCollection * test_CaloHitContribution = new edm4hep::CaloHitContributionCollection();
    store.registerCollection("testCaloHitContribution",test_CaloHitContribution);
    l_writer.registerForWrite("testCaloHitContribution");

  
  
  for (unsigned int i = 0; i < 100; ++i){

    std::cout << "Event " << i << std::endl;

    // Now do teh generic testing
    
    for (unsigned int j = 0; j < 5; ++j){
      std::cout << "Hit " << j << std::endl;
      auto myhit =  pippo->create();
      myhit.setEnergy(1000);
      myhit.setPosition({1.,1.,1.});
    }

    // Now do teh specific testing

    // Create a few CaloHitContribution

    auto my_calohit_1 = test_CaloHitContribution->create();
    my_calohit_1.setEnergy(1.);
    my_calohit_1.setTime(1.);
    my_calohit_1.setStepPosition({1.,1.,1.});

    auto my_calohit_2 = test_CaloHitContribution->create();
    my_calohit_2.setEnergy(1.);
    my_calohit_2.setTime(1.);
    my_calohit_2.setStepPosition({2.,2.,2.});

    // Add the CaloHitContributions to a new SimCalorimeterHit

    auto my_simcalohit = test_Sim_CaloHitContribution->create();
    my_simcalohit.addToContributions(my_calohit_1);
    my_simcalohit.addToContributions(my_calohit_2);
    std::cout << "SimCaloHit  " << my_simcalohit.getEnergy() << std::endl;
    
    l_writer.writeEvent();
    store.clearCollections();
  }
  l_writer.finish();
}
  
