#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include "FacilityHashTable.h"
#include <string>

using namespace std;

class FacilityManager{
    public:
        string eraseWhiteSpace(const string& str);
        void loadFacilities(const string& facilitiesFile, FacilityHashTable& hashTable);
};


#endif
