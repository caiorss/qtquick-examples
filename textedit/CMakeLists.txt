cmake_minimum_required(VERSION 3.1)

project(textedit LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

add_executable(textedit
    main.cpp
    textfilemodel.cpp textfilemodel.hpp    
    qml.qrc)
target_compile_definitions(textedit PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(textedit PRIVATE
    Qt5::Core
    Qt5::Quick
    localib::logger
    )
target_compile_definitions(textedit PRIVATE QT_QML_DEBUG  QT_DECLARATIVE_DEBUG)
