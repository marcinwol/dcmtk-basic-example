# This is example of the cmake file that can be used for basic compilation of a C++11 program
# that uses DCMTK 3.6.0  avaliable in ubuntu 14.04

cmake_minimum_required(VERSION 2.8)

# name of the cpp project
project(testDMCTK)

# cpp flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# specify that we have a config file. This is required, since DCMTK package for Ubuntu 14.04 
# uses /usr/include/dcmtk/config/cfunix.h to setup dcmtk. The file is only loaded by
# DCMTK's /usr/include/dcmtk/config/osconfig.h when HAVE_CONFIG_H is set.
add_definitions(-DHAVE_CONFIG_H)

# define location of the source code. This is used so that we can refer in the example
# code to the DCMIMAGES folder relatively to the source folder.
add_definitions(-DSOURCE_CODE_LOCATION="${CMAKE_SOURCE_DIR}")

# our source file
set(SOURCE_FILES main.cpp)

# search for DCMTK library and header files 
find_package(DCMTK REQUIRED)

# specify DCMTK header include directories
include_directories(${DCMTK_INCLUDE_DIRS})

# set output executable of our test program
add_executable(testDMCTK ${SOURCE_FILES})

# link DCMTK library files 
target_link_libraries(testDMCTK ${DCMTK_LIBRARIES})


