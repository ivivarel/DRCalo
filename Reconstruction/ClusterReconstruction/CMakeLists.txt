# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Create a project:
project( DRCalo_ClusterReconstruction )

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED)
find_package(EDM4HEP)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

file(GLOB ClusterReconstruction_h "include/*.h")
file(GLOB ClusterReconstruction_cxx "src/*.cxx")
file(GLOB ClusterReconstruction_dict_cxx "G__*.cxx")

#message(STATUS ${NtupleConverters_cxx})

add_library( DRCalo_ClusterReconstructionLib SHARED ${ClusterReconstruction_h} ${ClusterReconstruction_cxx})

target_link_libraries(DRCalo_ClusterReconstructionLib ${ROOT_LIBRARIES} EDM4HEP::edm4hep podio::podioRootIO DRCalo_DdAndCalibrationLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include )

add_executable( ConvertToEDM4Hep ${CMAKE_CURRENT_SOURCE_DIR}/utils/ConvertRawOutputToEDM4Hep.cxx )
target_link_libraries( ConvertToEDM4Hep ${ROOT_LIBRARIES} DRCalo_ClusterReconstructionLib )

add_executable( TestClusterRecSteer ${CMAKE_CURRENT_SOURCE_DIR}/utils/TestClusterRecSteer.cxx )
target_link_libraries( TestClusterRecSteer ${ROOT_LIBRARIES} DRCalo_ClusterReconstructionLib )

add_executable( TestPodio ${CMAKE_CURRENT_SOURCE_DIR}/utils/test_podio.cxx )
target_link_libraries( TestPodio ${ROOT_LIBRARIES} DRCalo_ClusterReconstructionLib EDM4HEP::edm4hep podio::podioRootIO )
add_executable( TestReadPodio ${CMAKE_CURRENT_SOURCE_DIR}/utils/test_readpodio.cxx )
target_link_libraries( TestReadPodio ${ROOT_LIBRARIES} DRCalo_ClusterReconstructionLib EDM4HEP::edm4hep podio::podioRootIO )

install(FILES ${ClusterReconstruction_h} DESTINATION include/ClusterReconstruction)
install( TARGETS ConvertToEDM4Hep DESTINATION bin )
install( TARGETS TestClusterRecSteer DESTINATION bin )
install( TARGETS TestPodio DESTINATION bin )
install( TARGETS TestReadPodio DESTINATION bin ) 
install( TARGETS DRCalo_ClusterReconstructionLib DESTINATION lib )


