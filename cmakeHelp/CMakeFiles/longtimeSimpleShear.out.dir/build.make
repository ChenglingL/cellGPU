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
include CMakeFiles/longtimeSimpleShear.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/longtimeSimpleShear.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/longtimeSimpleShear.out.dir/flags.make

CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o: CMakeFiles/longtimeSimpleShear.out.dir/flags.make
CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o: ../localTest/longtimeSimpleShear.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/longtimeSimpleShear.cpp

CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/longtimeSimpleShear.cpp > CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.i

CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/longtimeSimpleShear.cpp -o CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.s

# Object files for target longtimeSimpleShear.out
longtimeSimpleShear_out_OBJECTS = \
"CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o"

# External object files for target longtimeSimpleShear.out
longtimeSimpleShear_out_EXTERNAL_OBJECTS =

../localTest/executable/longtimeSimpleShear.out: CMakeFiles/longtimeSimpleShear.out.dir/localTest/longtimeSimpleShear.cpp.o
../localTest/executable/longtimeSimpleShear.out: CMakeFiles/longtimeSimpleShear.out.dir/build.make
../localTest/executable/longtimeSimpleShear.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/longtimeSimpleShear.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/longtimeSimpleShear.out: src/models/libmodel.a
../localTest/executable/longtimeSimpleShear.out: src/models/libmodelGPU.a
../localTest/executable/longtimeSimpleShear.out: src/updaters/libupdaters.a
../localTest/executable/longtimeSimpleShear.out: src/updaters/libupdatersGPU.a
../localTest/executable/longtimeSimpleShear.out: src/analysis/libanalysis.a
../localTest/executable/longtimeSimpleShear.out: src/databases/libdatabase.a
../localTest/executable/longtimeSimpleShear.out: src/simulation/libsimulation.a
../localTest/executable/longtimeSimpleShear.out: src/utility/libutility.a
../localTest/executable/longtimeSimpleShear.out: src/utility/libutilityGPU.a
../localTest/executable/longtimeSimpleShear.out: /usr/local/cuda-12.2/lib64/libcudart_static.a
../localTest/executable/longtimeSimpleShear.out: /usr/lib/x86_64-linux-gnu/librt.so
../localTest/executable/longtimeSimpleShear.out: /usr/lib/x86_64-linux-gnu/libgmpxx.so
../localTest/executable/longtimeSimpleShear.out: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
../localTest/executable/longtimeSimpleShear.out: /usr/lib/x86_64-linux-gnu/libpthread.so
../localTest/executable/longtimeSimpleShear.out: CMakeFiles/longtimeSimpleShear.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../localTest/executable/longtimeSimpleShear.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/longtimeSimpleShear.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/longtimeSimpleShear.out.dir/build: ../localTest/executable/longtimeSimpleShear.out

.PHONY : CMakeFiles/longtimeSimpleShear.out.dir/build

CMakeFiles/longtimeSimpleShear.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/longtimeSimpleShear.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/longtimeSimpleShear.out.dir/clean

CMakeFiles/longtimeSimpleShear.out.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles/longtimeSimpleShear.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/longtimeSimpleShear.out.dir/depend

