cmake_minimum_required(VERSION 3.28.3)
project(a6_7_luizamocan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC  ON)
set(CMAKE_AUTOUIC  ON)

include_directories(.)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(a6_7_luizamocan
    AdminRepository.cpp
    AdminRepository.h
    Controller.cpp
    Controller.h
    Dog.cpp
    Dog.h
        main.cpp
        UI.cpp
    UI.h
    UserRepository.cpp
    UserRepository.h
        ValidationException.h
        ValidationException.cpp
        ValidateDog.cpp
        ValidateDog.h
        FileSaver.h
        CSVSaver.cpp
        CSVSaver.h
        HTMLSaver.cpp
        HTMLSaver.h
        FileViewer.h
        HTMLViewer.cpp
        HTMLViewer.h
        CSVViewer.cpp
        CSVViewer.h
)

target_link_libraries(a6_7_luizamocan PRIVATE Qt6::Widgets)