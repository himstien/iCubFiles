# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/icub/myiCubFiles/moveHands

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/icub/myiCubFiles/moveHands

# Include any dependencies generated for this target.
include CMakeFiles/moveHand.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/moveHand.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/moveHand.dir/flags.make

CMakeFiles/moveHand.dir/moveHands.cpp.o: CMakeFiles/moveHand.dir/flags.make
CMakeFiles/moveHand.dir/moveHands.cpp.o: moveHands.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/myiCubFiles/moveHands/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/moveHand.dir/moveHands.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/moveHand.dir/moveHands.cpp.o -c /home/icub/myiCubFiles/moveHands/moveHands.cpp

CMakeFiles/moveHand.dir/moveHands.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/moveHand.dir/moveHands.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/myiCubFiles/moveHands/moveHands.cpp > CMakeFiles/moveHand.dir/moveHands.cpp.i

CMakeFiles/moveHand.dir/moveHands.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/moveHand.dir/moveHands.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/myiCubFiles/moveHands/moveHands.cpp -o CMakeFiles/moveHand.dir/moveHands.cpp.s

CMakeFiles/moveHand.dir/moveHands.cpp.o.requires:
.PHONY : CMakeFiles/moveHand.dir/moveHands.cpp.o.requires

CMakeFiles/moveHand.dir/moveHands.cpp.o.provides: CMakeFiles/moveHand.dir/moveHands.cpp.o.requires
	$(MAKE) -f CMakeFiles/moveHand.dir/build.make CMakeFiles/moveHand.dir/moveHands.cpp.o.provides.build
.PHONY : CMakeFiles/moveHand.dir/moveHands.cpp.o.provides

CMakeFiles/moveHand.dir/moveHands.cpp.o.provides.build: CMakeFiles/moveHand.dir/moveHands.cpp.o

# Object files for target moveHand
moveHand_OBJECTS = \
"CMakeFiles/moveHand.dir/moveHands.cpp.o"

# External object files for target moveHand
moveHand_EXTERNAL_OBJECTS =

moveHand: CMakeFiles/moveHand.dir/moveHands.cpp.o
moveHand: CMakeFiles/moveHand.dir/build.make
moveHand: /usr/lib/libYARP_OS.so.2.3.22
moveHand: /usr/lib/libYARP_sig.so.2.3.22
moveHand: /usr/lib/libYARP_math.so.2.3.22
moveHand: /usr/lib/libYARP_dev.so.2.3.22
moveHand: /usr/lib/libYARP_wire_rep_utils.a
moveHand: /usr/lib/libyarpcar.so.2.3.22
moveHand: /usr/lib/libyarp_xmlrpc.so.2.3.22
moveHand: /usr/lib/libyarp_tcpros.so.2.3.22
moveHand: /usr/lib/libyarp_bayer.so.2.3.22
moveHand: /usr/lib/libyarp_priority.so.2.3.22
moveHand: /usr/lib/libYARP_name.so.2.3.22
moveHand: /usr/lib/libYARP_init.so.2.3.22
moveHand: /usr/lib/libyarpcar.so.2.3.22
moveHand: /usr/lib/libYARP_dev.so.2.3.22
moveHand: /usr/lib/libyarp_xmlrpc.so.2.3.22
moveHand: /usr/lib/libyarp_tcpros.so.2.3.22
moveHand: /usr/lib/libYARP_wire_rep_utils.a
moveHand: /usr/lib/libyarp_bayer.so.2.3.22
moveHand: /usr/lib/libyarp_priority.so.2.3.22
moveHand: /usr/lib/libYARP_math.so.2.3.22
moveHand: /usr/lib/libYARP_sig.so.2.3.22
moveHand: /usr/lib/libgsl.so
moveHand: /usr/lib/libgslcblas.so
moveHand: /usr/lib/libYARP_name.so.2.3.22
moveHand: /usr/lib/libYARP_OS.so.2.3.22
moveHand: /usr/lib/libACE.so
moveHand: CMakeFiles/moveHand.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable moveHand"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/moveHand.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/moveHand.dir/build: moveHand
.PHONY : CMakeFiles/moveHand.dir/build

CMakeFiles/moveHand.dir/requires: CMakeFiles/moveHand.dir/moveHands.cpp.o.requires
.PHONY : CMakeFiles/moveHand.dir/requires

CMakeFiles/moveHand.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/moveHand.dir/cmake_clean.cmake
.PHONY : CMakeFiles/moveHand.dir/clean

CMakeFiles/moveHand.dir/depend:
	cd /home/icub/myiCubFiles/moveHands && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/icub/myiCubFiles/moveHands /home/icub/myiCubFiles/moveHands /home/icub/myiCubFiles/moveHands /home/icub/myiCubFiles/moveHands /home/icub/myiCubFiles/moveHands/CMakeFiles/moveHand.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/moveHand.dir/depend
