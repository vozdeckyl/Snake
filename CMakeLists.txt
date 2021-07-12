cmake_minimum_required(VERSION 3.13)

# set the project name
project(Snake VERSION 0.2)

# making the configuration file
configure_file(${PROJECT_SOURCE_DIR}/src/SnakeConfig.h.in ${PROJECT_SOURCE_DIR}/src/SnakeConfig.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME CounterTest COMMAND counterTest)
add_test(NAME LabelTest COMMAND labelTest)
add_test(NAME ImageTest COMMAND imageTest)
add_test(NAME MenuTest COMMAND menuTest)
