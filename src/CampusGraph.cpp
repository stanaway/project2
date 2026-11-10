#include "CampusGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cctype>
using namespace std;

//function to remove leading and trailing whitespace
static string trimWhitespace(const string& str)
{
    size_t first = 0;
    size_t last = str.length();

    while (first < last && isspace(static_cast<unsigned char>(str[first])))
    {
        first ++;
    }
    while (last > first && isspace(static_cast<unsigned char>(str[last - 1])))
    {
        last--;
    }
    return str.substr(first, last - first);
}

//function that comverts string to lowercase
static string toLower(const string& str)
{
    string cleaned = trimWhitespace(str);
    for (char& c : cleaned)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return cleaned;
}

//constructor
CampusGraph::CampusGraph()
{
    connectionCount = 0;    //initializes connection count to 0
}

//loads buildings from buildings.txt
void CampusGraph::loadBuildings(const string& fileName, const string& displayFileName)
{
    ifstream file(fileName);

    if (!file.is_open())    //if no file
    {
        cout << "[ERROR] Could not open buildings file." << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    //read file
    while (getline(file, line))
    {
        lineNumber++;
        string cleanedLine = trimWhitespace(line);

        if (cleanedLine.empty() || cleanedLine == "#")  //if line empty or comment
        {
            continue;
        }

        if (findBuildingIndex(cleanedLine) != -1)   //if already present in buildings
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Duplicate building name." << endl;
            continue;
        }

        if (addBuilding(cleanedLine))
        {
            accepted++;
        }
        else//if invalid
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Invalid building name." << endl;
        }
    }

    file.close();

    cout << "\n------ BUILDING LOADING SUMMARY ------" << endl;
    cout << "Accepted records: " << accepted << endl;
    cout << "Rejected records: " << rejected << endl;
}

//loads connections from connections.txt
void CampusGraph::loadConnections(const string& fileName, const string& displayFileName)
{
    ifstream file(fileName);

    if (!file.is_open())    //if no file
    {
        cout << "[ERROR] Could not open connections file." << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line))
    {
        lineNumber++;
        string cleanedLine = trimWhitespace(line);

        if (cleanedLine.empty() || cleanedLine == "#")  //if line empty or comment
        {
            continue;
        }

        size_t separator = cleanedLine.find('|');
        if (separator == string::npos)  //if error finding separator
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Missing '|' separator." << endl;
            continue;
        }

        size_t secondSeparator = cleanedLine.find('|', separator + 1);
        if (secondSeparator != string::npos) //if another separator in line found
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Extra fields found!" << endl;
            continue;
        }

        string buildingA = trimWhitespace(cleanedLine.substr(0, separator));
        string buildingB = trimWhitespace(cleanedLine.substr(separator + 1));

        if (buildingA.empty() || buildingB.empty()) //compare strings
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Building name cannot be empty!" << endl;
            continue;
        }

        if (addConnection(buildingA, buildingB))
        {
            accepted++;
        }
        else
        {
            rejected++;
            cout << "[WARNING] " << displayFileName << ", line " << lineNumber << ": Failed to add connection." << endl;
        }
    }

    file.close();

    cout << "\n------ CONNECTION LOADING SUMMARY  ------" << endl;
    cout << "Accepted Records: " << accepted << endl;
    cout << "Rejected records: " << rejected << endl;
}

