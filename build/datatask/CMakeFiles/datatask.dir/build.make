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

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhangqi/project/dataservice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhangqi/project/dataservice/build

# Include any dependencies generated for this target.
include datatask/CMakeFiles/datatask.dir/depend.make

# Include the progress variables for this target.
include datatask/CMakeFiles/datatask.dir/progress.make

# Include the compile flags for this target's objects.
include datatask/CMakeFiles/datatask.dir/flags.make

datatask/CMakeFiles/datatask.dir/datatest.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/datatest.cpp.o: ../datatask/datatest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/datatest.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/datatest.cpp.o -c /home/zhangqi/project/dataservice/datatask/datatest.cpp

datatask/CMakeFiles/datatask.dir/datatest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/datatest.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/datatask/datatest.cpp > CMakeFiles/datatask.dir/datatest.cpp.i

datatask/CMakeFiles/datatask.dir/datatest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/datatest.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/datatask/datatest.cpp -o CMakeFiles/datatask.dir/datatest.cpp.s

datatask/CMakeFiles/datatask.dir/datatest.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/datatest.cpp.o.requires

datatask/CMakeFiles/datatask.dir/datatest.cpp.o.provides: datatask/CMakeFiles/datatask.dir/datatest.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/datatest.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/datatest.cpp.o.provides

datatask/CMakeFiles/datatask.dir/datatest.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/datatest.cpp.o

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o: ../datatask/datatask_node.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/datatask_node.cpp.o -c /home/zhangqi/project/dataservice/datatask/datatask_node.cpp

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/datatask_node.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/datatask/datatask_node.cpp > CMakeFiles/datatask.dir/datatask_node.cpp.i

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/datatask_node.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/datatask/datatask_node.cpp -o CMakeFiles/datatask.dir/datatask_node.cpp.s

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.requires

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.provides: datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.provides

datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o: ../include/inifile/inifile.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o -c /home/zhangqi/project/dataservice/include/inifile/inifile.cpp

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/inifile/inifile.cpp > CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/inifile/inifile.cpp -o CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o: ../include/inifile/stringutil.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o -c /home/zhangqi/project/dataservice/include/inifile/stringutil.cpp

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/inifile/stringutil.cpp > CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/inifile/stringutil.cpp -o CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o: ../include/redis/redisworker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o -c /home/zhangqi/project/dataservice/include/redis/redisworker.cpp

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/redis/redisworker.cpp > CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/redis/redisworker.cpp -o CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o: ../include/mongodb/BSONCreator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o -c /home/zhangqi/project/dataservice/include/mongodb/BSONCreator.cpp

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/mongodb/BSONCreator.cpp > CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/mongodb/BSONCreator.cpp -o CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o: ../include/mongodb/em_mongodb.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o -c /home/zhangqi/project/dataservice/include/mongodb/em_mongodb.cpp

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/mongodb/em_mongodb.cpp > CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/mongodb/em_mongodb.cpp -o CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o: ../include/zookeeper/ksm_zk.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o -c /home/zhangqi/project/dataservice/include/zookeeper/ksm_zk.cpp

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/zookeeper/ksm_zk.cpp > CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/zookeeper/ksm_zk.cpp -o CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o: datatask/CMakeFiles/datatask.dir/flags.make
datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o: ../include/utility/utility.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhangqi/project/dataservice/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o"
	cd /home/zhangqi/project/dataservice/build/datatask && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o -c /home/zhangqi/project/dataservice/include/utility/utility.cpp

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/datatask.dir/__/include/utility/utility.cpp.i"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zhangqi/project/dataservice/include/utility/utility.cpp > CMakeFiles/datatask.dir/__/include/utility/utility.cpp.i

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/datatask.dir/__/include/utility/utility.cpp.s"
	cd /home/zhangqi/project/dataservice/build/datatask && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zhangqi/project/dataservice/include/utility/utility.cpp -o CMakeFiles/datatask.dir/__/include/utility/utility.cpp.s

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.requires:
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.requires

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.provides: datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.requires
	$(MAKE) -f datatask/CMakeFiles/datatask.dir/build.make datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.provides.build
.PHONY : datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.provides

datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.provides.build: datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o

# Object files for target datatask
datatask_OBJECTS = \
"CMakeFiles/datatask.dir/datatest.cpp.o" \
"CMakeFiles/datatask.dir/datatask_node.cpp.o" \
"CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o" \
"CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o" \
"CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o" \
"CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o" \
"CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o" \
"CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o" \
"CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o"

# External object files for target datatask
datatask_EXTERNAL_OBJECTS =

datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/datatest.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/build.make
datatask/Debug/datatask: datatask/CMakeFiles/datatask.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Debug/datatask"
	cd /home/zhangqi/project/dataservice/build/datatask && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/datatask.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
datatask/CMakeFiles/datatask.dir/build: datatask/Debug/datatask
.PHONY : datatask/CMakeFiles/datatask.dir/build

datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/datatest.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/datatask_node.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/inifile/inifile.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/inifile/stringutil.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/redis/redisworker.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/mongodb/BSONCreator.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/mongodb/em_mongodb.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/zookeeper/ksm_zk.cpp.o.requires
datatask/CMakeFiles/datatask.dir/requires: datatask/CMakeFiles/datatask.dir/__/include/utility/utility.cpp.o.requires
.PHONY : datatask/CMakeFiles/datatask.dir/requires

datatask/CMakeFiles/datatask.dir/clean:
	cd /home/zhangqi/project/dataservice/build/datatask && $(CMAKE_COMMAND) -P CMakeFiles/datatask.dir/cmake_clean.cmake
.PHONY : datatask/CMakeFiles/datatask.dir/clean

datatask/CMakeFiles/datatask.dir/depend:
	cd /home/zhangqi/project/dataservice/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangqi/project/dataservice /home/zhangqi/project/dataservice/datatask /home/zhangqi/project/dataservice/build /home/zhangqi/project/dataservice/build/datatask /home/zhangqi/project/dataservice/build/datatask/CMakeFiles/datatask.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : datatask/CMakeFiles/datatask.dir/depend

