cmake_minimum_required(VERSION 3.1)

project(qtquick1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

add_executable(qtquick1
    qml.qrc   # Resource file
    main.cpp
    todomodel.cpp todomodel.hpp
    todolist.cpp todolist.hpp
    )
target_compile_definitions(qtquick1 PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qtquick1 PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets)
