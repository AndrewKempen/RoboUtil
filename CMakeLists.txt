cmake_minimum_required(VERSION 3.0)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
project(RoboUtil CXX)

set(CMAKE_CXX_FLAGS "-g -Wall")

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

include_directories(RoboUtil/src)


file(GLOB_RECURSE SRC_FILES "RoboUtil/src/*.cpp")
add_library(RoboUtil ${SRC_FILES})


################################
# Testing
################################

# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(3rdparty/googletest)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

##############
# Unit Tests
##############
file(GLOB TEST_FILES RoboUtil/test/*.cpp)
add_executable(RoboUtil_test ${TEST_FILES})

# Standard linking to gtest stuff.
target_link_libraries(RoboUtil_test gtest gtest_main)

# Extra linking for the project.
target_link_libraries(RoboUtil_test RoboUtil)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME that-test-I-made COMMAND RoboUtil_test)

