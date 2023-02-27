cmake_minimum_required(VERSION 3.14)

project(bloom_filter)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)
include_directories(include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Fetch CLI11 from GitHub
include(FetchContent)
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.2.0
)
FetchContent_MakeAvailable(CLI11)

include_directories(${CLI11_DIR}/include)

add_subdirectory(src)
