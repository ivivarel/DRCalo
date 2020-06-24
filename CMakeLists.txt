cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(dual-readout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEPMC_DIR "$ENV{HEPMC_DIR}")
set(HEPMC3_DIR "$ENV{HEPMC_DIR}")
set(PYTHIA_DIR "$ENV{PYTHIA_DIR}")
set(FASTJET_DIR "$ENV{FASTJET_DIR}")

add_subdirectory(dual-readout)

#This for the moment does not work, conflict between HepMC versions
#add_subdirectory(Git_IDEA_CALO_FIBER/DRC4pifibers/DRC4pigeometry/Dream/B4)

