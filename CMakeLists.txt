cmake_minimum_required(VERSION 3.9)
project(Kingdom_Defense)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/cmake/Modules")
find_package(SFML 2 COMPONENTS REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable(New main.cpp)


target_link_libraries(New ${SFML_LIBRARIES} )