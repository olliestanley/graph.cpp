cmake_minimum_required(VERSION 3.10)
project(GraphLibrary)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

# header files
include_directories(include)

# library
add_library(graph_lib ${SRC_FILES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_FILES tests/*.cpp)

add_executable(test_graph ${TEST_FILES})
target_link_libraries(test_graph graph_lib gtest_main)

include(CTest)
enable_testing()
add_test(NAME GraphTests COMMAND test_graph)

add_executable(graph_main app/main.cpp)
target_link_libraries(graph_main graph_lib)
