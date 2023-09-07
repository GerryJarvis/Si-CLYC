#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.21)
project(CLYC)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(CLYC CLYC.cc ${sources} ${headers})
target_link_libraries(CLYC ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build CLYC. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(CLYC_SCRIPTS
#  exampleB1.in
#  exampleB1.out
#  run1.mac
#  run2.mac
  init_vis.mac
  vis.mac
  gpsNeutron.mac
  gpsDeutron.mac
  gpsTriton.mac 
  gpsH.mac
  gpsHe.mac
  gpsLi.mac
  gpsB.mac
  gpsBe.mac
  gpsC.mac
  gpsN.mac
  gpsO.mac
  gpsFe.mac
  # opticalphoton.mac
  AmBeNeutron.mac
  1--100H.mac
  252Cf.mac
  )

foreach(_script ${CLYC_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
# add_custom_target(CLYC DEPENDS CLYC)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS CLYC DESTINATION bin)
