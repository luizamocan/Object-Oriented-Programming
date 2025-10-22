cmake_minimum_required(VERSION 3.30)
project(a8_9_luizamocan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/mingw_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC  ON)
set(CMAKE_AUTOUIC  ON)
include_directories(.)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(a8_9_luizamocan
    AdminRepository.cpp
    AdminRepository.h
    Controller.cpp
    Controller.h
    CSVSaver.cpp
    CSVSaver.h
    CSVViewer.cpp
    CSVViewer.h
    Dog.cpp
    Dog.h
    FileSaver.h
    FileViewer.h
    HTMLSaver.cpp
    HTMLSaver.h
    HTMLViewer.cpp
    HTMLViewer.h
    main.cpp
    UI.cpp
    UI.h
    UserRepository.cpp
    UserRepository.h
    ValidateDog.cpp
    ValidateDog.h
    ValidationException.cpp
    ValidationException.h
        GUI.cpp
        GUI.h
        ModelGUI.cpp
        ModelGUI.h
        AdminGUI.cpp
        AdminGUI.h
        UserGUI.cpp
        UserGUI.h
        MainGUI.cpp
        MainGUI.h
        UndoAction.h
        AdoptionListWindow.cpp
        AdoptionListWindow.h
        AdoptionListModel.h
        AdoptionListModel.cpp
)


target_link_libraries(a8_9_luizamocan PRIVATE Qt6::Widgets)