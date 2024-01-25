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
include CMakeFiles/voronoiGlassyDynamics.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/voronoiGlassyDynamics.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/voronoiGlassyDynamics.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voronoiGlassyDynamics.out.dir/flags.make

CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o: CMakeFiles/voronoiGlassyDynamics.out.dir/flags.make
CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o: ../glassyDnamicsProject/voronoiGlassyDynamics.cpp
CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o: CMakeFiles/voronoiGlassyDynamics.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o -MF CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o.d -o CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o -c /u/cli6/cellGPU/glassyDnamicsProject/voronoiGlassyDynamics.cpp

CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.i"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/cellGPU/glassyDnamicsProject/voronoiGlassyDynamics.cpp > CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.i

CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.s"
	/sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/cellGPU/glassyDnamicsProject/voronoiGlassyDynamics.cpp -o CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.s

# Object files for target voronoiGlassyDynamics.out
voronoiGlassyDynamics_out_OBJECTS = \
"CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o"

# External object files for target voronoiGlassyDynamics.out
voronoiGlassyDynamics_out_EXTERNAL_OBJECTS =

../glassyDnamicsProject/voronoiGlassyDynamics.out: CMakeFiles/voronoiGlassyDynamics.out.dir/glassyDnamicsProject/voronoiGlassyDynamics.cpp.o
../glassyDnamicsProject/voronoiGlassyDynamics.out: CMakeFiles/voronoiGlassyDynamics.out.dir/build.make
../glassyDnamicsProject/voronoiGlassyDynamics.out: /sw/spack/delta-2022-03/apps/cuda/11.6.1-gcc-11.2.0-vglutoe/lib64/libcudart_static.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: /usr/lib64/librt.so
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/models/libmodel.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/models/libmodelGPU.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/updaters/libupdaters.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/updaters/libupdatersGPU.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/analysis/libanalysis.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/databases/libdatabase.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/simulation/libsimulation.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/utility/libutility.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: src/utility/libutilityGPU.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: /sw/spack/delta-2022-03/apps/cuda/11.6.1-gcc-11.2.0-vglutoe/lib64/libcudart_static.a
../glassyDnamicsProject/voronoiGlassyDynamics.out: /usr/lib64/librt.so
../glassyDnamicsProject/voronoiGlassyDynamics.out: /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/lib64/libgomp.so
../glassyDnamicsProject/voronoiGlassyDynamics.out: /lib64/libpthread.so
../glassyDnamicsProject/voronoiGlassyDynamics.out: CMakeFiles/voronoiGlassyDynamics.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/u/cli6/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../glassyDnamicsProject/voronoiGlassyDynamics.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voronoiGlassyDynamics.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voronoiGlassyDynamics.out.dir/build: ../glassyDnamicsProject/voronoiGlassyDynamics.out
.PHONY : CMakeFiles/voronoiGlassyDynamics.out.dir/build

CMakeFiles/voronoiGlassyDynamics.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voronoiGlassyDynamics.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voronoiGlassyDynamics.out.dir/clean

CMakeFiles/voronoiGlassyDynamics.out.dir/depend:
	cd /u/cli6/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/cli6/cellGPU /u/cli6/cellGPU /u/cli6/cellGPU/cmakeHelp /u/cli6/cellGPU/cmakeHelp /u/cli6/cellGPU/cmakeHelp/CMakeFiles/voronoiGlassyDynamics.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voronoiGlassyDynamics.out.dir/depend
