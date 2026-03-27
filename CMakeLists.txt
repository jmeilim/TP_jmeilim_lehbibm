cmake_minimum_required(VERSION 3.10)
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
add_executable(test_00 test/test_00.cxx)
target_link_libraries(test_00 core)

add_executable(test_01 test/test_01.cxx)
target_link_libraries(test_01 core)

if(DOXYGEN_FOUND)
 add_custom_target(doc
 COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
 COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/latex make
 WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
 COMMENT "Generating documentation (HTML + PDF)"
 )
endif()