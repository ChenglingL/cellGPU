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
include CMakeFiles/spv.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/spv.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/spv.out.dir/flags.make

CMakeFiles/spv.out.dir/localTest/spv.cpp.o: CMakeFiles/spv.out.dir/flags.make
CMakeFiles/spv.out.dir/localTest/spv.cpp.o: ../localTest/spv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/spv.out.dir/localTest/spv.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/spv.out.dir/localTest/spv.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/spv.cpp

CMakeFiles/spv.out.dir/localTest/spv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spv.out.dir/localTest/spv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/spv.cpp > CMakeFiles/spv.out.dir/localTest/spv.cpp.i

CMakeFiles/spv.out.dir/localTest/spv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spv.out.dir/localTest/spv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/spv.cpp -o CMakeFiles/spv.out.dir/localTest/spv.cpp.s

# Object files for target spv.out
spv_out_OBJECTS = \
"CMakeFiles/spv.out.dir/localTest/spv.cpp.o"

# External object files for target spv.out
spv_out_EXTERNAL_OBJECTS =

../localTest/executable/spv.out: CMakeFiles/spv.out.dir/localTest/spv.cpp.o
../localTest/executable/spv.out: CMakeFiles/spv.out.dir/build.make
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/libcudart_static.a
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/spv.out: src/models/libmodel.a
../localTest/executable/spv.out: src/models/libmodelGPU.a
../localTest/executable/spv.out: src/updaters/libupdaters.a
../localTest/executable/spv.out: src/updaters/libupdatersGPU.a
../localTest/executable/spv.out: src/analysis/libanalysis.a
../localTest/executable/spv.out: src/databases/libdatabase.a
../localTest/executable/spv.out: src/simulation/libsimulation.a
../localTest/executable/spv.out: src/utility/libutility.a
../localTest/executable/spv.out: src/utility/libutilityGPU.a
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/libcudart_static.a
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/spv.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/spv.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/spv.out: CMakeFiles/spv.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/spv.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spv.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/spv.out.dir/build: ../localTest/executable/spv.out

.PHONY : CMakeFiles/spv.out.dir/build

CMakeFiles/spv.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/spv.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/spv.out.dir/clean

CMakeFiles/spv.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/spv.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/spv.out.dir/depend

