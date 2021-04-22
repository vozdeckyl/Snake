cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snake VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# making the configuration file
configure_file(SnakeConfig.h.in SnakeConfig.h)

# add the executable
add_executable(snake main.cpp menu.cpp)

#importing the ncurses library
target_link_libraries(snake ncurses)

#library needed for multithreading
target_link_libraries(snake pthread)

target_include_directories(snake PUBLIC "${PROJECT_BINARY_DIR}")