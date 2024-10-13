cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
set(PROJECT_NAME "qtkeyboard")

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

# Qt Cmake MOC RCC enable
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (NOT DEFINED QtVersion)
    set(QtVersion Qt5)
endif()
# Qt Packages
message(STATUS "Use QtVersion: ${QtVersion}")
find_package(${QtVersion} COMPONENTS Gui Core Widgets Svg REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/dist/out)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/dist/lib)

# About Keyboard Plugin Library
add_subdirectory(${PROJECT_SOURCE_DIR}/plugin)

# About Test Executable
add_subdirectory(${PROJECT_SOURCE_DIR}/app/qtKeyboardTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/app/test)
