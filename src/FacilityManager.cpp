#include "FacilityManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;


string FacilityManager::eraseWhiteSpace(const string& str){
    size_t first = 0;
    size_t last = str.length();

    while(first < last && isspace(static_cast<unsigned char>(str[first]))){//starts from the index 0 and checks if the character it is at is a whitespace or not. it goes through the whole string until it reaches a char
        first++;
    }

    while(last > first && isspace(static_cast<unsigned char>(str[last - 1]))){//same thing as the previous loop but starts at the last index and works its way backwards
        last--;
    }

    return str.substr(first, last - first);// extracts the string parts of the string (without the whitespaces)

}

void FacilityManager::loadFacilities(const string& facilitiesFile, FacilityHashTable& hashTable){
    ifstream file(facilitiesFile);
    
    if(!file.is_open()){
        cout << "ERROR: Could not open file!" << endl;
        return;
    }

    string line;
    int lineNum = 0;

    int accepted = 0;
    int rejected = 0;

    while(getline(file, line)){
        lineNum++;
        if(lineNum == 1){
            continue;
        }
        line = eraseWhiteSpace(line);

        if(line.empty() || line[0] == '#'){//if there is an empty line or the line is a comment, skip it
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string building;
        string category;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, building, '|');
        getline(ss, category, '|');

        string extraFields;
        if(getline(ss, extraFields, '|')){
            rejected++;
            cout << "Error in " << facilitiesFile << ", line " << lineNum << ": There are extra fields." << endl;
            continue;
        }

        id = eraseWhiteSpace(id);
        name = eraseWhiteSpace(name);
        building = eraseWhiteSpace(building);
        category = eraseWhiteSpace(category);

        if(id.empty() || name.empty() || building.empty() || category.empty()){
            rejected++;
            cout << "Error in " << facilitiesFile << ", line " << lineNum << ": Missing a required field." << endl;
            continue;
        }

        if(!hashTable.isValidID(id)){
            rejected++;
            cout << "Error in " << facilitiesFile << ", line " << lineNum << ": Invalid Facility ID." << endl;
            continue;


        }


        Facility facility(id, name, building, category);
        if(hashTable.insert(facility)){
            accepted++;
        }
        else{
            rejected++;
            cout << "Error in " << facilitiesFile << ", line " << lineNum << ": Duplicate Facility ID." << endl;
            continue;
        }


    }

    cout << "\n ----- Accepted and Rejected Records -----" << endl;
    cout << "Accepted Records: " << accepted << endl;
    cout << "Rejected Records: " << rejected << endl;
}
