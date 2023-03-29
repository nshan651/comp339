FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(cli11)

enable_testing()

# No deprecation warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

# Common library
# add_library(common SHARED lib.cc)

# add_executable(
#   bloom 
#   bloom.cc
# )
# # target_compile_definitions(caeser_test PRIVATE -DSOME_MACRO)
# target_link_libraries(
#   bloom PRIVATE CLI11::CLI11
#   crypto
#   b2
#   # common
# )

add_executable(
  cloud
  cloud.cc
)
# target_compile_definitions(caeser_test PRIVATE -DSOME_MACRO)
target_link_libraries(
  cloud PRIVATE CLI11::CLI11
  crypto
  b2
  # common
)

# include(GoogleTest)
# gtest_discover_tests(caeser_test)
