Smart Campus Navigation and Facility Analytics System - Emma Stanaway, Gabriela Magana, Zeynep Cansu
====================================================================

Description
-------------------------------------------------------------------------------------------------------------------
The Smart Campus Navigation and Facility Analytics System is a a C++ program that loads campus data from text files and lets a user locate facilities, explore building connections, find routes, browse a department hierarchy, and view summary reports.

The system uses several  data-structures to organize and retrieve information. These include:
A custom hash table for facility lookup by ID.
An undirected graph for campus buildings and walkways, including Breadth-First Search (BFS).
A general tree for the academic department hierarchy.

The program load information from the provided input files, validates the data, and allows users to access the system’s features through a menu.

Features
-------------------------------------------------------------------------------------------------------------------
View all facilities
Search facilities by ID using a custom hash table
View the campus graph
Display graph counts and degrees
Find reachable buildings using Breadth-First Search (BFS)
Add and search departments
Display the department hierarchy
Perform preorder traversal


Build Instructions
-------------------------------------------------------------------------------------------------------------------
In a Linux terminal, type “ g++ -Iinclude src/*.cpp ” to compile the project and create an executable.
In CLion IDE, ensure CMakeLists.txt from the repository is present and use the GUI (or Ctrl+F9) to build the project.


Run Instructions
-------------------------------------------------------------------------------------------------------------------
In a Linux terminal, type “ ./a.out “ to run the executable created by the g++ compiler.
In CLion IDE, ensure CMakeLists.txt from the repository is present and use the GUI (or Shift+F10) to run the project.


Directory Layout
-------------------------------------------------------------------------------------------------------------------

Project 2/
|
|——include/ Header files
|	|--CampusGraph.h
|	|--DepartmentTree.h
|	|--Facility.h
|	|--FacilityHashTable.h
|	|--FacilityManager.h
|——src/ Implementation files, including main.cpp
|	|--CampusGraph.cpp
|	|--DepartmentTree.cpp
|	|--Facility.cpp
|	|--FacilityHashTable.cpp
|	|--FacilityManager.cpp
|	|--main.cpp
|——data/ The four starter input files (unchanged)
|	|--buildings.txt
|	|--connections.txt
|	|--departments.txt
|	|--facilities.txt
|——testdata/ Your own test files
|——README.txt
|——CONTRIBUTIONS.txt
|——design_document.txt
|——test_results.txt
|——.gitignore


Input Data Files
-------------------------------------------------------------------------------------------------------------------
buildings.txt: Contains campus building records
connections.txt: Contains the connections between buildings
departments.txt: Contains department records
facilities.txt: Contains facility records
