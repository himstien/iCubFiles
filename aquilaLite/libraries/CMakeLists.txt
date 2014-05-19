# Copyright: 2012 RobotCub Consortium
# Author: Martin Peniak <www.martinpeniak.com>
# CopyPolicy: Released under the terms of the FreeBSD license.

find_package(YARP REQUIRED) 

if(YARP_FOUND)
	add_subdirectory(tracker)
	add_subdirectory(iCubMotor)
	message(STATUS "The following AquilaLite libraries will be compiled:")
	message(STATUS " - tracker")
	message(STATUS " - iCubMotor")
else()
	message("The following AquilaLite libraries will not be compiled:")
	message(" - tracker")
	message(" - iCubMotor")
endif()
