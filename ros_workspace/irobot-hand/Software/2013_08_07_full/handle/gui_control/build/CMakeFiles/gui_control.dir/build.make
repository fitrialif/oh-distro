# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build

# Include any dependencies generated for this target.
include CMakeFiles/gui_control.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gui_control.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gui_control.dir/flags.make

CMakeFiles/gui_control.dir/src/controlform.o: CMakeFiles/gui_control.dir/flags.make
CMakeFiles/gui_control.dir/src/controlform.o: ../src/controlform.cpp
CMakeFiles/gui_control.dir/src/controlform.o: ../manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_lib/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /opt/ros/fuerte/stacks/qt_ros/qt_build/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/gui_control.dir/src/controlform.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/msg_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gui_control.dir/src/controlform.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/gui_control.dir/src/controlform.o -c /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/controlform.cpp

CMakeFiles/gui_control.dir/src/controlform.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui_control.dir/src/controlform.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/controlform.cpp > CMakeFiles/gui_control.dir/src/controlform.i

CMakeFiles/gui_control.dir/src/controlform.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui_control.dir/src/controlform.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/controlform.cpp -o CMakeFiles/gui_control.dir/src/controlform.s

CMakeFiles/gui_control.dir/src/controlform.o.requires:
.PHONY : CMakeFiles/gui_control.dir/src/controlform.o.requires

CMakeFiles/gui_control.dir/src/controlform.o.provides: CMakeFiles/gui_control.dir/src/controlform.o.requires
	$(MAKE) -f CMakeFiles/gui_control.dir/build.make CMakeFiles/gui_control.dir/src/controlform.o.provides.build
.PHONY : CMakeFiles/gui_control.dir/src/controlform.o.provides

CMakeFiles/gui_control.dir/src/controlform.o.provides.build: CMakeFiles/gui_control.dir/src/controlform.o

CMakeFiles/gui_control.dir/src/gui.o: CMakeFiles/gui_control.dir/flags.make
CMakeFiles/gui_control.dir/src/gui.o: ../src/gui.cpp
CMakeFiles/gui_control.dir/src/gui.o: ../manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_lib/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /opt/ros/fuerte/stacks/qt_ros/qt_build/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/gui_control.dir/src/gui.o: /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/msg_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gui_control.dir/src/gui.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/gui_control.dir/src/gui.o -c /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/gui.cpp

CMakeFiles/gui_control.dir/src/gui.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui_control.dir/src/gui.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/gui.cpp > CMakeFiles/gui_control.dir/src/gui.i

CMakeFiles/gui_control.dir/src/gui.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui_control.dir/src/gui.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/src/gui.cpp -o CMakeFiles/gui_control.dir/src/gui.s

CMakeFiles/gui_control.dir/src/gui.o.requires:
.PHONY : CMakeFiles/gui_control.dir/src/gui.o.requires

CMakeFiles/gui_control.dir/src/gui.o.provides: CMakeFiles/gui_control.dir/src/gui.o.requires
	$(MAKE) -f CMakeFiles/gui_control.dir/build.make CMakeFiles/gui_control.dir/src/gui.o.provides.build
.PHONY : CMakeFiles/gui_control.dir/src/gui.o.provides

CMakeFiles/gui_control.dir/src/gui.o.provides.build: CMakeFiles/gui_control.dir/src/gui.o

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o: CMakeFiles/gui_control.dir/flags.make
CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o: include/gui_control/moc_controlform.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o -c /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/include/gui_control/moc_controlform.cxx

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/include/gui_control/moc_controlform.cxx > CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.i

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/include/gui_control/moc_controlform.cxx -o CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.s

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.requires:
.PHONY : CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.requires

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.provides: CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.requires
	$(MAKE) -f CMakeFiles/gui_control.dir/build.make CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.provides.build
.PHONY : CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.provides

CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.provides.build: CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o

ui_controlform.h: ../ui/controlform.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_controlform.h"
	/usr/bin/uic-qt4 -o /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/ui_controlform.h /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/ui/controlform.ui

include/gui_control/moc_controlform.cxx: ../include/gui_control/controlform.hpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating include/gui_control/moc_controlform.cxx"
	/usr/bin/moc-qt4 -I/home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/include -I/home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/msg_gen/cpp/include -I/opt/ros/fuerte/include -I/home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_lib/include -I/usr/include/qt4 -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build -DQT_GUI_LIB -DQT_CORE_LIB -o /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/include/gui_control/moc_controlform.cxx /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/include/gui_control/controlform.hpp

# Object files for target gui_control
gui_control_OBJECTS = \
"CMakeFiles/gui_control.dir/src/controlform.o" \
"CMakeFiles/gui_control.dir/src/gui.o" \
"CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o"

# External object files for target gui_control
gui_control_EXTERNAL_OBJECTS =

../bin/gui_control: CMakeFiles/gui_control.dir/src/controlform.o
../bin/gui_control: CMakeFiles/gui_control.dir/src/gui.o
../bin/gui_control: CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o
../bin/gui_control: /usr/lib/x86_64-linux-gnu/libQtGui.so
../bin/gui_control: /usr/lib/x86_64-linux-gnu/libQtCore.so
../bin/gui_control: CMakeFiles/gui_control.dir/build.make
../bin/gui_control: CMakeFiles/gui_control.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/gui_control"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gui_control.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gui_control.dir/build: ../bin/gui_control
.PHONY : CMakeFiles/gui_control.dir/build

CMakeFiles/gui_control.dir/requires: CMakeFiles/gui_control.dir/src/controlform.o.requires
CMakeFiles/gui_control.dir/requires: CMakeFiles/gui_control.dir/src/gui.o.requires
CMakeFiles/gui_control.dir/requires: CMakeFiles/gui_control.dir/include/gui_control/moc_controlform.o.requires
.PHONY : CMakeFiles/gui_control.dir/requires

CMakeFiles/gui_control.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gui_control.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gui_control.dir/clean

CMakeFiles/gui_control.dir/depend: ui_controlform.h
CMakeFiles/gui_control.dir/depend: include/gui_control/moc_controlform.cxx
	cd /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build /home/sisir/irobot-hand/Software/2013_08_07_full/handle/gui_control/build/CMakeFiles/gui_control.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gui_control.dir/depend

