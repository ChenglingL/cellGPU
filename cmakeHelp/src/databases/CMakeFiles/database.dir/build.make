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
include src/databases/CMakeFiles/database.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/databases/CMakeFiles/database.dir/compiler_depend.make

# Include the progress variables for this target.
include src/databases/CMakeFiles/database.dir/progress.make

# Include the compile flags for this target's objects.
include src/databases/CMakeFiles/database.dir/flags.make

src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o: ../src/databases/logEquilibrationStateWriter.cpp
src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o -MF CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o.d -o CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/logEquilibrationStateWriter.cpp

src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/logEquilibrationStateWriter.cpp > CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.i

src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/logEquilibrationStateWriter.cpp -o CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.s

src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o: ../src/databases/DatabaseNetCDF.cpp
src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o -MF CMakeFiles/database.dir/DatabaseNetCDF.cpp.o.d -o CMakeFiles/database.dir/DatabaseNetCDF.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDF.cpp

src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/DatabaseNetCDF.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDF.cpp > CMakeFiles/database.dir/DatabaseNetCDF.cpp.i

src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/DatabaseNetCDF.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDF.cpp -o CMakeFiles/database.dir/DatabaseNetCDF.cpp.s

src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o: ../src/databases/DatabaseNetCDFAVM.cpp
src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o -MF CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o.d -o CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFAVM.cpp

src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFAVM.cpp > CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.i

src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFAVM.cpp -o CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.s

src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o: ../src/databases/DatabaseNetCDFSPV.cpp
src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o -MF CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o.d -o CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFSPV.cpp

src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFSPV.cpp > CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.i

src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/DatabaseNetCDFSPV.cpp -o CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.s

src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o: ../src/databases/DatabaseTextVoronoi.cpp
src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o -MF CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o.d -o CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/DatabaseTextVoronoi.cpp

src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/DatabaseTextVoronoi.cpp > CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.i

src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/DatabaseTextVoronoi.cpp -o CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.s

src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o: ../src/databases/vectorValueDatabase.cpp
src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o -MF CMakeFiles/database.dir/vectorValueDatabase.cpp.o.d -o CMakeFiles/database.dir/vectorValueDatabase.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/vectorValueDatabase.cpp

src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/vectorValueDatabase.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/vectorValueDatabase.cpp > CMakeFiles/database.dir/vectorValueDatabase.cpp.i

src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/vectorValueDatabase.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/vectorValueDatabase.cpp -o CMakeFiles/database.dir/vectorValueDatabase.cpp.s

src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o: src/databases/CMakeFiles/database.dir/flags.make
src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o: ../src/databases/nvtModelDatabase.cpp
src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o: src/databases/CMakeFiles/database.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o -MF CMakeFiles/database.dir/nvtModelDatabase.cpp.o.d -o CMakeFiles/database.dir/nvtModelDatabase.cpp.o -c /u/cli6/Cell_G/cellGPU/src/databases/nvtModelDatabase.cpp

src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/database.dir/nvtModelDatabase.cpp.i"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /u/cli6/Cell_G/cellGPU/src/databases/nvtModelDatabase.cpp > CMakeFiles/database.dir/nvtModelDatabase.cpp.i

src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/database.dir/nvtModelDatabase.cpp.s"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && /sw/spack/delta-2022-03/apps/gcc/11.2.0-gcc-8.4.1-fxgnsyr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /u/cli6/Cell_G/cellGPU/src/databases/nvtModelDatabase.cpp -o CMakeFiles/database.dir/nvtModelDatabase.cpp.s

# Object files for target database
database_OBJECTS = \
"CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o" \
"CMakeFiles/database.dir/DatabaseNetCDF.cpp.o" \
"CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o" \
"CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o" \
"CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o" \
"CMakeFiles/database.dir/vectorValueDatabase.cpp.o" \
"CMakeFiles/database.dir/nvtModelDatabase.cpp.o"

# External object files for target database
database_EXTERNAL_OBJECTS =

src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/logEquilibrationStateWriter.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/DatabaseNetCDF.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/DatabaseNetCDFAVM.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/DatabaseNetCDFSPV.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/DatabaseTextVoronoi.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/vectorValueDatabase.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/nvtModelDatabase.cpp.o
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/build.make
src/databases/libdatabase.a: src/databases/CMakeFiles/database.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/u/cli6/Cell_G/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libdatabase.a"
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && $(CMAKE_COMMAND) -P CMakeFiles/database.dir/cmake_clean_target.cmake
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/database.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/databases/CMakeFiles/database.dir/build: src/databases/libdatabase.a
.PHONY : src/databases/CMakeFiles/database.dir/build

src/databases/CMakeFiles/database.dir/clean:
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases && $(CMAKE_COMMAND) -P CMakeFiles/database.dir/cmake_clean.cmake
.PHONY : src/databases/CMakeFiles/database.dir/clean

src/databases/CMakeFiles/database.dir/depend:
	cd /u/cli6/Cell_G/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/cli6/Cell_G/cellGPU /u/cli6/Cell_G/cellGPU/src/databases /u/cli6/Cell_G/cellGPU/cmakeHelp /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases /u/cli6/Cell_G/cellGPU/cmakeHelp/src/databases/CMakeFiles/database.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/databases/CMakeFiles/database.dir/depend

