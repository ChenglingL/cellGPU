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
include CMakeFiles/AreaPriStat.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AreaPriStat.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AreaPriStat.out.dir/flags.make

CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o: CMakeFiles/AreaPriStat.out.dir/flags.make
CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o: ../AreaPriStat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/AreaPriStat.cpp

CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/AreaPriStat.cpp > CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.i

CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/AreaPriStat.cpp -o CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.s

# Object files for target AreaPriStat.out
AreaPriStat_out_OBJECTS = \
"CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o"

# External object files for target AreaPriStat.out
AreaPriStat_out_EXTERNAL_OBJECTS =

../executable/AreaPriStat.out: CMakeFiles/AreaPriStat.out.dir/AreaPriStat.cpp.o
../executable/AreaPriStat.out: CMakeFiles/AreaPriStat.out.dir/build.make
../executable/AreaPriStat.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/AreaPriStat.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/AreaPriStat.out: src/models/libmodel.a
../executable/AreaPriStat.out: src/models/libmodelGPU.a
../executable/AreaPriStat.out: src/updaters/libupdaters.a
../executable/AreaPriStat.out: src/updaters/libupdatersGPU.a
../executable/AreaPriStat.out: src/analysis/libanalysis.a
../executable/AreaPriStat.out: src/databases/libdatabase.a
../executable/AreaPriStat.out: src/simulation/libsimulation.a
../executable/AreaPriStat.out: src/utility/libutility.a
../executable/AreaPriStat.out: src/utility/libutilityGPU.a
../executable/AreaPriStat.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/AreaPriStat.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/AreaPriStat.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../executable/AreaPriStat.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../executable/AreaPriStat.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../executable/AreaPriStat.out: CMakeFiles/AreaPriStat.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../executable/AreaPriStat.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AreaPriStat.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AreaPriStat.out.dir/build: ../executable/AreaPriStat.out

.PHONY : CMakeFiles/AreaPriStat.out.dir/build

CMakeFiles/AreaPriStat.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AreaPriStat.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AreaPriStat.out.dir/clean

CMakeFiles/AreaPriStat.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/AreaPriStat.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AreaPriStat.out.dir/depend

