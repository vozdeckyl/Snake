#add all cpp files
file(GLOB ALL_CPP_FILES "*.cpp")

#create a library from the files
add_library(libSnake ${ALL_CPP_FILES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#create the binary and add the library
add_executable(snake main.cpp)
target_link_libraries(snake libSnake ncurses pthread)

target_include_directories(snake PUBLIC "${PROJECT_BINARY_DIR}")