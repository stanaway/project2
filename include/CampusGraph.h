#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
using namespace std;

//  a building and its adjacent neighbors
struct BuildingNode
{
    string name;
    vector<string> neighbors;
};

//  undirected campus graph
class CampusGraph
{
    private:
        vector<BuildingNode> buildings;
        int connectionCount;

        int findBuildingIndex(const string& name) const;    //returns index of building by name, or -1

    public:
        CampusGraph();  //constructor

        void loadBuildings(const string& fileName, const string& displayFileName = "buildings.txt");    //file loading for buildings.txt
        void loadConnections(const string& fileName, const string& displayFileName = "connections.txt");    //file loadding for connections.txt

        bool addBuilding(const string& buildingName);   //adds building
        bool addConnection(const string& buildingA, const string& buildingB);   //adds connection between 2 buildings

        void displayGraph() const;  //for displaying each building and neighbors
        void displayCountsAndDegrees() const;   //for displaing degrees and connections
        void findReachable(const string& startName) const;  //bfs
};

#endif