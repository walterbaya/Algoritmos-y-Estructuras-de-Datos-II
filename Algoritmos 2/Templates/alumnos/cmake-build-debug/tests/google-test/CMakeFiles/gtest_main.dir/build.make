# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/walter/Descargas/CLion-2019.2.3/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/walter/Descargas/CLion-2019.2.3/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug"

# Include any dependencies generated for this target.
include tests/google-test/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include tests/google-test/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include tests/google-test/CMakeFiles/gtest_main.dir/flags.make

tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: tests/google-test/CMakeFiles/gtest_main.dir/flags.make
tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: ../tests/google-test/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/tests/google-test/src/gtest_main.cc"

tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/tests/google-test/src/gtest_main.cc" > CMakeFiles/gtest_main.dir/src/gtest_main.cc.i

tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/tests/google-test/src/gtest_main.cc" -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.s

# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

tests/google-test/libgtest_main.a: tests/google-test/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
tests/google-test/libgtest_main.a: tests/google-test/CMakeFiles/gtest_main.dir/build.make
tests/google-test/libgtest_main.a: tests/google-test/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest_main.a"
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/google-test/CMakeFiles/gtest_main.dir/build: tests/google-test/libgtest_main.a

.PHONY : tests/google-test/CMakeFiles/gtest_main.dir/build

tests/google-test/CMakeFiles/gtest_main.dir/clean:
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean.cmake
.PHONY : tests/google-test/CMakeFiles/gtest_main.dir/clean

tests/google-test/CMakeFiles/gtest_main.dir/depend:
	cd "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos" "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/tests/google-test" "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug" "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test" "/home/walter/Escritorio/Algoritmos 2/Memoria Dinamica/03_templates (1)/alumnos/cmake-build-debug/tests/google-test/CMakeFiles/gtest_main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/google-test/CMakeFiles/gtest_main.dir/depend

