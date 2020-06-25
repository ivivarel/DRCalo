# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Create a project:
project( DRCalo_NtupleConverters )

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

file(GLOB NtupleConverters_h "include/*.h")
file(GLOB NtupleConverters_cxx "src/*.cxx")
file(GLOB NtupleConverters_dict_cxx "G__*.cxx")

#message(STATUS ${NtupleConverters_cxx})

add_library( DRCalo_NtupleConvertersLib SHARED ${NtupleConverters_h} ${NtupleConverters_cxx})

target_link_libraries(DRCalo_NtupleConvertersLib ${ROOT_LIBRARIES})
target_include_directories( DRCalo_NtupleConvertersLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )	  

#add_executable( AddTruthToG4Ntuple ${CMAKE_SOURCE_DIR}/utils/UpdateG4tree.cxx )

install( TARGETS DRCalo_NtupleConvertersLib DESTINATION lib )
install( FILES ${NtupleConverters_h} DESTINATION include/NtupleConverters )
install( FILES scripts/UpdateG4Tree.sh DESTINATION scripts ) 
install( FILES macros/UpdateG4tree.cxx DESTINATION macros ) 





