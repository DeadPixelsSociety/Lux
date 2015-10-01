cmake_minimum_required(VERSION 2.8)

project(LUX)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)

find_package(Boost REQUIRED COMPONENTS filesystem system)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories(${SFML2_INCLUDE_DIRS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/local/path.h.in ${CMAKE_CURRENT_BINARY_DIR}/config/path.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/config)

add_executable(lux
  lux.cc
  local/Assets.cc
  local/Bonus.cc
  local/Bullets.cc
  local/Camera.cc
  local/Enemy.cc
  local/Entity.cc
  local/Event.cc
  local/Group.cc
  local/Hero.cc
  local/Particles.cc
  local/Resources.cc
  local/Scenario.cc
  local/Sensor.cc
  local/Ship.cc
  local/Shoot.cc
  local/Stars.cc
  local/WindowGeometry.cc
  local/WindowSettings.cc
)

target_link_libraries(lux
  ${SFML2_LIBRARIES}
  ${Boost_LIBRARIES}
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share/lux"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)

install(
  TARGETS lux
  RUNTIME DESTINATION games
)

