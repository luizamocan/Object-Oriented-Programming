cmake_minimum_required(VERSION 3.30)
project(e_915_luizamocan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
SET(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_executable(e_915_luizamocan
    main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        gui.cpp
        gui.h)
target_link_libraries(e_915_luizamocan
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
