# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /vagrant

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /vagrant/build

# Utility rule file for foc.

# Include the progress variables for this target.
include CMakeFiles/foc.dir/progress.make

foc: CMakeFiles/foc.dir/build.make

.PHONY : foc

# Rule to build all files generated by this target.
CMakeFiles/foc.dir/build: foc

.PHONY : CMakeFiles/foc.dir/build

CMakeFiles/foc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/foc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/foc.dir/clean

CMakeFiles/foc.dir/depend:
	cd /vagrant/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /vagrant /vagrant /vagrant/build /vagrant/build /vagrant/build/CMakeFiles/foc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/foc.dir/depend
