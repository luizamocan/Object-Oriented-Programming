cmake_minimum_required(VERSION 3.30)
project(a2_luizamocan_1 C)

set(CMAKE_C_STANDARD 11)


add_executable(a2_luizamocan_1
        domain.c
        domain.h
        dynamicArray.c
        dynamicArray.h
        repo.c
        repo.h
        service.c
        service.h
        ui.c
        ui.h
        main.c)
