#include "ConvertToEdm4Hep.h"

// edm4hep includes

#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/SimCalorimeterHitCollection.h"

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"


ConvertToEdm4Hep::ConvertToEdm4Hep() :
  m_outFileName("output.podio.root"),
  m_inputSimName(""),
  m_inputTruthName(""),
  m_debug(false)
{}

ConvertToEdm4Hep::~ConvertToEdm4Hep()
{}

bool ConvertToEdm4Hep::Convert()
{
  if (m_debug) std::cout << "In ConvertToEdm4Hep::Convert" << std::endl;

  podio::EventStore store;
  podio::ROOTWriter l_writer(m_outFileName,&store);

  auto & mcps = store.create<edm4hep::MCParticleCollection>("MCParticles");
  l_writer.registerForWrite("MCParticles");

  auto& schs = store.create<edm4hep::SimCalorimeterHitCollection>("SimCalorimeterHits");
  l_writer.registerForWrite("SimCalorimeterHits");

  unsigned nevents = 10;

  for (unsigned i = 0; i < nevents; ++i){
    if (nevents % 100) std::cout << "Processing event " << i << std::endl;

    auto mcp1 = mcps.create();
    mcp1.setPDG(2212);
    mcp1.setMomentum( {100, 50, 1000});

    // Now deal with the simulation hits

    auto sch1 = schs.create();
    sch1.setCellID(0xaaaaaaaaaa);
    sch1.setEnergy(0.1);
    sch1.setPosition({1,1,1});
    
    l_writer.writeEvent();

    store.clearCollections();
  }
  
  l_writer.finish();

  return true;
  
}
  
