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
include CMakeFiles/productionRunTest.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/productionRunTest.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/productionRunTest.out.dir/flags.make

CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o: CMakeFiles/productionRunTest.out.dir/flags.make
CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o: ../localTest/productionRunTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/productionRunTest.cpp

CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/productionRunTest.cpp > CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.i

CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/productionRunTest.cpp -o CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.s

# Object files for target productionRunTest.out
productionRunTest_out_OBJECTS = \
"CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o"

# External object files for target productionRunTest.out
productionRunTest_out_EXTERNAL_OBJECTS =

../localTest/executable/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/localTest/productionRunTest.cpp.o
../localTest/executable/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/build.make
../localTest/executable/productionRunTest.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/productionRunTest.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/productionRunTest.out: src/models/libmodel.a
../localTest/executable/productionRunTest.out: src/models/libmodelGPU.a
../localTest/executable/productionRunTest.out: src/updaters/libupdaters.a
../localTest/executable/productionRunTest.out: src/updaters/libupdatersGPU.a
../localTest/executable/productionRunTest.out: src/analysis/libanalysis.a
../localTest/executable/productionRunTest.out: src/databases/libdatabase.a
../localTest/executable/productionRunTest.out: src/simulation/libsimulation.a
../localTest/executable/productionRunTest.out: src/utility/libutility.a
../localTest/executable/productionRunTest.out: src/utility/libutilityGPU.a
../localTest/executable/productionRunTest.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/productionRunTest.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/productionRunTest.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/productionRunTest.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/productionRunTest.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/productionRunTest.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/productionRunTest.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/productionRunTest.out.dir/build: ../localTest/executable/productionRunTest.out

.PHONY : CMakeFiles/productionRunTest.out.dir/build

CMakeFiles/productionRunTest.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/productionRunTest.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/productionRunTest.out.dir/clean

CMakeFiles/productionRunTest.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/productionRunTest.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/productionRunTest.out.dir/depend

