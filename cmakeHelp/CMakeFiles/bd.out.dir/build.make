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
include CMakeFiles/bd.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bd.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bd.out.dir/flags.make

CMakeFiles/bd.out.dir/bd.cpp.o: CMakeFiles/bd.out.dir/flags.make
CMakeFiles/bd.out.dir/bd.cpp.o: ../bd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bd.out.dir/bd.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bd.out.dir/bd.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd.cpp

CMakeFiles/bd.out.dir/bd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bd.out.dir/bd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd.cpp > CMakeFiles/bd.out.dir/bd.cpp.i

CMakeFiles/bd.out.dir/bd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bd.out.dir/bd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd.cpp -o CMakeFiles/bd.out.dir/bd.cpp.s

# Object files for target bd.out
bd_out_OBJECTS = \
"CMakeFiles/bd.out.dir/bd.cpp.o"

# External object files for target bd.out
bd_out_EXTERNAL_OBJECTS =

../executable/bd.out: CMakeFiles/bd.out.dir/bd.cpp.o
../executable/bd.out: CMakeFiles/bd.out.dir/build.make
../executable/bd.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/bd.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/bd.out: src/models/libmodel.a
../executable/bd.out: src/models/libmodelGPU.a
../executable/bd.out: src/updaters/libupdaters.a
../executable/bd.out: src/updaters/libupdatersGPU.a
../executable/bd.out: src/analysis/libanalysis.a
../executable/bd.out: src/databases/libdatabase.a
../executable/bd.out: src/simulation/libsimulation.a
../executable/bd.out: src/utility/libutility.a
../executable/bd.out: src/utility/libutilityGPU.a
../executable/bd.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../executable/bd.out: /usr/lib/x86_64-linux-gnu/librt.so
../executable/bd.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../executable/bd.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../executable/bd.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../executable/bd.out: CMakeFiles/bd.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../executable/bd.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bd.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bd.out.dir/build: ../executable/bd.out

.PHONY : CMakeFiles/bd.out.dir/build

CMakeFiles/bd.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bd.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bd.out.dir/clean

CMakeFiles/bd.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/bd.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bd.out.dir/depend

