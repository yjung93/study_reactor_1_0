# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/yjung93/work/study/framework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yjung93/work/study/framework

# Include any dependencies generated for this target.
include CMakeFiles/example_reactor_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/example_reactor_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/example_reactor_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example_reactor_server.dir/flags.make

CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o: CMakeFiles/example_reactor_server.dir/flags.make
CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o: applications/example_reactor/MainServer.cpp
CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o: CMakeFiles/example_reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o -MF CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o.d -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o -c /home/yjung93/work/study/framework/applications/example_reactor/MainServer.cpp

CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjung93/work/study/framework/applications/example_reactor/MainServer.cpp > CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.i

CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjung93/work/study/framework/applications/example_reactor/MainServer.cpp -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.s

CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o: CMakeFiles/example_reactor_server.dir/flags.make
CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o: applications/example_reactor/Acceptor.cpp
CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o: CMakeFiles/example_reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o -MF CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o.d -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o -c /home/yjung93/work/study/framework/applications/example_reactor/Acceptor.cpp

CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjung93/work/study/framework/applications/example_reactor/Acceptor.cpp > CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.i

CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjung93/work/study/framework/applications/example_reactor/Acceptor.cpp -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.s

CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o: CMakeFiles/example_reactor_server.dir/flags.make
CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o: applications/example_reactor/ServerEventHandler.cpp
CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o: CMakeFiles/example_reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o -MF CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o.d -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o -c /home/yjung93/work/study/framework/applications/example_reactor/ServerEventHandler.cpp

CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjung93/work/study/framework/applications/example_reactor/ServerEventHandler.cpp > CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.i

CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjung93/work/study/framework/applications/example_reactor/ServerEventHandler.cpp -o CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.s

CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o: CMakeFiles/example_reactor_server.dir/flags.make
CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o: framework/v_1_0/EventHandler.cpp
CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o: CMakeFiles/example_reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o -MF CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o.d -o CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o -c /home/yjung93/work/study/framework/framework/v_1_0/EventHandler.cpp

CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjung93/work/study/framework/framework/v_1_0/EventHandler.cpp > CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.i

CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjung93/work/study/framework/framework/v_1_0/EventHandler.cpp -o CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.s

CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o: CMakeFiles/example_reactor_server.dir/flags.make
CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o: framework/v_1_0/Reactor.cpp
CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o: CMakeFiles/example_reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o -MF CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o.d -o CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o -c /home/yjung93/work/study/framework/framework/v_1_0/Reactor.cpp

CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjung93/work/study/framework/framework/v_1_0/Reactor.cpp > CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.i

CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjung93/work/study/framework/framework/v_1_0/Reactor.cpp -o CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.s

# Object files for target example_reactor_server
example_reactor_server_OBJECTS = \
"CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o" \
"CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o" \
"CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o" \
"CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o" \
"CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o"

# External object files for target example_reactor_server
example_reactor_server_EXTERNAL_OBJECTS =

example_reactor_server: CMakeFiles/example_reactor_server.dir/applications/example_reactor/MainServer.cpp.o
example_reactor_server: CMakeFiles/example_reactor_server.dir/applications/example_reactor/Acceptor.cpp.o
example_reactor_server: CMakeFiles/example_reactor_server.dir/applications/example_reactor/ServerEventHandler.cpp.o
example_reactor_server: CMakeFiles/example_reactor_server.dir/framework/v_1_0/EventHandler.cpp.o
example_reactor_server: CMakeFiles/example_reactor_server.dir/framework/v_1_0/Reactor.cpp.o
example_reactor_server: CMakeFiles/example_reactor_server.dir/build.make
example_reactor_server: CMakeFiles/example_reactor_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yjung93/work/study/framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable example_reactor_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_reactor_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example_reactor_server.dir/build: example_reactor_server
.PHONY : CMakeFiles/example_reactor_server.dir/build

CMakeFiles/example_reactor_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example_reactor_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example_reactor_server.dir/clean

CMakeFiles/example_reactor_server.dir/depend:
	cd /home/yjung93/work/study/framework && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yjung93/work/study/framework /home/yjung93/work/study/framework /home/yjung93/work/study/framework /home/yjung93/work/study/framework /home/yjung93/work/study/framework/CMakeFiles/example_reactor_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/example_reactor_server.dir/depend
