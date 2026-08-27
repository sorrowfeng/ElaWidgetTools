# 3.5 is actually available almost everywhere.
# 3.30 as the upper policy limit avoids CMake deprecation warnings.
cmake_minimum_required(VERSION 3.5...3.30)

project(ElaFramework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#在这里配置QT路径 例如 D:/Qt/6.6.2/msvc2019_64 D:/Qt/5.15.2/msvc2019_64 /home/liniyous/Qt/5.15.2/gcc_64
if(NOT DEFINED QT_SDK_DIR)
    set(QT_SDK_DIR "" CACHE PATH "Qt SDK Root Directory (e.g., C:/Qt/6.9.0/msvc2022_64)")
endif()
message("在CMAKE中配置 QT_SDK_DIR 选项指定QT路径; 当前路径: ${QT_SDK_DIR}")

if(NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "Installation path" FORCE)
endif()

option(BUILD_EXAMPLES "Build ElaWidgetToolsExample" ON)
list(APPEND CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (${QT_VERSION} VERSION_GREATER 6.7.0 OR ${QT_VERSION} VERSION_LESS 5.12.0)
    message(WARNING "你当前使用的QT版本不在官方维护范围内！可能出现编译失败或使用时崩溃问题，推荐QT版本为QT5.15.2 QT6.6.2 QT6.6.3！请知悉~")
    message(WARNING "The QT version you are currently using is no longer under maintenance! There may be issues such as compilation failures or crashes during use. The recommended QT versions are QT5.15.2, QT6.6.2, and QT6.6.3! Please be advised")
endif ()

if (${QT_VERSION} VERSION_GREATER_EQUAL 6.5.3 AND ${QT_VERSION} VERSION_LESS_EQUAL 6.6.1)
    message(FATAL_ERROR "你当前使用的QT版本为不推荐版本！可能出现使用时异常或崩溃问题，推荐QT版本为QT5.15.2 QT6.6.2 QT6.6.3！请知悉~")
    message(FATAL_ERROR "The QT version you are currently using is not recommended! It may cause exceptions or crashes during operation. The recommended QT versions are QT5.15.2, QT6.6.2, and QT6.6.3! Please be advised")
endif ()

if (NOT WIN32)
    add_link_options(-Wl,--disable-new-dtags)
    set(CMAKE_SKIP_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "${QT_SDK_DIR}/lib:${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib")
endif ()

add_subdirectory(ElaWidgetTools)
if (BUILD_EXAMPLES)
    add_subdirectory(ElaWidgetToolsExample)
endif ()

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ElaWidgetTools)
endif ()
