cmake_minimum_required(VERSION 3.1)

project(textedit-plugin LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Copy target file to current directory whenerver it is rebuilt
function(copy_after_build TARGET_NAME DIRECTORY)
    # Note: CMAKE_CURRENT_LIST_DIR is the directory where is this
    # CMakeLists.txt file.
    set(DESTDIR ${CMAKE_CURRENT_LIST_DIR}/${DIRECTORY})
    file(MAKE_DIRECTORY ${DESTDIR})

    # Copy binary file to <CMakeLists.txt didctory>./bin
    # after target is compiled.
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
                               $<TARGET_FILE:${TARGET_NAME}> ${DESTDIR}
                               )
endfunction()


find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

add_library(qmlplugin SHARED
    qmlplugin.cpp textfilemodel.cpp textfilemodel.hpp
    logger.cpp logger.hpp
    )
target_compile_definitions(qmlplugin PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qmlplugin PRIVATE Qt5::Core Qt5::Quick)
copy_after_build(qmlplugin "plugins")


add_executable(textedit-plugin
    main.cpp        
    qml.qrc)
target_compile_definitions(textedit-plugin PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(textedit-plugin PRIVATE Qt5::Core Qt5::Quick)
target_compile_definitions(textedit-plugin PRIVATE QT_QML_DEBUG  QT_DECLARATIVE_DEBUG)

copy_after_build(textedit-plugin ".")
