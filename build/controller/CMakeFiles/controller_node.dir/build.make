# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/ubuntu/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/catkin_ws/build

# Include any dependencies generated for this target.
include controller/CMakeFiles/controller_node.dir/depend.make

# Include the progress variables for this target.
include controller/CMakeFiles/controller_node.dir/progress.make

# Include the compile flags for this target's objects.
include controller/CMakeFiles/controller_node.dir/flags.make

controller/CMakeFiles/controller_node.dir/src/main.cpp.o: controller/CMakeFiles/controller_node.dir/flags.make
controller/CMakeFiles/controller_node.dir/src/main.cpp.o: /home/ubuntu/catkin_ws/src/controller/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object controller/CMakeFiles/controller_node.dir/src/main.cpp.o"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/controller_node.dir/src/main.cpp.o -c /home/ubuntu/catkin_ws/src/controller/src/main.cpp

controller/CMakeFiles/controller_node.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/controller_node.dir/src/main.cpp.i"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/catkin_ws/src/controller/src/main.cpp > CMakeFiles/controller_node.dir/src/main.cpp.i

controller/CMakeFiles/controller_node.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/controller_node.dir/src/main.cpp.s"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/catkin_ws/src/controller/src/main.cpp -o CMakeFiles/controller_node.dir/src/main.cpp.s

controller/CMakeFiles/controller_node.dir/src/main.cpp.o.requires:
.PHONY : controller/CMakeFiles/controller_node.dir/src/main.cpp.o.requires

controller/CMakeFiles/controller_node.dir/src/main.cpp.o.provides: controller/CMakeFiles/controller_node.dir/src/main.cpp.o.requires
	$(MAKE) -f controller/CMakeFiles/controller_node.dir/build.make controller/CMakeFiles/controller_node.dir/src/main.cpp.o.provides.build
.PHONY : controller/CMakeFiles/controller_node.dir/src/main.cpp.o.provides

controller/CMakeFiles/controller_node.dir/src/main.cpp.o.provides.build: controller/CMakeFiles/controller_node.dir/src/main.cpp.o

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o: controller/CMakeFiles/controller_node.dir/flags.make
controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o: /home/ubuntu/catkin_ws/src/controller/src/openni2.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/controller_node.dir/src/openni2.cpp.o -c /home/ubuntu/catkin_ws/src/controller/src/openni2.cpp

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/controller_node.dir/src/openni2.cpp.i"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/catkin_ws/src/controller/src/openni2.cpp > CMakeFiles/controller_node.dir/src/openni2.cpp.i

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/controller_node.dir/src/openni2.cpp.s"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/catkin_ws/src/controller/src/openni2.cpp -o CMakeFiles/controller_node.dir/src/openni2.cpp.s

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.requires:
.PHONY : controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.requires

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.provides: controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.requires
	$(MAKE) -f controller/CMakeFiles/controller_node.dir/build.make controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.provides.build
.PHONY : controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.provides

controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.provides.build: controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o: controller/CMakeFiles/controller_node.dir/flags.make
controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o: /home/ubuntu/catkin_ws/src/controller/src/Processing.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/controller_node.dir/src/Processing.cpp.o -c /home/ubuntu/catkin_ws/src/controller/src/Processing.cpp

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/controller_node.dir/src/Processing.cpp.i"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/catkin_ws/src/controller/src/Processing.cpp > CMakeFiles/controller_node.dir/src/Processing.cpp.i

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/controller_node.dir/src/Processing.cpp.s"
	cd /home/ubuntu/catkin_ws/build/controller && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/catkin_ws/src/controller/src/Processing.cpp -o CMakeFiles/controller_node.dir/src/Processing.cpp.s

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.requires:
.PHONY : controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.requires

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.provides: controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.requires
	$(MAKE) -f controller/CMakeFiles/controller_node.dir/build.make controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.provides.build
.PHONY : controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.provides

controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.provides.build: controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o

# Object files for target controller_node
controller_node_OBJECTS = \
"CMakeFiles/controller_node.dir/src/main.cpp.o" \
"CMakeFiles/controller_node.dir/src/openni2.cpp.o" \
"CMakeFiles/controller_node.dir/src/Processing.cpp.o"

# External object files for target controller_node
controller_node_EXTERNAL_OBJECTS =

/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: controller/CMakeFiles/controller_node.dir/src/main.cpp.o
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: controller/CMakeFiles/controller_node.dir/build.make
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_videostab.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_ccalib.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_fuzzy.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_rgbd.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_xfeatures2d.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_ximgproc.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_xobjdetect.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_xphoto.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/libroscpp.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/librosconsole.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/liblog4cxx.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/librostime.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /opt/ros/indigo/lib/libcpp_common.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_shape.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_video.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_calib3d.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_features2d.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_flann.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_objdetect.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_ml.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_highgui.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_photo.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_videoio.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_imgproc.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: /usr/local/lib/libopencv_core.so.3.2.0
/home/ubuntu/catkin_ws/devel/lib/controller/controller_node: controller/CMakeFiles/controller_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/ubuntu/catkin_ws/devel/lib/controller/controller_node"
	cd /home/ubuntu/catkin_ws/build/controller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/controller_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
controller/CMakeFiles/controller_node.dir/build: /home/ubuntu/catkin_ws/devel/lib/controller/controller_node
.PHONY : controller/CMakeFiles/controller_node.dir/build

controller/CMakeFiles/controller_node.dir/requires: controller/CMakeFiles/controller_node.dir/src/main.cpp.o.requires
controller/CMakeFiles/controller_node.dir/requires: controller/CMakeFiles/controller_node.dir/src/openni2.cpp.o.requires
controller/CMakeFiles/controller_node.dir/requires: controller/CMakeFiles/controller_node.dir/src/Processing.cpp.o.requires
.PHONY : controller/CMakeFiles/controller_node.dir/requires

controller/CMakeFiles/controller_node.dir/clean:
	cd /home/ubuntu/catkin_ws/build/controller && $(CMAKE_COMMAND) -P CMakeFiles/controller_node.dir/cmake_clean.cmake
.PHONY : controller/CMakeFiles/controller_node.dir/clean

controller/CMakeFiles/controller_node.dir/depend:
	cd /home/ubuntu/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/catkin_ws/src /home/ubuntu/catkin_ws/src/controller /home/ubuntu/catkin_ws/build /home/ubuntu/catkin_ws/build/controller /home/ubuntu/catkin_ws/build/controller/CMakeFiles/controller_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : controller/CMakeFiles/controller_node.dir/depend

