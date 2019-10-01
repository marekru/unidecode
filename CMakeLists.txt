cmake_minimum_required(VERSION 3.10)
project(unidecode)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tests)

include_directories(include)

file(GLOB_RECURSE sources src/*.cpp)
string (REPLACE ";" "\n    " FILES_MSG "${sources}")
message(STATUS "source files:\n    ${FILES_MSG}")

add_library(unidecode ${sources})