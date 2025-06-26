if(CMAKE_VERSION VERSION_LESS 3.14)
	cmake_minimum_required(VERSION 3.5)
else()
    cmake_minimum_required(VERSION 3.14)
endif()

project(ElaFramework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#在这里配置QT路径 例如 D:/Qt/6.6.2/msvc2019_64
if(NOT DEFINED QT_SDK_DIR)
    set(QT_SDK_DIR "" CACHE PATH "Qt SDK Root Directory (e.g., C:/Qt/6.9.0/msvc2022_64)")
endif()

SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

option(BUILD_ELAPACKETIO "Build ElaPacketIO" OFF)
list(APPEND CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(ElaWidgetTools)
if (WIN32 AND BUILD_ELAPACKETIO)
    add_definitions(-DBUILD_WITH_ELAPACKETIO)
    add_subdirectory(ElaPacketIO)
endif ()
add_subdirectory(ElaWidgetToolsExample)

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElaWidgetTools)
endif ()
