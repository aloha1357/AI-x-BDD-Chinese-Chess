cmake_minimum_required(VERSION 3.20)
project(ChineseChess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Collect source files
file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/**/*.h")
file(GLOB_RECURSE STEP_SOURCES "features/step_definitions/*.cpp")

# Create executable for tests
add_executable(chinese_chess_tests
    ${SOURCES}
    ${STEP_SOURCES}
    test/main.cpp
)

# Link Google Test
target_link_libraries(chinese_chess_tests
    gtest_main
    gtest
)

# Enable testing
enable_testing()
add_test(NAME ChineseChessTests COMMAND chinese_chess_tests)
