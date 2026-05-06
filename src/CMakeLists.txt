add_library(core
    Particle.cxx
    Vector.cxx
    Univers.cxx
    Forces.cxx
    Stromer.cxx
    Boundary.cxx
)

target_include_directories(core
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(core PRIVATE -Wall -Wextra -O2)

target_compile_features(core PUBLIC cxx_std_14)