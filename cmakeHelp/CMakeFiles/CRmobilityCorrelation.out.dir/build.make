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
include CMakeFiles/CRmobilityCorrelation.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CRmobilityCorrelation.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CRmobilityCorrelation.out.dir/flags.make

CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o: CMakeFiles/CRmobilityCorrelation.out.dir/flags.make
CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o: ../localTest/CRmobilityCorrelation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/CRmobilityCorrelation.cpp

CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/CRmobilityCorrelation.cpp > CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.i

CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/CRmobilityCorrelation.cpp -o CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.s

# Object files for target CRmobilityCorrelation.out
CRmobilityCorrelation_out_OBJECTS = \
"CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o"

# External object files for target CRmobilityCorrelation.out
CRmobilityCorrelation_out_EXTERNAL_OBJECTS =

../localTest/executable/CRmobilityCorrelation.out: CMakeFiles/CRmobilityCorrelation.out.dir/localTest/CRmobilityCorrelation.cpp.o
../localTest/executable/CRmobilityCorrelation.out: CMakeFiles/CRmobilityCorrelation.out.dir/build.make
../localTest/executable/CRmobilityCorrelation.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/CRmobilityCorrelation.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/CRmobilityCorrelation.out: src/models/libmodel.a
../localTest/executable/CRmobilityCorrelation.out: src/models/libmodelGPU.a
../localTest/executable/CRmobilityCorrelation.out: src/updaters/libupdaters.a
../localTest/executable/CRmobilityCorrelation.out: src/updaters/libupdatersGPU.a
../localTest/executable/CRmobilityCorrelation.out: src/analysis/libanalysis.a
../localTest/executable/CRmobilityCorrelation.out: src/databases/libdatabase.a
../localTest/executable/CRmobilityCorrelation.out: src/simulation/libsimulation.a
../localTest/executable/CRmobilityCorrelation.out: src/utility/libutility.a
../localTest/executable/CRmobilityCorrelation.out: src/utility/libutilityGPU.a
../localTest/executable/CRmobilityCorrelation.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/CRmobilityCorrelation.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/CRmobilityCorrelation.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/CRmobilityCorrelation.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/CRmobilityCorrelation.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/CRmobilityCorrelation.out: CMakeFiles/CRmobilityCorrelation.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/CRmobilityCorrelation.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CRmobilityCorrelation.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CRmobilityCorrelation.out.dir/build: ../localTest/executable/CRmobilityCorrelation.out

.PHONY : CMakeFiles/CRmobilityCorrelation.out.dir/build

CMakeFiles/CRmobilityCorrelation.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CRmobilityCorrelation.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CRmobilityCorrelation.out.dir/clean

CMakeFiles/CRmobilityCorrelation.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/CRmobilityCorrelation.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CRmobilityCorrelation.out.dir/depend

