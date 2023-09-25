#include "ClusterRecAlgorithms.h"

#include <iostream>

ClusterRecAlgorithms::ClusterRecAlgorithms():
  m_seedTh(0.050/*this is roughly 20 photons for 400 ph/GeV*/),m_expandTh(0.02),m_seedIsolTh(0),m_debug(false)
{
}

ClusterRecAlgorithms::~ClusterRecAlgorithms()
{}

void ClusterRecAlgorithms::PreClustering(edm4hep::ClusterCollection & l_clusColl, DR_CaloGridHelper * l_caloGrid)
{
  DR_listID l_clusCand;
  l_clusCand.clear();
  double l_candEne;
  l_candEne = 0;
  double totEne;
  totEne = 0;
  
  // Make a loop on all grid pseudocells, save the IDs of the candidate seeds

  if (m_debug) std::cout << "ClusterRecAlgorithms::FindSeeds : new event. Starting to look for seeds" << std::endl;

  auto l_grid = l_caloGrid->GetGrid();
  
  for (auto itr = l_grid.begin(); itr != l_grid.end(); ++itr){
    l_candEne = l_caloGrid->GetEnergy(itr->first);
    totEne += l_candEne;
    if (m_debug) std::cout << "New cluster being considered as seed with ID " << itr->first << " and energy " << l_candEne << std::endl;
    
    if (l_candEne < m_seedTh) continue; // check if seed is above threshold.
    // Now check if the seed is a local maximum
    
    if (m_debug) std::cout << "The candidate with energy " << l_candEne << " is above the seed threshold of " << m_seedTh << std::endl;
    
    bool isLocalMaximum;
    isLocalMaximum = true;
    
    // Thanks to how the grid is built, the adjacent 8 pseudocells can be easily obtained by considering the GridID. ID +- 1 --> same cos theta, adjacent in phi. ID +- m_spacing --> same phi, adjacent cos theta, etc...
    
    DR_listID adjCells = l_caloGrid->ListOfAdjacentCellID(itr->first);
    
    for (auto adjItr = adjCells.begin(); adjItr != adjCells.end(); ++adjItr){
      //      if (m_debug) std::cout << "Adjacent cell with ID " << (*adjItr) << " and energy " << l_caloGrid->GetEnergy(*adjItr) << std::endl;
      if (l_candEne < l_caloGrid->GetEnergy(*adjItr)) isLocalMaximum = false;
    }
    
    if (isLocalMaximum){
      if (m_debug) std::cout << "The candidate is a local maximum" << std::endl;
      l_clusCand.push_back(itr->first);
    }
    
  } //for (auto itr = l_grid.begin(); itr != l_grid.end(); ++itr){

  // Now check for adjacent local maxima (that is, two maxima withe the same energy closeby. This is not so infrequent due to the quantised nature of the fiber signal)

  RemoveAdjacentSeeds(l_clusCand,l_caloGrid);
  
  if (m_debug){
    std::cout << "\n\n\n List of local maxima: \n" << std::endl;
    for  (auto l_id : l_clusCand){
      std::cout << "CellID " << l_id << " with energy " << l_caloGrid->GetEnergy(l_id) << std::endl;
    }
  }

  // Now we have got the seed IDs: form the clusters

  for (DR_GridID l_id : l_clusCand){
    DR_listID l_clusExpand; // store the list of cells added via expansion to this cluster
    l_clusExpand.clear();

    l_clusExpand.push_back(l_id);

    if (m_debug) std::cout << "Checking seed " << l_id << " for expansion" << std::endl;
    
    // Expand the cluster
    Expand(l_id,l_caloGrid,l_clusExpand);

    if (m_debug) {
      std::cout << "The cells belonging to this clusters are: " << std::endl;
      for (auto itr : l_clusExpand){
	std::cout << (itr) << std::endl;
      }
    }
    
    auto l_cluster = l_clusColl.create();
    
    // Create a cluster from each seed
    for (DR_GridID l_pseudoCl_id: l_clusExpand){
      AddToCluster(l_cluster,l_caloGrid,l_pseudoCl_id);
    }
    
    ComputeCluster(l_cluster);
    
  }

  
  if (m_debug) {
    std::cout << "The total grid energy is " << totEne << std::endl;
    std::cout << "There are " << l_clusColl.size() << " clusters around " << std::endl;
    std::cout << "The cluster energies are: " << std::endl;
    for (auto clus : l_clusColl){
      std::cout << clus.getEnergy() << std::endl;
    }
  }

    // List of pseudo-clusters complete      
  
}

