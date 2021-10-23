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

add_executable(menuTest menuTest.cpp)
target_link_libraries(menuTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(travellerTest travellerTest.cpp)
target_link_libraries(travellerTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(resultTest resultTest.cpp)
target_link_libraries(resultTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(fileManagerTest fileManagerTest.cpp)
target_link_libraries(fileManagerTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(scoreLoggerTest scoreLoggerTest.cpp)
target_link_libraries(scoreLoggerTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(settingTest settingTest.cpp)
target_link_libraries(settingTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(settingsMenuTest settingsMenuTest.cpp)
target_link_libraries(settingsMenuTest ${GTEST_LIBRARIES} pthread libSnake)

add_executable(snakeTest snakeTest.cpp)
target_link_libraries(snakeTest ${GTEST_LIBRARIES} pthread libSnake)
