FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(cli11)

enable_testing()

# No deprecation warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

# Find fmt and spdlog
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# Common library
# add_library(common SHARED lib.cc)

add_executable(
  bloom 
  bloom.cc
)
target_compile_definitions(bloom PRIVATE -DBLOOM)
target_link_libraries(
  bloom PRIVATE CLI11::CLI11
  crypto
  fmt::fmt
  spdlog::spdlog
)

# include(GoogleTest)
# gtest_discover_tests(caeser_test)
