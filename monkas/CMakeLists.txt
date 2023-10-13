add_library(monkas
        token.h
        lexer.h
        lexer.cc)
target_include_directories(monkas PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party/fmt>
$<INSTALL_INTERFACE:include/fmt>)
target_link_libraries(monkas PUBLIC fmt::fmt)
target_compile_features(monkas PUBLIC cxx_std_20)
target_compile_options(monkas PUBLIC -Wall -Wextra -Wpedantic)