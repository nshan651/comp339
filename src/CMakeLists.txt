FetchContent_MakeAvailable(googletest)

enable_testing()

# add_executable(
#   square_root_tests
#   square_root_tests.cc
#   square_root.c
# )
# target_link_libraries(
#   square_root_tests
#   gtest_main
# )

# Common library
add_library(common SHARED lib.cc)

# Main executable
add_executable(
  main
  main.cc
  parse_args.cc
)
target_link_libraries(main common)

add_executable(
  decoder
  decoder.cc
  parse_args.cc
)
target_link_libraries(decoder common)

add_executable(
  encoder 
  encoder.cc
  parse_args.cc
)
target_link_libraries(encoder common)

# add_executable(
#   decoder
#   decoder.cc
#   utils.cc
# )
# target_link_libraries(decoder -lm)

include(GoogleTest)
# gtest_discover_tests(caeser_test)
