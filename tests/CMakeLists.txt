cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(BOOST_ALL_DYN_LINK OFF)

include_directories(../include/)

file(GLOB_RECURSE TEST_FILES *.cpp)
string (REPLACE ";" "\n    " TEST_FILES_MSG "${TEST_FILES}")
message(STATUS "Test files:\n    ${TEST_FILES_MSG}")

add_executable(unidecode_test ${TEST_FILES})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${BOOST_INCLUDEDIR})

target_link_libraries(unidecode_test unidecode ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_LIBRARIES})
