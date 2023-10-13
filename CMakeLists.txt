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

add_subdirectory(monkas)

add_executable(monkas_main main.cc)
target_link_libraries(monkas_main PUBLIC monkas)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()