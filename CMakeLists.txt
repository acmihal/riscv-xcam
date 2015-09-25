cmake_minimum_required(VERSION 2.8)

project(riscv-xcam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fno-inline -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE on)

#include(ExternalProject)
#ExternalProject_Add(
#    gtest
#    GIT_REPOSITORY https://github.com/google/googletest.git
#    GIT_TAG release-1.7.0
#    INSTALL_COMMAND ""
#)
#
#add_library(libgtest IMPORTED STATIC GLOBAL)
#add_dependencies(libgtest gtest)

add_subdirectory(libxcam)
