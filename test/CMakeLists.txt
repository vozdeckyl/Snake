# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(counterTest counterTest.cpp)
target_link_libraries(counterTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(labelTest labelTest.cpp)
target_link_libraries(labelTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(imageTest imageTest.cpp)
target_link_libraries(imageTest ${GTEST_LIBRARIES} pthread libSnake)
