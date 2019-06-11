cmake_minimum_required(VERSION 3.9)
project(qtquick_examples
    DESCRIPTION "Lot of QT Quick examples in a single CMake project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#-------------------------------------#

# Add sub projects
add_subdirectory(hello-world)
add_subdirectory(controls)
add_subdirectory(textedit)
add_subdirectory(todolist)
add_subdirectory(formula-calculator)



