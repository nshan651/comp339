FetchContent_MakeAvailable(googletest)

enable_testing()

# Common library
add_library(common SHARED lib.cc streams.cc)

# Test
add_executable(
  caeser_test
  caeser_test.cc
  encoder.cc
  decoder.cc
)
# target_compile_definitions(caeser_test PRIVATE -DSOME_MACRO)
target_link_libraries(
  caeser_test
  gtest_main
  common
)

# Decoder
add_executable(
  decoder
  decoder.cc
  build_cipher.cc
)
target_compile_definitions(decoder PRIVATE -DDECODER)
target_link_libraries(decoder common)

# Encoder
add_executable(
  encoder 
  encoder.cc
  build_cipher.cc
)
target_compile_definitions(encoder PRIVATE -DENCODER)
target_link_libraries(encoder common)

include(GoogleTest)
gtest_discover_tests(caeser_test)
