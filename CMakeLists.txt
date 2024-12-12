cmake_minimum_required(VERSION 3.30)
project(Some_pseudogen_kod)

set(CMAKE_CXX_STANDARD 14)

add_executable(Some_pseudogen_kod
    main.cpp
    robot.h
    robot.cpp
    map.cpp
    map.h
    mapObject.cpp
    mapObject.h)
