# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Create a project:
project( DRCalo_DRDigitization )

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)
find_package(EDM4HEP)
find_package(podio)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(ROOT_BUG)

ROOT_GENERATE_DICTIONARY(G__FiberDigitizer ${CMAKE_CURRENT_SOURCE_DIR}/include/FiberDigitizer.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/FiberDigitizerLinkDef.h DEPENDENCIES DRCalo_DdAndCalibrationLib sipm)

ROOT_GENERATE_DICTIONARY(G__DigitSteer ${CMAKE_CURRENT_SOURCE_DIR}/include/DigitSteer.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/DigitSteerLinkDef.h DEPENDENCIES DRCalo_DdAndCalibrationLib sipm)

file(GLOB DRDigitization_h "include/*.h")
file(GLOB DRDigitization_cxx "src/*.cxx")



add_library( DRCalo_DRDigitizationLib SHARED ${DRDigitization_h} ${DRDigitization_cxx} G__FiberDigitizer.cxx G__DigitSteer.cxx)
add_dependencies(DRCalo_DRDigitizationLib DRCalo_DdAndCalibrationLib)

target_link_libraries(DRCalo_DRDigitizationLib ${ROOT_LIBRARIES} EDM4HEP::edm4hep podio::podioRootIO DRCalo_DdAndCalibrationLib sipm)
target_include_directories(DRCalo_DRDigitizationLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_executable( RunDRDigitization ${CMAKE_CURRENT_SOURCE_DIR}/utils/RunDRDigitization.cxx )
target_link_libraries( RunDRDigitization ${ROOT_LIBRARIES} DRCalo_DRDigitizationLib sipm)

install(FILES ${DRDigitization_h} DESTINATION include/DRDigitization)
install(FILES python/run_digitization.py DESTINATION python)
install(FILES python/test_digitization.py DESTINATION python)
install( TARGETS DRCalo_DRDigitizationLib DESTINATION lib )
install(FILES ${CMAKE_BINARY_DIR}/Digitization/DRDigitization/libDigitSteer.rootmap DESTINATION lib )
install(FILES ${CMAKE_BINARY_DIR}/Digitization/DRDigitization/libDigitSteer_rdict.pcm DESTINATION lib )
install(FILES ${CMAKE_BINARY_DIR}/Digitization/DRDigitization/libFiberDigitizer.rootmap DESTINATION lib )
install(FILES ${CMAKE_BINARY_DIR}/Digitization/DRDigitization/libFiberDigitizer_rdict.pcm DESTINATION lib )
install( TARGETS DRCalo_DRDigitizationLib LIBRARY DESTINATION lib )
install( TARGETS RunDRDigitization DESTINATION bin )

