# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/scharmi/PW/lab08/solutions08

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/scharmi/PW/lab08/solutions08/build

# Include any dependencies generated for this target.
include CMakeFiles/pipeline-utils.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pipeline-utils.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pipeline-utils.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pipeline-utils.dir/flags.make

CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o: CMakeFiles/pipeline-utils.dir/flags.make
CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o: ../pipeline-utils.c
CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o: CMakeFiles/pipeline-utils.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scharmi/PW/lab08/solutions08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o -MF CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o.d -o CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o -c /home/scharmi/PW/lab08/solutions08/pipeline-utils.c

CMakeFiles/pipeline-utils.dir/pipeline-utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pipeline-utils.dir/pipeline-utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/scharmi/PW/lab08/solutions08/pipeline-utils.c > CMakeFiles/pipeline-utils.dir/pipeline-utils.c.i

CMakeFiles/pipeline-utils.dir/pipeline-utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pipeline-utils.dir/pipeline-utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/scharmi/PW/lab08/solutions08/pipeline-utils.c -o CMakeFiles/pipeline-utils.dir/pipeline-utils.c.s

# Object files for target pipeline-utils
pipeline__utils_OBJECTS = \
"CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o"

# External object files for target pipeline-utils
pipeline__utils_EXTERNAL_OBJECTS =

libpipeline-utils.a: CMakeFiles/pipeline-utils.dir/pipeline-utils.c.o
libpipeline-utils.a: CMakeFiles/pipeline-utils.dir/build.make
libpipeline-utils.a: CMakeFiles/pipeline-utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scharmi/PW/lab08/solutions08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libpipeline-utils.a"
	$(CMAKE_COMMAND) -P CMakeFiles/pipeline-utils.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pipeline-utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pipeline-utils.dir/build: libpipeline-utils.a
.PHONY : CMakeFiles/pipeline-utils.dir/build

CMakeFiles/pipeline-utils.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pipeline-utils.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pipeline-utils.dir/clean

CMakeFiles/pipeline-utils.dir/depend:
	cd /home/scharmi/PW/lab08/solutions08/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scharmi/PW/lab08/solutions08 /home/scharmi/PW/lab08/solutions08 /home/scharmi/PW/lab08/solutions08/build /home/scharmi/PW/lab08/solutions08/build /home/scharmi/PW/lab08/solutions08/build/CMakeFiles/pipeline-utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pipeline-utils.dir/depend

