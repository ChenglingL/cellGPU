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
include CMakeFiles/overlapAndcageRelativeSISF.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/overlapAndcageRelativeSISF.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/overlapAndcageRelativeSISF.out.dir/flags.make

CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o: CMakeFiles/overlapAndcageRelativeSISF.out.dir/flags.make
CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o: ../overlapAndcageRelativeSISF.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/overlapAndcageRelativeSISF.cpp

CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/overlapAndcageRelativeSISF.cpp > CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.i

CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/overlapAndcageRelativeSISF.cpp -o CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.s

# Object files for target overlapAndcageRelativeSISF.out
overlapAndcageRelativeSISF_out_OBJECTS = \
"CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o"

# External object files for target overlapAndcageRelativeSISF.out
overlapAndcageRelativeSISF_out_EXTERNAL_OBJECTS =

../executable/overlapAndcageRelativeSISF.out: CMakeFiles/overlapAndcageRelativeSISF.out.dir/overlapAndcageRelativeSISF.cpp.o
../executable/overlapAndcageRelativeSISF.out: CMakeFiles/overlapAndcageRelativeSISF.out.dir/build.make
../executable/overlapAndcageRelativeSISF.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/overlapAndcageRelativeSISF.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/overlapAndcageRelativeSISF.out: src/models/libmodel.a
../executable/overlapAndcageRelativeSISF.out: src/models/libmodelGPU.a
../executable/overlapAndcageRelativeSISF.out: src/updaters/libupdaters.a
../executable/overlapAndcageRelativeSISF.out: src/updaters/libupdatersGPU.a
../executable/overlapAndcageRelativeSISF.out: src/analysis/libanalysis.a
../executable/overlapAndcageRelativeSISF.out: src/databases/libdatabase.a
../executable/overlapAndcageRelativeSISF.out: src/simulation/libsimulation.a
../executable/overlapAndcageRelativeSISF.out: src/utility/libutility.a
../executable/overlapAndcageRelativeSISF.out: src/utility/libutilityGPU.a
../executable/overlapAndcageRelativeSISF.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/overlapAndcageRelativeSISF.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/overlapAndcageRelativeSISF.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../executable/overlapAndcageRelativeSISF.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../executable/overlapAndcageRelativeSISF.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../executable/overlapAndcageRelativeSISF.out: CMakeFiles/overlapAndcageRelativeSISF.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../executable/overlapAndcageRelativeSISF.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/overlapAndcageRelativeSISF.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/overlapAndcageRelativeSISF.out.dir/build: ../executable/overlapAndcageRelativeSISF.out

.PHONY : CMakeFiles/overlapAndcageRelativeSISF.out.dir/build

CMakeFiles/overlapAndcageRelativeSISF.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/overlapAndcageRelativeSISF.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/overlapAndcageRelativeSISF.out.dir/clean

CMakeFiles/overlapAndcageRelativeSISF.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/overlapAndcageRelativeSISF.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/overlapAndcageRelativeSISF.out.dir/depend

