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
CMAKE_SOURCE_DIR = /u/cli6/Cell_G/cellGPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /u/cli6/Cell_G/cellGPU/cmakeHelp

# Include any dependencies generated for this target.
include src/simulation/CMakeFiles/simulation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/simulation/CMakeFiles/simulation.dir/compiler_depend.make

# Include the progress variables for this target.
include src/simulation/CMakeFiles/simulation.dir/progress.make

# Include the compile flags for this target's objects.
include src/simulation/CMakeFiles/simulation.dir/flags.make

src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o: src/simulation/CMakeFiles/simulation.dir/flags.make
src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o: ../src/simulation/Simulation.cpp
src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o: src/simulation/CMakeFiles/simulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o -MF CMakeFiles/simulation.dir/Simulation.cpp.o.d -o CMakeFiles/simulation.dir/Simulation.cpp.o -c /u/cli6/Cell_G/cellGPU/src/simulation/Simulation.cpp

src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simulation.dir/Simulation.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/simulation/Simulation.cpp > CMakeFiles/simulation.dir/Simulation.cpp.i

src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simulation.dir/Simulation.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/simulation/Simulation.cpp -o CMakeFiles/simulation.dir/Simulation.cpp.s

# Object files for target simulation
simulation_OBJECTS = \
"CMakeFiles/simulation.dir/Simulation.cpp.o"

# External object files for target simulation
simulation_EXTERNAL_OBJECTS =

src/simulation/libsimulation.a: src/simulation/CMakeFiles/simulation.dir/Simulation.cpp.o
src/simulation/libsimulation.a: src/simulation/CMakeFiles/simulation.dir/build.make
src/simulation/libsimulation.a: src/simulation/CMakeFiles/simulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsimulation.a"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && $(CMAKE_COMMAND) -P CMakeFiles/simulation.dir/cmake_clean_target.cmake
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/simulation/CMakeFiles/simulation.dir/build: src/simulation/libsimulation.a
.PHONY : src/simulation/CMakeFiles/simulation.dir/build

src/simulation/CMakeFiles/simulation.dir/clean:
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation && $(CMAKE_COMMAND) -P CMakeFiles/simulation.dir/cmake_clean.cmake
.PHONY : src/simulation/CMakeFiles/simulation.dir/clean

src/simulation/CMakeFiles/simulation.dir/depend:
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/cli6/Cell_G/cellGPU /u/cli6/Cell_G/cellGPU/src/simulation /u/cli6/Cell_G/cellGPU/cmakeHelp /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation /u/cli6/Cell_G/cellGPU/cmakeHelp/src/simulation/CMakeFiles/simulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/simulation/CMakeFiles/simulation.dir/depend

