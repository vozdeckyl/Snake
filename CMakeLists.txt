cmake_minimum_required(VERSION 3.13)

# set the project name
project(Snake VERSION 0.2)

#set the DEBUG flag if necessary
if(CMAKE_BUILD_TYPE)
  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(DEBUG)
  endif()
endif()
  
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
add_test(NAME TravellerTest COMMAND travellerTest)
add_test(NAME ResultTest COMMAND resultTest)
add_test(NAME FileManagerTest COMMAND fileManagerTest)
add_test(NAME ScoreLoggerTest COMMAND scoreLoggerTest)
add_test(NAME SettingTest COMMAND settingTest)
add_test(NAME SettingsMenuTest COMMAND settingsMenuTest)

set(CPACK_PACKAGE_NAME "shellsnake")
set(CPACK_PACKAGE_VENDOR "LV")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lubos Vozdecky")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 2)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_EXECUTABLES snake)


install(
    TARGETS "snake"
    EXPORT "${PROJECT_NAME}Targets"
    COMPONENT ${PROJECT_NAME} # must be here, not any line lower
    #PERMISSIONS SETUID OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    # these get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
    )

install(
    FILES
    "data/logo.txt"
    DESTINATION /usr/local/share/${CPACK_PACKAGE_NAME}
    )

install(
    FILES
    "data/scores.bin"
    "data/settings.bin"
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE
    DESTINATION /var/${CPACK_PACKAGE_NAME}
    )

include(CPack)
