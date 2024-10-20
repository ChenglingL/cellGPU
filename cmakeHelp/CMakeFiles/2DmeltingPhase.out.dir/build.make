# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp

# Include any dependencies generated for this target.
include CMakeFiles/2DmeltingPhase.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2DmeltingPhase.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2DmeltingPhase.out.dir/flags.make

CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o: CMakeFiles/2DmeltingPhase.out.dir/flags.make
CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o: ../localTest/2DmeltingPhase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/2DmeltingPhase.cpp

CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/2DmeltingPhase.cpp > CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.i

CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/2DmeltingPhase.cpp -o CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.s

# Object files for target 2DmeltingPhase.out
2DmeltingPhase_out_OBJECTS = \
"CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o"

# External object files for target 2DmeltingPhase.out
2DmeltingPhase_out_EXTERNAL_OBJECTS =

../localTest/executable/2DmeltingPhase.out: CMakeFiles/2DmeltingPhase.out.dir/localTest/2DmeltingPhase.cpp.o
../localTest/executable/2DmeltingPhase.out: CMakeFiles/2DmeltingPhase.out.dir/build.make
../localTest/executable/2DmeltingPhase.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/2DmeltingPhase.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/2DmeltingPhase.out: src/models/libmodel.a
../localTest/executable/2DmeltingPhase.out: src/models/libmodelGPU.a
../localTest/executable/2DmeltingPhase.out: src/updaters/libupdaters.a
../localTest/executable/2DmeltingPhase.out: src/updaters/libupdatersGPU.a
../localTest/executable/2DmeltingPhase.out: src/analysis/libanalysis.a
../localTest/executable/2DmeltingPhase.out: src/databases/libdatabase.a
../localTest/executable/2DmeltingPhase.out: src/simulation/libsimulation.a
../localTest/executable/2DmeltingPhase.out: src/utility/libutility.a
../localTest/executable/2DmeltingPhase.out: src/utility/libutilityGPU.a
../localTest/executable/2DmeltingPhase.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/2DmeltingPhase.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/2DmeltingPhase.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/2DmeltingPhase.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/2DmeltingPhase.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/2DmeltingPhase.out: CMakeFiles/2DmeltingPhase.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/2DmeltingPhase.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2DmeltingPhase.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2DmeltingPhase.out.dir/build: ../localTest/executable/2DmeltingPhase.out

.PHONY : CMakeFiles/2DmeltingPhase.out.dir/build

CMakeFiles/2DmeltingPhase.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2DmeltingPhase.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2DmeltingPhase.out.dir/clean

CMakeFiles/2DmeltingPhase.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/2DmeltingPhase.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2DmeltingPhase.out.dir/depend

