# Copyright: 2012 RobotCub Consortium
# Author: Martin Peniak
# CopyPolicy: Released under the terms of the FreeBSD license

set(LIBNAME tracker)
project(${LIBNAME})

set(INCLUDES include/tracker.h)
set(SOURCES src/tracker.cpp)

source_group("Header Files" FILES ${INCLUDES})
source_group("Source Files" FILES ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include ${YARP_INCLUDE_DIRS})

add_library(${LIBNAME} ${INCLUDES} ${SOURCES})
target_link_libraries(${LIBNAME})
install(TARGETS ${LIBNAME} DESTINATION lib)



