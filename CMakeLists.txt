cmake_minimum_required(VERSION 3.30)
project(Some_pseudogen_kod)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        SimulationController.cpp
        SimulationController.h
)

add_executable(Some_pseudogen_kod ${SOURCE_FILES})

include_directories(Map)
add_subdirectory(Map)

target_link_libraries(Some_pseudogen_kod MapOfObjects_lib)


add_subdirectory(Google_tests)