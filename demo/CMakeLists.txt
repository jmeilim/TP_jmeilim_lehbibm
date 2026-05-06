add_executable(simulation
    main.cxx
)

target_compile_features(simulation PUBLIC cxx_std_14)

target_link_libraries(simulation PRIVATE core)

target_compile_options(simulation PRIVATE
    -Wall
    -Wextra
    -O2
)   