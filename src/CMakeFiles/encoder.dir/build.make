# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/nick/git/comp339

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nick/git/comp339

# Include any dependencies generated for this target.
include src/CMakeFiles/encoder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/encoder.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/encoder.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/encoder.dir/flags.make

src/CMakeFiles/encoder.dir/encoder.cc.o: src/CMakeFiles/encoder.dir/flags.make
src/CMakeFiles/encoder.dir/encoder.cc.o: src/encoder.cc
src/CMakeFiles/encoder.dir/encoder.cc.o: src/CMakeFiles/encoder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nick/git/comp339/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/encoder.dir/encoder.cc.o"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/encoder.dir/encoder.cc.o -MF CMakeFiles/encoder.dir/encoder.cc.o.d -o CMakeFiles/encoder.dir/encoder.cc.o -c /home/nick/git/comp339/src/encoder.cc

src/CMakeFiles/encoder.dir/encoder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encoder.dir/encoder.cc.i"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nick/git/comp339/src/encoder.cc > CMakeFiles/encoder.dir/encoder.cc.i

src/CMakeFiles/encoder.dir/encoder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encoder.dir/encoder.cc.s"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nick/git/comp339/src/encoder.cc -o CMakeFiles/encoder.dir/encoder.cc.s

src/CMakeFiles/encoder.dir/parse_args.cc.o: src/CMakeFiles/encoder.dir/flags.make
src/CMakeFiles/encoder.dir/parse_args.cc.o: src/parse_args.cc
src/CMakeFiles/encoder.dir/parse_args.cc.o: src/CMakeFiles/encoder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nick/git/comp339/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/encoder.dir/parse_args.cc.o"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/encoder.dir/parse_args.cc.o -MF CMakeFiles/encoder.dir/parse_args.cc.o.d -o CMakeFiles/encoder.dir/parse_args.cc.o -c /home/nick/git/comp339/src/parse_args.cc

src/CMakeFiles/encoder.dir/parse_args.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encoder.dir/parse_args.cc.i"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nick/git/comp339/src/parse_args.cc > CMakeFiles/encoder.dir/parse_args.cc.i

src/CMakeFiles/encoder.dir/parse_args.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encoder.dir/parse_args.cc.s"
	cd /home/nick/git/comp339/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nick/git/comp339/src/parse_args.cc -o CMakeFiles/encoder.dir/parse_args.cc.s

# Object files for target encoder
encoder_OBJECTS = \
"CMakeFiles/encoder.dir/encoder.cc.o" \
"CMakeFiles/encoder.dir/parse_args.cc.o"

# External object files for target encoder
encoder_EXTERNAL_OBJECTS =

bin/encoder: src/CMakeFiles/encoder.dir/encoder.cc.o
bin/encoder: src/CMakeFiles/encoder.dir/parse_args.cc.o
bin/encoder: src/CMakeFiles/encoder.dir/build.make
bin/encoder: src/libcommon.so
bin/encoder: src/CMakeFiles/encoder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nick/git/comp339/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/encoder"
	cd /home/nick/git/comp339/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encoder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/encoder.dir/build: bin/encoder
.PHONY : src/CMakeFiles/encoder.dir/build

src/CMakeFiles/encoder.dir/clean:
	cd /home/nick/git/comp339/src && $(CMAKE_COMMAND) -P CMakeFiles/encoder.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/encoder.dir/clean

src/CMakeFiles/encoder.dir/depend:
	cd /home/nick/git/comp339 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nick/git/comp339 /home/nick/git/comp339/src /home/nick/git/comp339 /home/nick/git/comp339/src /home/nick/git/comp339/src/CMakeFiles/encoder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/encoder.dir/depend

