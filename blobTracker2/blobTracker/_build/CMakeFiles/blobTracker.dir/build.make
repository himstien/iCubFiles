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
CMAKE_SOURCE_DIR = /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build

# Include any dependencies generated for this target.
include CMakeFiles/blobTracker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/blobTracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blobTracker.dir/flags.make

CMakeFiles/blobTracker.dir/blob_tracker.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/blob_tracker.cpp.o: ../blob_tracker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/blob_tracker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/blob_tracker.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/blob_tracker.cpp

CMakeFiles/blobTracker.dir/blob_tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/blob_tracker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/blob_tracker.cpp > CMakeFiles/blobTracker.dir/blob_tracker.cpp.i

CMakeFiles/blobTracker.dir/blob_tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/blob_tracker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/blob_tracker.cpp -o CMakeFiles/blobTracker.dir/blob_tracker.cpp.s

CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.requires

CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.provides: CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.provides

CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.provides.build: CMakeFiles/blobTracker.dir/blob_tracker.cpp.o

CMakeFiles/blobTracker.dir/eventCodec.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/eventCodec.cpp.o: ../eventCodec.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/eventCodec.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/eventCodec.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventCodec.cpp

CMakeFiles/blobTracker.dir/eventCodec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/eventCodec.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventCodec.cpp > CMakeFiles/blobTracker.dir/eventCodec.cpp.i

CMakeFiles/blobTracker.dir/eventCodec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/eventCodec.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventCodec.cpp -o CMakeFiles/blobTracker.dir/eventCodec.cpp.s

CMakeFiles/blobTracker.dir/eventCodec.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/eventCodec.cpp.o.requires

CMakeFiles/blobTracker.dir/eventCodec.cpp.o.provides: CMakeFiles/blobTracker.dir/eventCodec.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/eventCodec.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/eventCodec.cpp.o.provides

CMakeFiles/blobTracker.dir/eventCodec.cpp.o.provides.build: CMakeFiles/blobTracker.dir/eventCodec.cpp.o

CMakeFiles/blobTracker.dir/main.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/main.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/main.cpp

CMakeFiles/blobTracker.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/main.cpp > CMakeFiles/blobTracker.dir/main.cpp.i

CMakeFiles/blobTracker.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/main.cpp -o CMakeFiles/blobTracker.dir/main.cpp.s

CMakeFiles/blobTracker.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/main.cpp.o.requires

CMakeFiles/blobTracker.dir/main.cpp.o.provides: CMakeFiles/blobTracker.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/main.cpp.o.provides

CMakeFiles/blobTracker.dir/main.cpp.o.provides.build: CMakeFiles/blobTracker.dir/main.cpp.o

CMakeFiles/blobTracker.dir/tracker_pool.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/tracker_pool.cpp.o: ../tracker_pool.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/tracker_pool.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/tracker_pool.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/tracker_pool.cpp

CMakeFiles/blobTracker.dir/tracker_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/tracker_pool.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/tracker_pool.cpp > CMakeFiles/blobTracker.dir/tracker_pool.cpp.i

CMakeFiles/blobTracker.dir/tracker_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/tracker_pool.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/tracker_pool.cpp -o CMakeFiles/blobTracker.dir/tracker_pool.cpp.s

CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.requires

CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.provides: CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.provides

CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.provides.build: CMakeFiles/blobTracker.dir/tracker_pool.cpp.o

CMakeFiles/blobTracker.dir/eventBottle.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/eventBottle.cpp.o: ../eventBottle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/eventBottle.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/eventBottle.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventBottle.cpp

CMakeFiles/blobTracker.dir/eventBottle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/eventBottle.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventBottle.cpp > CMakeFiles/blobTracker.dir/eventBottle.cpp.i

CMakeFiles/blobTracker.dir/eventBottle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/eventBottle.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/eventBottle.cpp -o CMakeFiles/blobTracker.dir/eventBottle.cpp.s

