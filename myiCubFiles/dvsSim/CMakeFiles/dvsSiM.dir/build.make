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
CMAKE_SOURCE_DIR = /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim

# Include any dependencies generated for this target.
include CMakeFiles/dvsSiM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dvsSiM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dvsSiM.dir/flags.make

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o: CMakeFiles/dvsSiM.dir/flags.make
CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o: convertToSpikes.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o -c /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim/convertToSpikes.cpp

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim/convertToSpikes.cpp > CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.i

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim/convertToSpikes.cpp -o CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.s

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.requires:
.PHONY : CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.requires

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.provides: CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.requires
	$(MAKE) -f CMakeFiles/dvsSiM.dir/build.make CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.provides.build
.PHONY : CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.provides

CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.provides.build: CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o

# Object files for target dvsSiM
dvsSiM_OBJECTS = \
"CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o"

# External object files for target dvsSiM
dvsSiM_EXTERNAL_OBJECTS =

dvsSiM: CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o
dvsSiM: CMakeFiles/dvsSiM.dir/build.make
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_math.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_dev.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_name.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_init.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_math.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_dev.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.62.1
dvsSiM: /usr/local/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.62.1
dvsSiM: CMakeFiles/dvsSiM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable dvsSiM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dvsSiM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dvsSiM.dir/build: dvsSiM
.PHONY : CMakeFiles/dvsSiM.dir/build

CMakeFiles/dvsSiM.dir/requires: CMakeFiles/dvsSiM.dir/convertToSpikes.cpp.o.requires
.PHONY : CMakeFiles/dvsSiM.dir/requires

CMakeFiles/dvsSiM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dvsSiM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dvsSiM.dir/clean

CMakeFiles/dvsSiM.dir/depend:
	cd /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim /home/icub/Himanshu_local/iCubFiles/myiCubFiles/dvsSim/CMakeFiles/dvsSiM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dvsSiM.dir/depend
