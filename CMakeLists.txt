cmake_minimum_required(VERSION 3.10)
enable_testing()
project(Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_compile_options(-Wall -Wextra -O2)
add_subdirectory(src)
add_subdirectory(demo)


find_package(Doxygen)
if(DOXYGEN_FOUND)
 add_custom_target(doc
 COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
 COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/latex make
 WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
 COMMENT "Generating documentation (HTML + PDF)"
 )
endif()