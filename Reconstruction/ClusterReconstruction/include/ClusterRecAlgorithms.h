#ifndef DR_CLUSTERRECALGORITHMS
#define DR_CLUSTERRECALGORITHMS

#include "DR_CaloGridHelper.h"

#include "edm4hep/ClusterCollection.h"

typedef std::vector<DR_GridID> DR_listID;

class ClusterRecAlgorithms
{
 public:
  ClusterRecAlgorithms();
  ~ClusterRecAlgorithms();

  void PreClustering(edm4hep::ClusterCollection & l_clusColl, DR_CaloGridHelper * l_caloGrid); // Seed Finding plus expansion and creation of protoclusters.
  
  void AddToCluster(edm4hep::Cluster & l_clus, DR_CaloGridHelper * l_caloGrid,DR_GridID l_id); // Add all fibers linked to pseudo-cell DR_GridID to teh cluster
  
  void Expand(DR_GridID l_id /* ID to be checked for expansion */,
	      DR_CaloGridHelper * l_caloGrid /* grid to be used for expansion */,
	      DR_listID& l_expand /* list of IDs already belonging to the cluster*/); // Expand the seed

  void ComputeCluster(edm4hep::Cluster & l_clus); // The cluster has been linked to all its fibers. It is time to compute the cluster valiables

  void RemoveAdjacentSeeds(DR_listID l_listMax,DR_CaloGridHelper * l_caloGrid);
  
  void SetSeedTh(float l_seedTh){m_seedTh = l_seedTh;}
  void SetExpandTh(float l_expandTh){m_expandTh = l_expandTh;}
  void SetSeedIsolTh(float l_seedIsolTh){m_seedIsolTh = l_seedIsolTh;}
  void SetRelMergeTh(float l_relMergeTh){m_relMergeTh = l_relMergeTh;}

  void DoDebug(bool l_debug = true) {m_debug = l_debug;}
  
 private:
  float m_seedTh; // Seed threshold
  float m_expandTh; // Threshold to expand the cluster from a seed
  float m_seedIsolTh; // Minimum distance between two seeds (for the moment not used)
  float m_relMergeTh; // If more than this fraction of the most energetic cluster is shared, then merge the two clusters
  bool m_debug;

};

#endif // #ifndef DR_CLUSTERRECALGORITHMS
