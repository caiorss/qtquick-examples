cmake_minimum_required(VERSION 3.1)

project(hello-world LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

add_executable(hello-world main.cpp qml.qrc)
target_compile_definitions(hello-world PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(hello-world PRIVATE Qt5::Core Qt5::Quick)
