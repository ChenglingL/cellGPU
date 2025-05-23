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
include CMakeFiles/SimpleShearSystemSize.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SimpleShearSystemSize.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SimpleShearSystemSize.out.dir/flags.make

CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o: CMakeFiles/SimpleShearSystemSize.out.dir/flags.make
CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o: ../localTest/SimpleShearSystemSize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SimpleShearSystemSize.cpp

CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SimpleShearSystemSize.cpp > CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.i

CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/SimpleShearSystemSize.cpp -o CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.s

# Object files for target SimpleShearSystemSize.out
SimpleShearSystemSize_out_OBJECTS = \
"CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o"

# External object files for target SimpleShearSystemSize.out
SimpleShearSystemSize_out_EXTERNAL_OBJECTS =

../localTest/executable/SimpleShearSystemSize.out: CMakeFiles/SimpleShearSystemSize.out.dir/localTest/SimpleShearSystemSize.cpp.o
../localTest/executable/SimpleShearSystemSize.out: CMakeFiles/SimpleShearSystemSize.out.dir/build.make
../localTest/executable/SimpleShearSystemSize.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SimpleShearSystemSize.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SimpleShearSystemSize.out: src/models/libmodel.a
../localTest/executable/SimpleShearSystemSize.out: src/models/libmodelGPU.a
../localTest/executable/SimpleShearSystemSize.out: src/updaters/libupdaters.a
../localTest/executable/SimpleShearSystemSize.out: src/updaters/libupdatersGPU.a
../localTest/executable/SimpleShearSystemSize.out: src/analysis/libanalysis.a
../localTest/executable/SimpleShearSystemSize.out: src/databases/libdatabase.a
../localTest/executable/SimpleShearSystemSize.out: src/simulation/libsimulation.a
../localTest/executable/SimpleShearSystemSize.out: src/utility/libutility.a
../localTest/executable/SimpleShearSystemSize.out: src/utility/libutilityGPU.a
../localTest/executable/SimpleShearSystemSize.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/SimpleShearSystemSize.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/SimpleShearSystemSize.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/SimpleShearSystemSize.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/SimpleShearSystemSize.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/SimpleShearSystemSize.out: CMakeFiles/SimpleShearSystemSize.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/SimpleShearSystemSize.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SimpleShearSystemSize.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SimpleShearSystemSize.out.dir/build: ../localTest/executable/SimpleShearSystemSize.out

.PHONY : CMakeFiles/SimpleShearSystemSize.out.dir/build

CMakeFiles/SimpleShearSystemSize.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SimpleShearSystemSize.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SimpleShearSystemSize.out.dir/clean

CMakeFiles/SimpleShearSystemSize.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/SimpleShearSystemSize.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SimpleShearSystemSize.out.dir/depend