CMakeFiles/blobTracker.dir/eventBottle.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/eventBottle.cpp.o.requires

CMakeFiles/blobTracker.dir/eventBottle.cpp.o.provides: CMakeFiles/blobTracker.dir/eventBottle.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/eventBottle.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/eventBottle.cpp.o.provides

CMakeFiles/blobTracker.dir/eventBottle.cpp.o.provides.build: CMakeFiles/blobTracker.dir/eventBottle.cpp.o

CMakeFiles/blobTracker.dir/unmask.cpp.o: CMakeFiles/blobTracker.dir/flags.make
CMakeFiles/blobTracker.dir/unmask.cpp.o: ../unmask.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/blobTracker.dir/unmask.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/blobTracker.dir/unmask.cpp.o -c /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/unmask.cpp

CMakeFiles/blobTracker.dir/unmask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blobTracker.dir/unmask.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/unmask.cpp > CMakeFiles/blobTracker.dir/unmask.cpp.i

CMakeFiles/blobTracker.dir/unmask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blobTracker.dir/unmask.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/unmask.cpp -o CMakeFiles/blobTracker.dir/unmask.cpp.s

CMakeFiles/blobTracker.dir/unmask.cpp.o.requires:
.PHONY : CMakeFiles/blobTracker.dir/unmask.cpp.o.requires

CMakeFiles/blobTracker.dir/unmask.cpp.o.provides: CMakeFiles/blobTracker.dir/unmask.cpp.o.requires
	$(MAKE) -f CMakeFiles/blobTracker.dir/build.make CMakeFiles/blobTracker.dir/unmask.cpp.o.provides.build
.PHONY : CMakeFiles/blobTracker.dir/unmask.cpp.o.provides

CMakeFiles/blobTracker.dir/unmask.cpp.o.provides.build: CMakeFiles/blobTracker.dir/unmask.cpp.o

# Object files for target blobTracker
blobTracker_OBJECTS = \
"CMakeFiles/blobTracker.dir/blob_tracker.cpp.o" \
"CMakeFiles/blobTracker.dir/eventCodec.cpp.o" \
"CMakeFiles/blobTracker.dir/main.cpp.o" \
"CMakeFiles/blobTracker.dir/tracker_pool.cpp.o" \
"CMakeFiles/blobTracker.dir/eventBottle.cpp.o" \
"CMakeFiles/blobTracker.dir/unmask.cpp.o"

# External object files for target blobTracker
blobTracker_EXTERNAL_OBJECTS =

blobTracker: CMakeFiles/blobTracker.dir/blob_tracker.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/eventCodec.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/main.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/tracker_pool.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/eventBottle.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/unmask.cpp.o
blobTracker: CMakeFiles/blobTracker.dir/build.make
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_math.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_dev.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_name.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_init.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_math.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_dev.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_sig.so.2.3.62.1
blobTracker: /usr/local/lib/x86_64-linux-gnu/libYARP_OS.so.2.3.62.1
blobTracker: CMakeFiles/blobTracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable blobTracker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blobTracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blobTracker.dir/build: blobTracker
.PHONY : CMakeFiles/blobTracker.dir/build

CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/blob_tracker.cpp.o.requires
CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/eventCodec.cpp.o.requires
CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/main.cpp.o.requires
CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/tracker_pool.cpp.o.requires
CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/eventBottle.cpp.o.requires
CMakeFiles/blobTracker.dir/requires: CMakeFiles/blobTracker.dir/unmask.cpp.o.requires
.PHONY : CMakeFiles/blobTracker.dir/requires

CMakeFiles/blobTracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/blobTracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/blobTracker.dir/clean

CMakeFiles/blobTracker.dir/depend:
	cd /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build /home/icub/Himanshu_local/iCubFiles/blobTracker2/blobTracker/_build/CMakeFiles/blobTracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blobTracker.dir/depend

