cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set(CMAKE_INSTALL_PREFIX "$ENV{DRCALO_ARCHCONF}")

project(dual-readout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEPMC_DIR "$ENV{HEPMC_DIR}")
set(HEPMC3_DIR "$ENV{HEPMC_DIR}")
set(PYTHIA_DIR "$ENV{PYTHIA_DIR}")
set(FASTJET_DIR "$ENV{FASTJET_DIR}")

message( STATUS "Install path ${CMAKE_INSTALL_PREFIX}" )

add_subdirectory(dual-readout)
add_subdirectory(AnalysisTools)
add_subdirectory(NtupleConverters)
#add_subdirectory(Reconstruction/ClusterReconstruction)

#This for the moment does not work, conflict between HepMC versions
#add_subdirectory(Git_IDEA_CALO_FIBER/DRC4pifibers/DRC4pigeometry/Dream/B4)

### create the setup file

message (STATUS "Creating the setup.sh file" )

configure_file(DR_CMakeTools/scripts/setup_sh.in ${CMAKE_CURRENT_BINARY_DIR}/setup.sh @ONLY) 


