FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(cli11)
# include(cli11)

enable_testing()

# Common library
add_library(common SHARED lib.cc)

# main
add_executable(
  bloom 
  bloom.cc
  hash.cc
)
# target_compile_definitions(caeser_test PRIVATE -DSOME_MACRO)
target_link_libraries(
  bloom PRIVATE CLI11::CLI11
  crypto
  common
)

# Decoder
# add_executable(
#   decoder
#   decoder.cc
#   build_cipher.cc
# )
# target_compile_definitions(decoder PRIVATE -DDECODER)
# target_link_libraries(decoder common)

# # Encoder
# add_executable(
#   encoder 
#   encoder.cc
#   build_cipher.cc
# )
# target_compile_definitions(encoder PRIVATE -DENCODER)
# target_link_libraries(encoder common)

# include(GoogleTest)
# gtest_discover_tests(caeser_test)
