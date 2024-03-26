# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /u/cli6/cellGPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /u/cli6/cellGPU/cmakeHelp

# Include any dependencies generated for this target.
include CMakeFiles/productionRunTest.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/productionRunTest.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/productionRunTest.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/productionRunTest.out.dir/flags.make

CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o: CMakeFiles/productionRunTest.out.dir/flags.make
CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o: ../glassyDynamicsProject/productionRunTest.cpp
CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o: CMakeFiles/productionRunTest.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o -MF CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o.d -o CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o -c /u/cli6/cellGPU/glassyDynamicsProject/productionRunTest.cpp

CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.i"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/cellGPU/glassyDynamicsProject/productionRunTest.cpp > CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.i

CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.s"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/cellGPU/glassyDynamicsProject/productionRunTest.cpp -o CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.s

# Object files for target productionRunTest.out
productionRunTest_out_OBJECTS = \
"CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o"

# External object files for target productionRunTest.out
productionRunTest_out_EXTERNAL_OBJECTS =

../glassyDynamicsProject/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/glassyDynamicsProject/productionRunTest.cpp.o
../glassyDynamicsProject/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/build.make
../glassyDynamicsProject/productionRunTest.out: /sw/spack/delta-2022-03/apps/cuda/11.6.1-gcc-11.2.0-vglutoe/lib64/libcudart_static.a
../glassyDynamicsProject/productionRunTest.out: /usr/lib64/librt.so
../glassyDynamicsProject/productionRunTest.out: src/models/libmodel.a
../glassyDynamicsProject/productionRunTest.out: src/models/libmodelGPU.a
../glassyDynamicsProject/productionRunTest.out: src/updaters/libupdaters.a
../glassyDynamicsProject/productionRunTest.out: src/updaters/libupdatersGPU.a
../glassyDynamicsProject/productionRunTest.out: src/analysis/libanalysis.a
../glassyDynamicsProject/productionRunTest.out: src/databases/libdatabase.a
../glassyDynamicsProject/productionRunTest.out: src/simulation/libsimulation.a
../glassyDynamicsProject/productionRunTest.out: src/utility/libutility.a
../glassyDynamicsProject/productionRunTest.out: src/utility/libutilityGPU.a
../glassyDynamicsProject/productionRunTest.out: /sw/spack/delta-2022-03/apps/cuda/11.6.1-gcc-11.2.0-vglutoe/lib64/libcudart_static.a
../glassyDynamicsProject/productionRunTest.out: /usr/lib64/librt.so
../glassyDynamicsProject/productionRunTest.out: /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/lib64/libgomp.so
../glassyDynamicsProject/productionRunTest.out: /lib64/libpthread.so
../glassyDynamicsProject/productionRunTest.out: CMakeFiles/productionRunTest.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/u/cli6/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../glassyDynamicsProject/productionRunTest.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/productionRunTest.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/productionRunTest.out.dir/build: ../glassyDynamicsProject/productionRunTest.out
.PHONY : CMakeFiles/productionRunTest.out.dir/build

CMakeFiles/productionRunTest.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/productionRunTest.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/productionRunTest.out.dir/clean

CMakeFiles/productionRunTest.out.dir/depend:
	cd /u/cli6/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/cli6/cellGPU /u/cli6/cellGPU /u/cli6/cellGPU/cmakeHelp /u/cli6/cellGPU/cmakeHelp /u/cli6/cellGPU/cmakeHelp/CMakeFiles/productionRunTest.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/productionRunTest.out.dir/depend