//returns index of building searched by case insensitive name, or -1 if not found
int CampusGraph::findBuildingIndex(const string& name) const
{
    string target = toLower(name);

    for (size_t i = 0; i < buildings.size(); i++)
    {
        if (toLower(buildings[i].name) == target)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

//adds building to vector, if not empty and not duplicate
bool CampusGraph::addBuilding(const string& buildingName)
{
    string cleanedName = trimWhitespace(buildingName);

    if (cleanedName.empty())
    {
        return false;   //return false if empty
    }

    if (findBuildingIndex(cleanedName) != -1)
    {
        return false;   //return false if duplicate
    }

    BuildingNode newNode;
    newNode.name = cleanedName;
    buildings.push_back(newNode);   //add new node to buildings vector

    return true;    //return true if successful
}

//adds connection between two valid buildings
bool CampusGraph::addConnection(const string& buildingA, const string& buildingB)
{
    int indexA = findBuildingIndex(buildingA);
    int indexB = findBuildingIndex(buildingB);

    if (indexA == -1 || indexB == -1 || indexA == indexB)
    {
        return false;   //returns false to reject invalid or if both are the same
    }

    //checks for duplicates already in neighbor vector
    string targetB = toLower(buildings[indexB].name);
    for (const string& neighbor : buildings[indexA].neighbors)
    {
        if (toLower(neighbor) == targetB)
        {
            return false;   //returns false if duplicate found
        }
    }

    //adds building name to each others adjacency lists
    buildings[indexA].neighbors.push_back(buildings[indexB].name);
    buildings[indexB].neighbors.push_back(buildings[indexA].name);
    connectionCount++;  //and increases connection count of campusgraph object

    return true;    //returns true if successful
}

//displays each building and vectors, with loops, checking if empty first
void CampusGraph::displayGraph() const
{
    if (buildings.empty())
    {
        cout << "Campus graph is empty." << endl;
        return;     //returns early if empty, no loop iterations needed
    }

    cout << "\n ------ CAMPUS GRAPH ------" << endl;

    for (size_t i = 0; i < buildings.size(); ++i)   //loops through buildings
    {
        cout << buildings[i].name << ": ";
        if (buildings[i].neighbors.empty())
        {
            cout << "[NO CONNECTIONS]";     //no connections if neighbors is empty
        }
        else
        {
            for (size_t j = 0; j < buildings[i].neighbors.size(); ++j)  //loops through neighbors of current building
            {
                cout << buildings[i].neighbors[j];  //prints connections

                if (j + 1 < buildings[i].neighbors.size())
                {
                    cout << ", ";   //if not last
                }
            }
        }
        cout << endl;
    }
}

//displays counts and degrees of graph, using loop, checking if empty firsst
void CampusGraph::displayCountsAndDegrees() const
{
    if (buildings.empty())
    {
        cout << "Campus graph is empty!" << endl;
        return;     //returns early if empty, no loop iterations needed
    }

    cout << "------ GRAPH COUNTS AND DEGREES ------" << endl;

    for (size_t i = 0; i < buildings.size(); i++)   //loops through buildings
    {
        cout << buildings[i].name << " | DEGREE: " << buildings[i].neighbors.size() << endl;    //print degree of each
    }

    cout << "\nTOTAL BUILDINGS: " << buildings.size() << endl;  //print size of buildings vector
    cout << "TOTAL CONNECTIONS: " << connectionCount << endl;   //prints conenctioncount int
}

//bfs search in graph, to display all reachable buildings also connection dist
void CampusGraph::findReachable(const string& startName) const
{
    int startIndex = findBuildingIndex(startName);
    if (startIndex == -1)
    {
        cout << "[ERROR] Building " << startName << " not found in graph." << endl;
        return;     //exit early if invalid input
    }

    vector<bool> visited(buildings.size(), false);  //create vector of booleans, to track if visited yet
    vector<int> distance(buildings.size(), 0);      //create vector of ints, to track distance
    queue<int> q;   //create queue of ints to hold indices

    //begin w startindex
    visited[startIndex] = true;
    q.push(startIndex);

    cout << "\n------ REACHABLE BUILDINGS (B.F.S. FROM " << buildings[startIndex].name << ") ------" << endl;
    int reachableCount = 0; //counter

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        reachableCount++;   //increment

        cout << buildings[cur].name << " (distance " << distance[cur] << ")" << endl;

        for (const string& neighbor : buildings[cur].neighbors)
        {
            int nIndex = findBuildingIndex(neighbor);
            if (nIndex != -1 && !visited[nIndex])   //if valid and unvisited index
            {
                visited[nIndex] = true; //mark as visited
                distance[nIndex] = distance[cur] + 1;   //distance is current dist + 1
                q.push(nIndex); //push unvisited neighbor to queue
            }
        }
    }

    cout << "Reachable: " << reachableCount << " of " << buildings.size() << " buildings." << endl; //print reachable info
}
