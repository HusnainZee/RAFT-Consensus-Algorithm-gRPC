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
CMAKE_SOURCE_DIR = "/home/husnain/Music/ASM 6"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/husnain/Music/ASM 6/cmake/build"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

node.pb.cc: ../../node.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/husnain/Music/ASM 6/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating node.pb.cc, node.pb.h, node.grpc.pb.cc, node.grpc.pb.h"
	/bin/protoc-3.21.6.0 --grpc_out /home/husnain/Music/ASM\ 6/cmake/build --cpp_out /home/husnain/Music/ASM\ 6/cmake/build -I /home/husnain/Music/ASM\ 6 --plugin=protoc-gen-grpc="/bin/grpc_cpp_plugin" /home/husnain/Music/ASM\ 6/node.proto

node.pb.h: node.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate node.pb.h

node.grpc.pb.cc: node.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate node.grpc.pb.cc

node.grpc.pb.h: node.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate node.grpc.pb.h

CMakeFiles/server.dir/server.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.cc.o: ../../server.cc
CMakeFiles/server.dir/server.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/husnain/Music/ASM 6/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/server.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/server.cc.o -MF CMakeFiles/server.dir/server.cc.o.d -o CMakeFiles/server.dir/server.cc.o -c "/home/husnain/Music/ASM 6/server.cc"

CMakeFiles/server.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/husnain/Music/ASM 6/server.cc" > CMakeFiles/server.dir/server.cc.i

CMakeFiles/server.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/husnain/Music/ASM 6/server.cc" -o CMakeFiles/server.dir/server.cc.s

CMakeFiles/server.dir/node.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/node.pb.cc.o: node.pb.cc
CMakeFiles/server.dir/node.pb.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/husnain/Music/ASM 6/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/node.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/node.pb.cc.o -MF CMakeFiles/server.dir/node.pb.cc.o.d -o CMakeFiles/server.dir/node.pb.cc.o -c "/home/husnain/Music/ASM 6/cmake/build/node.pb.cc"

CMakeFiles/server.dir/node.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/node.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/husnain/Music/ASM 6/cmake/build/node.pb.cc" > CMakeFiles/server.dir/node.pb.cc.i

CMakeFiles/server.dir/node.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/node.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/husnain/Music/ASM 6/cmake/build/node.pb.cc" -o CMakeFiles/server.dir/node.pb.cc.s

CMakeFiles/server.dir/node.grpc.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/node.grpc.pb.cc.o: node.grpc.pb.cc
CMakeFiles/server.dir/node.grpc.pb.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/husnain/Music/ASM 6/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/node.grpc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/node.grpc.pb.cc.o -MF CMakeFiles/server.dir/node.grpc.pb.cc.o.d -o CMakeFiles/server.dir/node.grpc.pb.cc.o -c "/home/husnain/Music/ASM 6/cmake/build/node.grpc.pb.cc"

CMakeFiles/server.dir/node.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/node.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/husnain/Music/ASM 6/cmake/build/node.grpc.pb.cc" > CMakeFiles/server.dir/node.grpc.pb.cc.i

CMakeFiles/server.dir/node.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/node.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/husnain/Music/ASM 6/cmake/build/node.grpc.pb.cc" -o CMakeFiles/server.dir/node.grpc.pb.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.cc.o" \
"CMakeFiles/server.dir/node.pb.cc.o" \
"CMakeFiles/server.dir/node.grpc.pb.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.cc.o
server: CMakeFiles/server.dir/node.pb.cc.o
server: CMakeFiles/server.dir/node.grpc.pb.cc.o
server: CMakeFiles/server.dir/build.make
server: /lib/libgrpc++.a
server: /lib/libprotobuf.a
server: /lib/libgrpc.a
server: /lib/libz.a
server: /lib/libcares.a
server: /lib/libaddress_sorting.a
server: /lib/libre2.a
server: /lib/libupb.a
server: /lib/libabsl_raw_hash_set.a
server: /lib/libabsl_hashtablez_sampler.a
server: /lib/libabsl_hash.a
server: /lib/libabsl_city.a
server: /lib/libabsl_low_level_hash.a
server: /lib/libabsl_statusor.a
server: /lib/libgpr.a
server: /lib/libabsl_bad_variant_access.a
server: /lib/libabsl_status.a
server: /lib/libabsl_strerror.a
server: /lib/libabsl_random_distributions.a
server: /lib/libabsl_random_seed_sequences.a
server: /lib/libabsl_random_internal_pool_urbg.a
server: /lib/libabsl_random_internal_randen.a
server: /lib/libabsl_random_internal_randen_hwaes.a
server: /lib/libabsl_random_internal_randen_hwaes_impl.a
server: /lib/libabsl_random_internal_randen_slow.a
server: /lib/libabsl_random_internal_platform.a
server: /lib/libabsl_random_internal_seed_material.a
server: /lib/libabsl_random_seed_gen_exception.a
server: /lib/libabsl_cord.a
server: /lib/libabsl_bad_optional_access.a
server: /lib/libabsl_cordz_info.a
server: /lib/libabsl_cord_internal.a
server: /lib/libabsl_cordz_functions.a
server: /lib/libabsl_exponential_biased.a
server: /lib/libabsl_cordz_handle.a
server: /lib/libabsl_str_format_internal.a
server: /lib/libabsl_synchronization.a
server: /lib/libabsl_stacktrace.a
server: /lib/libabsl_symbolize.a
server: /lib/libabsl_debugging_internal.a
server: /lib/libabsl_demangle_internal.a
server: /lib/libabsl_graphcycles_internal.a
server: /lib/libabsl_malloc_internal.a
server: /lib/libabsl_time.a
server: /lib/libabsl_strings.a
server: /lib/libabsl_throw_delegate.a
server: /lib/libabsl_int128.a
server: /lib/libabsl_strings_internal.a
server: /lib/libabsl_base.a
server: /lib/libabsl_spinlock_wait.a
server: /lib/libabsl_raw_logging_internal.a
server: /lib/libabsl_log_severity.a
server: /lib/libabsl_civil_time.a
server: /lib/libabsl_time_zone.a
server: /lib/libssl.a
server: /lib/libcrypto.a
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/husnain/Music/ASM 6/cmake/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend: node.grpc.pb.cc
CMakeFiles/server.dir/depend: node.grpc.pb.h
CMakeFiles/server.dir/depend: node.pb.cc
CMakeFiles/server.dir/depend: node.pb.h
	cd "/home/husnain/Music/ASM 6/cmake/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/husnain/Music/ASM 6" "/home/husnain/Music/ASM 6" "/home/husnain/Music/ASM 6/cmake/build" "/home/husnain/Music/ASM 6/cmake/build" "/home/husnain/Music/ASM 6/cmake/build/CMakeFiles/server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

