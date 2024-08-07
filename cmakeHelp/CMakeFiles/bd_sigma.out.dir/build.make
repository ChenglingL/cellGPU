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
include CMakeFiles/bd_sigma.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bd_sigma.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bd_sigma.out.dir/flags.make

CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o: CMakeFiles/bd_sigma.out.dir/flags.make
CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o: ../bd_sigma.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd_sigma.cpp

CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd_sigma.cpp > CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.i

CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/bd_sigma.cpp -o CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.s

# Object files for target bd_sigma.out
bd_sigma_out_OBJECTS = \
"CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o"

# External object files for target bd_sigma.out
bd_sigma_out_EXTERNAL_OBJECTS =

bd_sigma.out: CMakeFiles/bd_sigma.out.dir/bd_sigma.cpp.o
bd_sigma.out: CMakeFiles/bd_sigma.out.dir/build.make
bd_sigma.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
bd_sigma.out: /usr/lib/x86_64-linux-gnu/librt.so
bd_sigma.out: src/models/libmodel.a
bd_sigma.out: src/models/libmodelGPU.a
bd_sigma.out: src/updaters/libupdaters.a
bd_sigma.out: src/updaters/libupdatersGPU.a
bd_sigma.out: src/analysis/libanalysis.a
bd_sigma.out: src/databases/libdatabase.a
bd_sigma.out: src/simulation/libsimulation.a
bd_sigma.out: src/utility/libutility.a
bd_sigma.out: src/utility/libutilityGPU.a
bd_sigma.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
bd_sigma.out: /usr/lib/x86_64-linux-gnu/librt.so
bd_sigma.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
bd_sigma.out: /usr/lib/x86_64-linux-gnu/libpthread.so
bd_sigma.out: CMakeFiles/bd_sigma.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bd_sigma.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bd_sigma.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bd_sigma.out.dir/build: bd_sigma.out

.PHONY : CMakeFiles/bd_sigma.out.dir/build

CMakeFiles/bd_sigma.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bd_sigma.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bd_sigma.out.dir/clean

CMakeFiles/bd_sigma.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/bd_sigma.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bd_sigma.out.dir/depend

