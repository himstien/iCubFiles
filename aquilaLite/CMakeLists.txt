# Copyright: 2012 RobotCub Consortium
# Author: Martin Peniak <www.martinpeniak.com>
# CopyPolicy: Released under the terms of the FreeBSD license.

cmake_minimum_required(VERSION 2.8)
project(AquilaLite)

# find packages  
find_package(YARP REQUIRED)

# set flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


set(AQUILA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# put binaries under aquilaLite/bin
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
message(STATUS "Executables will be placed in ${EXECUTABLE_OUTPUT_PATH}")

# put libraries under aquilaLite/lib
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
message(STATUS "Libraries go to ${LIBRARY_OUTPUT_PATH}")

# add aquilaLite libraries
add_subdirectory(libraries)




