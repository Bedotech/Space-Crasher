project(spacecrasher)

#Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

set (Spacecrasher_VERSION_MAJOR 1)
set (Spacecrasher_VERSION_MINOR 0)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

# asteroid include.
include_directories("${PROJECT_SOURCE_DIR}/src")
add_library(asteroid src/asteroid.cpp)

add_executable(hello ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(hello asteroid)
target_link_libraries(hello ${SDL2_LIBRARY})

install(TARGETS hello DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
