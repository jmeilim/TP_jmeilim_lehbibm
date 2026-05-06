cmake_minimum_required(VERSION 3.10)

include(FetchContent)

FetchContent_Declare(
googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG
v1.17.0
)

FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(tests
    absorption.cxx
    periodique.cxx
    reflexion.cxx
    test_00.cxx
    test_01.cxx
    Test1.cxx
    Test2.cxx
)

target_link_libraries(tests
    PRIVATE core GTest::gtest_main
)
target_compile_features(tests PUBLIC cxx_std_14)

target_compile_options(tests PRIVATE
    -Wall
    -Wextra
    -O2
)
include(GoogleTest)
add_test(NAME AllTests COMMAND tests)