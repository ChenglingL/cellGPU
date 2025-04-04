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
include src/analysis/CMakeFiles/analysis.dir/depend.make

# Include the progress variables for this target.
include src/analysis/CMakeFiles/analysis.dir/progress.make

# Include the compile flags for this target's objects.
include src/analysis/CMakeFiles/analysis.dir/flags.make

src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.o: src/analysis/CMakeFiles/analysis.dir/flags.make
src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.o: ../src/analysis/autocorrelator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.o"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/analysis.dir/autocorrelator.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelator.cpp

src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/analysis.dir/autocorrelator.cpp.i"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelator.cpp > CMakeFiles/analysis.dir/autocorrelator.cpp.i

src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/analysis.dir/autocorrelator.cpp.s"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelator.cpp -o CMakeFiles/analysis.dir/autocorrelator.cpp.s

src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o: src/analysis/CMakeFiles/analysis.dir/flags.make
src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o: ../src/analysis/autocorrelatorVector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelatorVector.cpp

src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/analysis.dir/autocorrelatorVector.cpp.i"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelatorVector.cpp > CMakeFiles/analysis.dir/autocorrelatorVector.cpp.i

src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/analysis.dir/autocorrelatorVector.cpp.s"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/autocorrelatorVector.cpp -o CMakeFiles/analysis.dir/autocorrelatorVector.cpp.s

src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o: src/analysis/CMakeFiles/analysis.dir/flags.make
src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o: ../src/analysis/dynamicalFeatures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/dynamicalFeatures.cpp

src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/analysis.dir/dynamicalFeatures.cpp.i"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/dynamicalFeatures.cpp > CMakeFiles/analysis.dir/dynamicalFeatures.cpp.i

src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/analysis.dir/dynamicalFeatures.cpp.s"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/dynamicalFeatures.cpp -o CMakeFiles/analysis.dir/dynamicalFeatures.cpp.s

src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.o: src/analysis/CMakeFiles/analysis.dir/flags.make
src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.o: ../src/analysis/structuralFeatures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.o"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/analysis.dir/structuralFeatures.cpp.o -c /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/structuralFeatures.cpp

src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/analysis.dir/structuralFeatures.cpp.i"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/structuralFeatures.cpp > CMakeFiles/analysis.dir/structuralFeatures.cpp.i

src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/analysis.dir/structuralFeatures.cpp.s"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis/structuralFeatures.cpp -o CMakeFiles/analysis.dir/structuralFeatures.cpp.s

# Object files for target analysis
analysis_OBJECTS = \
"CMakeFiles/analysis.dir/autocorrelator.cpp.o" \
"CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o" \
"CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o" \
"CMakeFiles/analysis.dir/structuralFeatures.cpp.o"

# External object files for target analysis
analysis_EXTERNAL_OBJECTS =

src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/autocorrelator.cpp.o
src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/autocorrelatorVector.cpp.o
src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/dynamicalFeatures.cpp.o
src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/structuralFeatures.cpp.o
src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/build.make
src/analysis/libanalysis.a: src/analysis/CMakeFiles/analysis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libanalysis.a"
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && $(CMAKE_COMMAND) -P CMakeFiles/analysis.dir/cmake_clean_target.cmake
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/analysis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/analysis/CMakeFiles/analysis.dir/build: src/analysis/libanalysis.a

.PHONY : src/analysis/CMakeFiles/analysis.dir/build

src/analysis/CMakeFiles/analysis.dir/clean:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis && $(CMAKE_COMMAND) -P CMakeFiles/analysis.dir/cmake_clean.cmake
.PHONY : src/analysis/CMakeFiles/analysis.dir/clean

src/analysis/CMakeFiles/analysis.dir/depend:
	cd /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/src/analysis /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/cmakeHelp/src/analysis/CMakeFiles/analysis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/analysis/CMakeFiles/analysis.dir/depend

