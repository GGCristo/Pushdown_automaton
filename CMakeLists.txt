cmake_minimum_required(VERSION "3.9.2")

project(APf)

set(SOURCES
  src/Apf.cpp
  src/Transition.cpp
)

set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g -pedantic-errors -Wall -Wextra -std=c++17 -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pedantic-errors -Wall -Wextra -std=c++17")
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,-clang-analyzer-*,performance-*,readability-*,-readability-implicit-bool-conversion,-readability-magic-numbers,modernize-*,-modernize-use-trailing-return-type,bugprone-*)

add_executable(main ${SOURCES} src/main.cpp)

