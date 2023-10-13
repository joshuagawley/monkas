add_executable(lexer_test lexer_test.cc)
target_include_directories(lexer_test PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include/gtest>
        $<INSTALL_INTERFACE:include/gtest>)
target_link_libraries(lexer_test PRIVATE gtest gtest_main monkas)
gtest_discover_tests(lexer_test)