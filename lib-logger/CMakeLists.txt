cmake_minimum_required(VERSION 3.1)

project(liblogger LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)


#==== Target: lib_logger / library

add_library(logger logger.cpp logger.hpp)
target_compile_definitions(logger PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(logger PUBLIC Qt5::Core Qt5::Quick)


#===== Target: localib::logger / ALIAS to library

# Create alias target to lib_logger
add_library(localib::logger ALIAS logger)



