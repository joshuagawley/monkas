cmake_minimum_required(VERSION 3.22)
project(monkas LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(CTest)

set(FMT_INSTALL OFF)
add_subdirectory(third_party/fmt)
if(BUILD_TESTING)
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    add_subdirectory(third_party/googletest)
    include(GoogleTest)
endif()

add_library(monkas
        token.h
        lexer.h
        lexer.cc)
target_include_directories(monkas PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmt>
$<INSTALL_INTERFACE:include/fmt>)
target_link_libraries(monkas PUBLIC fmt::fmt)
target_compile_features(monkas PUBLIC cxx_std_20)
target_compile_options(monkas PUBLIC -Wall -Wextra -Wpedantic)

add_executable(monkas_main main.cc)
target_link_libraries(monkas_main PUBLIC monkas)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()