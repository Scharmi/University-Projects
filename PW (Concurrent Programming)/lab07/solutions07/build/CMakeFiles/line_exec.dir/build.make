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
CMAKE_SOURCE_DIR = /home/scharmi/PW/lab07/solutions07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/scharmi/PW/lab07/solutions07/build

# Include any dependencies generated for this target.
include CMakeFiles/line_exec.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/line_exec.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/line_exec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/line_exec.dir/flags.make

CMakeFiles/line_exec.dir/line_exec.c.o: CMakeFiles/line_exec.dir/flags.make
CMakeFiles/line_exec.dir/line_exec.c.o: ../line_exec.c
CMakeFiles/line_exec.dir/line_exec.c.o: CMakeFiles/line_exec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scharmi/PW/lab07/solutions07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/line_exec.dir/line_exec.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/line_exec.dir/line_exec.c.o -MF CMakeFiles/line_exec.dir/line_exec.c.o.d -o CMakeFiles/line_exec.dir/line_exec.c.o -c /home/scharmi/PW/lab07/solutions07/line_exec.c

CMakeFiles/line_exec.dir/line_exec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/line_exec.dir/line_exec.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/scharmi/PW/lab07/solutions07/line_exec.c > CMakeFiles/line_exec.dir/line_exec.c.i

CMakeFiles/line_exec.dir/line_exec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/line_exec.dir/line_exec.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/scharmi/PW/lab07/solutions07/line_exec.c -o CMakeFiles/line_exec.dir/line_exec.c.s

# Object files for target line_exec
line_exec_OBJECTS = \
"CMakeFiles/line_exec.dir/line_exec.c.o"

# External object files for target line_exec
line_exec_EXTERNAL_OBJECTS =

line_exec: CMakeFiles/line_exec.dir/line_exec.c.o
line_exec: CMakeFiles/line_exec.dir/build.make
line_exec: liberr.a
line_exec: CMakeFiles/line_exec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scharmi/PW/lab07/solutions07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable line_exec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/line_exec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/line_exec.dir/build: line_exec
.PHONY : CMakeFiles/line_exec.dir/build

CMakeFiles/line_exec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/line_exec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/line_exec.dir/clean

CMakeFiles/line_exec.dir/depend:
	cd /home/scharmi/PW/lab07/solutions07/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scharmi/PW/lab07/solutions07 /home/scharmi/PW/lab07/solutions07 /home/scharmi/PW/lab07/solutions07/build /home/scharmi/PW/lab07/solutions07/build /home/scharmi/PW/lab07/solutions07/build/CMakeFiles/line_exec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/line_exec.dir/depend
