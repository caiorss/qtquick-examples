cmake_minimum_required(VERSION 3.9)
project(qtquick_examples
    DESCRIPTION "Lot of QT Quick examples in a single CMake project"
    LANGUAGES CXX)

# Make whole compilation verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}"  "-DQT_QML_DEBUG")
add_definitions(-DQT_QML_DEBUG -DQML_IMPORT_TRACE=1)


#-------------------------------------#

# Add sub projects
add_subdirectory(hello-world)
add_subdirectory(controls)
add_subdirectory(textedit)
add_subdirectory(textedit-plugin)
add_subdirectory(todolist)
add_subdirectory(formula-calculator)
add_subdirectory(http-request)
add_subdirectory(table-xml)
add_subdirectory(qml-widget-disp)
