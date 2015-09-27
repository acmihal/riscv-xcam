cmake_minimum_required(VERSION 2.8)

project(riscv-xcam)

# can be changed to target_compile_features with cmake 3.x
add_compile_options("-std=c++11")

#set(CMAKE_VERBOSE_MAKEFILE on)

include(ExternalProject)
ExternalProject_Add(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.7.0
    CMAKE_CACHE_ARGS -Dgtest_disable_pthreads:BOOL=ON
    INSTALL_COMMAND ""
)
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)
add_library(libgtestmain IMPORTED STATIC GLOBAL)
add_dependencies(libgtestmain gtest)
set_target_properties(libgtestmain PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest_main.a"
)
include_directories("${source_dir}/include")

include_directories(include)
add_subdirectory(libxcam)

if(CMAKE_CROSSCOMPILING)
    install(DIRECTORY include/ DESTINATION $ENV{RISCV}/riscv64-unknown-elf/include/riscv-xcam
            FILES_MATCHING PATTERN "*.h")
else()
    install(DIRECTORY include/ DESTINATION $ENV{RISCV}/include/riscv-xcam
            FILES_MATCHING PATTERN "*.h")
endif()

if(NOT CMAKE_CROSSCOMPILING)
    enable_testing()
    add_subdirectory(test)
endif()
