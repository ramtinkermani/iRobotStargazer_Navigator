cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()

message(STATUS "Parth: "${PROJECT_SOURCE_DIR})
#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/src/lib)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/irobot_stargazer)
#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/include)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#rosbuild_add_library(libmem src/mem/memblock.c src/mem/memrec.c)
#rosbuild_add_executable(${PROJECT_NAME} src/memblock.c)
#rosbuild_add_executable(${PROJECT_NAME} src/memrec.c)

#rosbuild_add_executable(${PROJECT_NAME} src/bdd.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddapply.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddassoc.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddblk.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddcache.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddcmp.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddcomp.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bdddump.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddhash.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddmisc.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddprimes.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddprint.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddprprofile.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddqnt.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddreduce.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddrelprod.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddreorder.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddsat.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddsize.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddsupport.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddswap.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddunique.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/bddwarn.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/mtbdd.cpp)
#target_link_libraries(libbdd libmem)

rosbuild_add_executable(${PROJECT_NAME} src/construct.c)
rosbuild_add_executable(${PROJECT_NAME} src/misc.c)
rosbuild_add_executable(${PROJECT_NAME} src/monotone.c)
rosbuild_add_executable(${PROJECT_NAME} src/tri.c)
#rosbuild_add_executable(${PROJECT_NAME} src/alternating.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/buchi.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/cache.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/generalized.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/lex.cpp)
rosbuild_add_executable(${PROJECT_NAME} src/main.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/mem.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/parse.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/rewrt.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/set.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/trans.cpp)

rosbuild_add_executable(${PROJECT_NAME} src/lower_planner.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/trial.cpp)
#rosbuild_add_executable(${PROJECT_NAME} src/new_env.cpp)

#target_link_libraries(${PROJECT_NAME} libtriangle libltlba libbdd libmem)
#target_link_libraries(irobot_stargazer ltlba)
#target_link_libraries(irobot_stargazer memlib)
#target_link_libraries(irobot_stargazer bddlib)
