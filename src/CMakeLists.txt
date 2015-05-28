cmake_minimum_required(VERSION 2.8)

project(LUX)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories(${SFML2_INCLUDE_DIRS})

add_executable(lux
  lux.cc
  local/Bullets.cc
  local/Enemy.cc
  local/Entity.cc
  local/Event.cc
  local/Group.cc
  local/Hero.cc
  local/Sensor.cc
  local/Stars.cc
)

target_link_libraries(lux
  ${SFML2_LIBRARIES}
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/share/lux"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)

install(
  TARGETS lux
  RUNTIME DESTINATION games
)

