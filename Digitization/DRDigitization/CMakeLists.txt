# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Create a project:
project( DRCalo_DRDigitization )

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED)
find_package(EDM4HEP)


#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

file(GLOB DRDigitization_h "include/*.h")
file(GLOB DRDigitization_cxx "src/*.cxx")
file(GLOB DRDigitization_dict_cxx "G__*.cxx")

add_library( DRCalo_DRDigitizationLib SHARED ${DRDigitization_h} ${DRDigitization_cxx})

target_link_libraries(DRCalo_DRDigitizationLib ${ROOT_LIBRARIES} EDM4HEP::edm4hep DRCalo_DdAndCalibrationLib sipm)
target_include_directories(DRCalo_DRDigitizationLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

install(FILES ${DRDigitization_h} DESTINATION include/DRDigitization)
install( TARGETS DRCalo_DRDigitizationLib DESTINATION lib )


