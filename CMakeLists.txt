cmake_minimum_required(VERSION 3.9)
project(qtquick_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Add sub projects 
add_subdirectory(todolist)
add_subdirectory(hello-world)

