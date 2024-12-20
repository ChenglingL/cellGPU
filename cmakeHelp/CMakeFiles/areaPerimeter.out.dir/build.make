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
include CMakeFiles/areaPerimeter.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/areaPerimeter.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/areaPerimeter.out.dir/flags.make

CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o: CMakeFiles/areaPerimeter.out.dir/flags.make
CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o: ../localTest/areaPerimeter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/areaPerimeter.cpp

CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/areaPerimeter.cpp > CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.i

CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/areaPerimeter.cpp -o CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.s

# Object files for target areaPerimeter.out
areaPerimeter_out_OBJECTS = \
"CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o"

# External object files for target areaPerimeter.out
areaPerimeter_out_EXTERNAL_OBJECTS =

../localTest/executable/areaPerimeter.out: CMakeFiles/areaPerimeter.out.dir/localTest/areaPerimeter.cpp.o
../localTest/executable/areaPerimeter.out: CMakeFiles/areaPerimeter.out.dir/build.make
../localTest/executable/areaPerimeter.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/areaPerimeter.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/areaPerimeter.out: src/models/libmodel.a
../localTest/executable/areaPerimeter.out: src/models/libmodelGPU.a
../localTest/executable/areaPerimeter.out: src/updaters/libupdaters.a
../localTest/executable/areaPerimeter.out: src/updaters/libupdatersGPU.a
../localTest/executable/areaPerimeter.out: src/analysis/libanalysis.a
../localTest/executable/areaPerimeter.out: src/databases/libdatabase.a
../localTest/executable/areaPerimeter.out: src/simulation/libsimulation.a
../localTest/executable/areaPerimeter.out: src/utility/libutility.a
../localTest/executable/areaPerimeter.out: src/utility/libutilityGPU.a
../localTest/executable/areaPerimeter.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/areaPerimeter.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/areaPerimeter.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/areaPerimeter.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/areaPerimeter.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/areaPerimeter.out: CMakeFiles/areaPerimeter.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/areaPerimeter.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/areaPerimeter.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/areaPerimeter.out.dir/build: ../localTest/executable/areaPerimeter.out

.PHONY : CMakeFiles/areaPerimeter.out.dir/build

CMakeFiles/areaPerimeter.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/areaPerimeter.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/areaPerimeter.out.dir/clean

CMakeFiles/areaPerimeter.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/areaPerimeter.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/areaPerimeter.out.dir/depend

