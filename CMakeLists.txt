cmake_minimum_required(VERSION 3.10)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()
project(Simulation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_compile_options(-Wall -Wextra)
add_executable(simulation
    demo/main.cxx
    src/Lab2.cxx
    src/Lab3.cxx
    src/Lab4.cxx
)
add_library(core
    src/Lab2.cxx
    src/Lab4.cxx
)
add_executable(Test1 test/Test1.cxx)
target_link_libraries(Test1 core GTest::gtest_main)


include(GoogleTest)

gtest_discover_tests(Test1)


if(DOXYGEN_FOUND)
 add_custom_target(doc
 COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
 COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/latex make
 WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
 COMMENT "Generating documentation (HTML + PDF)"
 )
endif()