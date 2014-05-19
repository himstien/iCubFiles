# Copyright: 2012 RobotCub Consortium
# Author: Martin Peniak
# CopyPolicy: Released under the terms of the FreeBSD license

find_package(ICUB)

set(LIBNAME cubmotor)
project(${LIBNAME})

set(INCLUDES include/iCubMotor.h)
set(SOURCES src/iCubMotor.cpp)

source_group("Header Files" FILES ${INCLUDES})
source_group("Source Files" FILES ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include ${YARP_INCLUDE_DIRS} ${ICUB_INCLUDE_DIRS})

add_library(${LIBNAME} ${INCLUDES} ${SOURCES})
target_link_libraries(${LIBNAME} icubmod)
install(TARGETS ${LIBNAME} DESTINATION lib)



