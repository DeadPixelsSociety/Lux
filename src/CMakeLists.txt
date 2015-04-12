cmake_minimum_required(VERSION 2.8)

project(LUX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories(${SFML2_INCLUDE_DIRS})

add_executable(lux
  lux.cc
  local/Enemy.cc
  local/Entity.cc
  local/Group.cc
  local/Hero.cc
  local/Sensor.cc
)

target_link_libraries(lux
  ${SFML2_LIBRARIES}
)
