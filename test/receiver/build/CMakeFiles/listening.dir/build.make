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
CMAKE_SOURCE_DIR = /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build

# Include any dependencies generated for this target.
include CMakeFiles/listening.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/listening.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/listening.dir/flags.make

CMakeFiles/listening.dir/listening.cpp.o: CMakeFiles/listening.dir/flags.make
CMakeFiles/listening.dir/listening.cpp.o: ../listening.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/listening.dir/listening.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/listening.dir/listening.cpp.o -c /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/listening.cpp

CMakeFiles/listening.dir/listening.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/listening.dir/listening.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/listening.cpp > CMakeFiles/listening.dir/listening.cpp.i

CMakeFiles/listening.dir/listening.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/listening.dir/listening.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/listening.cpp -o CMakeFiles/listening.dir/listening.cpp.s

# Object files for target listening
listening_OBJECTS = \
"CMakeFiles/listening.dir/listening.cpp.o"

# External object files for target listening
listening_EXTERNAL_OBJECTS =

listening: CMakeFiles/listening.dir/listening.cpp.o
listening: CMakeFiles/listening.dir/build.make
listening: libclient.so
listening: CMakeFiles/listening.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable listening"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/listening.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/listening.dir/build: listening

.PHONY : CMakeFiles/listening.dir/build

CMakeFiles/listening.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/listening.dir/cmake_clean.cmake
.PHONY : CMakeFiles/listening.dir/clean

CMakeFiles/listening.dir/depend:
	cd /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build /home/pmmon/Documents/SNN/projects/LearnNetworking/Chapter5/receiver/build/CMakeFiles/listening.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/listening.dir/depend
