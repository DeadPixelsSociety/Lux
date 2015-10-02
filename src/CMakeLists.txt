cmake_minimum_required(VERSION 2.8)

project(LUX)

option(LUX_MOUSE_CONTROL "Control the game with mouse" ON)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Search for the library
if (NOT LUX_MOUSE_CONTROL)
  find_package(Threads)

  find_path(LIBSERIALPORT_INCLUDE_DIR libserialport.h
    PATH_SUFFIXES include)
  find_library(LIBSERIALPORT_LIBRARIES NAMES serialport
    PATH_SUFFIXES lib)

  include_directories(${LIBSERIALPORT_INCLUDE_DIR})
endif (NOT LUX_MOUSE_CONTROL)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories(${SFML2_INCLUDE_DIRS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lux
  lux.cc
  local/Bonus.cc
  local/Bullets.cc
  local/Enemy.cc
  local/Hero.cc
  local/Particles.cc
  local/Scenario.cc
  local/Sensor.cc
  local/Ship.cc
  local/Shoot.cc
  local/Stars.cc
  # game skel
  game/Action.cc
  game/AssetManager.cc
  game/Camera.cc
  game/Control.cc
  game/Entity.cc
  game/EntityManager.cc
  game/EventManager.cc
  game/Log.cc
  game/ResourceManager.cc
  game/WindowGeometry.cc
  game/WindowSettings.cc
)

target_link_libraries(lux
  ${SFML2_LIBRARIES}
  ${Boost_LIBRARIES}
)

if (NOT LUX_MOUSE_CONTROL)
  target_link_libraries(lux
    ${CMAKE_THREAD_LIBS_INIT}
    ${LIBSERIALPORT_LIBRARIES}
  )
endif (NOT LUX_MOUSE_CONTROL)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share/lux"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)

install(
  TARGETS lux
  RUNTIME DESTINATION games
)
