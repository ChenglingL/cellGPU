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
include CMakeFiles/SISFLongTime.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SISFLongTime.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SISFLongTime.out.dir/flags.make

CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o: CMakeFiles/SISFLongTime.out.dir/flags.make
CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o: ../localTest/SISFLongTime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFLongTime.cpp

CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFLongTime.cpp > CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.i

CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SISFLongTime.cpp -o CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.s

# Object files for target SISFLongTime.out
SISFLongTime_out_OBJECTS = \
"CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o"

# External object files for target SISFLongTime.out
SISFLongTime_out_EXTERNAL_OBJECTS =

../localTest/executable/SISFLongTime.out: CMakeFiles/SISFLongTime.out.dir/localTest/SISFLongTime.cpp.o
../localTest/executable/SISFLongTime.out: CMakeFiles/SISFLongTime.out.dir/build.make
../localTest/executable/SISFLongTime.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SISFLongTime.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SISFLongTime.out: src/models/libmodel.a
../localTest/executable/SISFLongTime.out: src/models/libmodelGPU.a
../localTest/executable/SISFLongTime.out: src/updaters/libupdaters.a
../localTest/executable/SISFLongTime.out: src/updaters/libupdatersGPU.a
../localTest/executable/SISFLongTime.out: src/analysis/libanalysis.a
../localTest/executable/SISFLongTime.out: src/databases/libdatabase.a
../localTest/executable/SISFLongTime.out: src/simulation/libsimulation.a
../localTest/executable/SISFLongTime.out: src/utility/libutility.a
../localTest/executable/SISFLongTime.out: src/utility/libutilityGPU.a
../localTest/executable/SISFLongTime.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SISFLongTime.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SISFLongTime.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/SISFLongTime.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/SISFLongTime.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/SISFLongTime.out: CMakeFiles/SISFLongTime.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/SISFLongTime.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SISFLongTime.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SISFLongTime.out.dir/build: ../localTest/executable/SISFLongTime.out

.PHONY : CMakeFiles/SISFLongTime.out.dir/build

CMakeFiles/SISFLongTime.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SISFLongTime.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SISFLongTime.out.dir/clean

CMakeFiles/SISFLongTime.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/SISFLongTime.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SISFLongTime.out.dir/depend

