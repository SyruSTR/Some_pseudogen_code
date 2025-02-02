cmake_minimum_required(VERSION 3.30)
project(Some_pseudogen_kod)

set(CMAKE_CXX_STANDARD 14)

add_executable(Some_pseudogen_kod
    main.cpp
        Map/robot.h
        Map/robot.cpp
        Map/map.cpp
        Map/map.h
        Map/mapObject.cpp
        Map/mapObject.h
        Map/Wall.h
        Map/Wall.cpp
        Map/Empty.h
        Map/Empty.cpp
    SimulationController.cpp
    SimulationController.h)