void ClusterRecAlgorithms::AddToCluster(edm4hep::Cluster & l_clus, DR_CaloGridHelper * l_caloGrid,DR_GridID l_id)
{
  auto l_grid = l_caloGrid->GetGrid();
  for (edm4hep::ConstCalorimeterHit * l_hit : l_grid[l_id]){ 
    l_clus.addToHits((*l_hit));
  }
}

void ClusterRecAlgorithms::Expand(DR_GridID l_id, DR_CaloGridHelper * l_caloGrid, DR_listID & l_expand)
{
  // Get a list of adjacent pseudocells
  DR_listID  adj_list_id= l_caloGrid->ListOfAdjacentCellID(l_id);
  //if (m_debug) std::cout << "checking adjacent cells for " << l_id << std::endl;
  for (DR_GridID  adj_id : adj_list_id){
    
    // check if they are already part of the pseudo-cluster
    bool already_clus;
    already_clus = false;
    for (DR_GridID exp_id : l_expand){
      if (exp_id == adj_id) {
	already_clus = true;
	break;
      }
    }
    
    if (already_clus) {
      //if (m_debug) std::cout << adj_id << " already in the pseudo-cluster " << std::endl;
      continue; // if already in the pseudo-cluster, move to the next pseudocell
    }
    
    //if (m_debug) std::cout << adj_id << " added to the pseudo-cluster " << std::endl;
    l_expand.push_back(adj_id); // Add the cell to the pseudocluster anyway
     
    if (l_caloGrid->GetEnergy(adj_id) > m_expandTh) { // if the energy is above the threshold for expansion, also check its adjacent cells for expansion
      //if (m_debug) std::cout << adj_id << " above threshold for expansion " << std::endl;
      Expand(adj_id,l_caloGrid,l_expand);
    }
    
  } //for (DR_GridID  adj_id : adj_list_id){

}

void ClusterRecAlgorithms::ComputeCluster(edm4hep::Cluster & l_clus)
{
  double energy;
  energy = 0;
  float l_x, l_y, l_z;
  l_x = 0;
  l_y = 0;
  l_z = 0;
  
  for (auto itr = l_clus.hits_begin(); itr != l_clus.hits_end(); ++itr){
    energy += itr->getEnergy();
    l_x += itr->getEnergy() * itr->getPosition().x;
    l_y += itr->getEnergy() * itr->getPosition().y;
    l_z += itr->getEnergy() * itr->getPosition().z;
  }
  if (energy != 0){
    l_x = l_x/TMath::Abs(energy);
    l_y = l_y/TMath::Abs(energy);
    l_z = l_z/TMath::Abs(energy);
  }

  l_clus.setEnergy(energy);
  l_clus.setPosition({l_x,l_y,l_z});
}

void ClusterRecAlgorithms::RemoveAdjacentSeeds(DR_listID l_listMax,DR_CaloGridHelper * l_caloGrid)
{
  std::cout << "Initial list of cell ids " << std::endl;
  for (auto itr = l_listMax.begin();itr != l_listMax.end(); ++itr){
    std::cout << (*itr) << std::endl;
  }
  if (l_listMax.size() < 2) return;
  
  for (auto itr = l_listMax.begin();itr != l_listMax.end(); ++itr){
    for (auto itr1 = itr + 1; itr1 != l_listMax.end(); ++itr1){
      DR_listID adjCells = l_caloGrid->ListOfAdjacentCellID((*itr1));
      if (std::find(adjCells.begin(), adjCells.end(), (*itr)) != adjCells.end()){
	l_listMax.erase(itr1);
	itr1--;
      }
    }
  }
  std::cout << "Final " << std::endl;
  for (auto itr = l_listMax.begin();itr != l_listMax.end(); ++itr){
    std::cout << (*itr) << std::endl;
  }
}
