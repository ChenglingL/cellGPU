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
include CMakeFiles/SISFShortTime.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SISFShortTime.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SISFShortTime.out.dir/flags.make

CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o: CMakeFiles/SISFShortTime.out.dir/flags.make
CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o: ../localTest/SISFShortTime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFShortTime.cpp

CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFShortTime.cpp > CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.i

CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFShortTime.cpp -o CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.s

# Object files for target SISFShortTime.out
SISFShortTime_out_OBJECTS = \
"CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o"

# External object files for target SISFShortTime.out
SISFShortTime_out_EXTERNAL_OBJECTS =

../localTest/executable/SISFShortTime.out: CMakeFiles/SISFShortTime.out.dir/localTest/SISFShortTime.cpp.o
../localTest/executable/SISFShortTime.out: CMakeFiles/SISFShortTime.out.dir/build.make
../localTest/executable/SISFShortTime.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SISFShortTime.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SISFShortTime.out: src/models/libmodel.a
../localTest/executable/SISFShortTime.out: src/models/libmodelGPU.a
../localTest/executable/SISFShortTime.out: src/updaters/libupdaters.a
../localTest/executable/SISFShortTime.out: src/updaters/libupdatersGPU.a
../localTest/executable/SISFShortTime.out: src/analysis/libanalysis.a
../localTest/executable/SISFShortTime.out: src/databases/libdatabase.a
../localTest/executable/SISFShortTime.out: src/simulation/libsimulation.a
../localTest/executable/SISFShortTime.out: src/utility/libutility.a
../localTest/executable/SISFShortTime.out: src/utility/libutilityGPU.a
../localTest/executable/SISFShortTime.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SISFShortTime.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SISFShortTime.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/SISFShortTime.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/SISFShortTime.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/SISFShortTime.out: CMakeFiles/SISFShortTime.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/SISFShortTime.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SISFShortTime.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SISFShortTime.out.dir/build: ../localTest/executable/SISFShortTime.out

.PHONY : CMakeFiles/SISFShortTime.out.dir/build

CMakeFiles/SISFShortTime.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SISFShortTime.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SISFShortTime.out.dir/clean

CMakeFiles/SISFShortTime.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/SISFShortTime.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SISFShortTime.out.dir/depend

