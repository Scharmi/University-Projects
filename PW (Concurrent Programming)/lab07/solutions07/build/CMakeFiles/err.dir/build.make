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
include CMakeFiles/err.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/err.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/err.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/err.dir/flags.make

CMakeFiles/err.dir/err.c.o: CMakeFiles/err.dir/flags.make
CMakeFiles/err.dir/err.c.o: ../err.c
CMakeFiles/err.dir/err.c.o: CMakeFiles/err.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scharmi/PW/lab07/solutions07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/err.dir/err.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/err.dir/err.c.o -MF CMakeFiles/err.dir/err.c.o.d -o CMakeFiles/err.dir/err.c.o -c /home/scharmi/PW/lab07/solutions07/err.c

CMakeFiles/err.dir/err.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/err.dir/err.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/scharmi/PW/lab07/solutions07/err.c > CMakeFiles/err.dir/err.c.i

CMakeFiles/err.dir/err.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/err.dir/err.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/scharmi/PW/lab07/solutions07/err.c -o CMakeFiles/err.dir/err.c.s

# Object files for target err
err_OBJECTS = \
"CMakeFiles/err.dir/err.c.o"

# External object files for target err
err_EXTERNAL_OBJECTS =

liberr.a: CMakeFiles/err.dir/err.c.o
liberr.a: CMakeFiles/err.dir/build.make
liberr.a: CMakeFiles/err.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scharmi/PW/lab07/solutions07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library liberr.a"
	$(CMAKE_COMMAND) -P CMakeFiles/err.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/err.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/err.dir/build: liberr.a
.PHONY : CMakeFiles/err.dir/build

CMakeFiles/err.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/err.dir/cmake_clean.cmake
.PHONY : CMakeFiles/err.dir/clean

CMakeFiles/err.dir/depend:
	cd /home/scharmi/PW/lab07/solutions07/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scharmi/PW/lab07/solutions07 /home/scharmi/PW/lab07/solutions07 /home/scharmi/PW/lab07/solutions07/build /home/scharmi/PW/lab07/solutions07/build /home/scharmi/PW/lab07/solutions07/build/CMakeFiles/err.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/err.dir/depend

