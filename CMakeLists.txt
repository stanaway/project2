cmake_minimum_required(VERSION 4.3)
project(2110_project2)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(2110_project2
        src/main.cpp
        src/Facility.cpp
        src/FacilityHashTable.cpp
        src/FacilityManager.cpp
        src/CampusGraph.cpp
)
