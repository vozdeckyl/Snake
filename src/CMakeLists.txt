#create a library from the files that have no dependence on the ncurses library
add_library(
    libSnake
    IDrawable.cpp
    menu.cpp
    counter.cpp
    label.cpp
    window.cpp
    result.cpp
    traveller.cpp
    image.cpp
    game.cpp
    snake.cpp
    scoreLogger.cpp
    setting.cpp
    settingsMenu.cpp
    fileManager.cpp
)


add_library(
  Xinterface
  Xinterface.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

#create the binary and add the library
add_executable(snake main.cpp NCursesEngine.cpp colors.cpp)
target_link_libraries(Xinterface X11)
target_link_libraries(snake libSnake ncurses pthread Xinterface)

target_include_directories(snake PUBLIC "${PROJECT_BINARY_DIR}")
