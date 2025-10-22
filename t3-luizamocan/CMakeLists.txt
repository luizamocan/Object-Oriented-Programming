cmake_minimum_required(VERSION 3.30)
project(t3_luizamocan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC  ON)
SET(CMAKE_AUTOUIC ON)
include_directories(.)
SET(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_executable(t3_luizamocan
    controller.cpp
    controller.h
    domain.cpp
    domain.h
    gui.cpp
    gui.h
    main.cpp)
target_link_libraries(t3_luizamocan
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
