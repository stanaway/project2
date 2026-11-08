#ifndef FACILITYHASHTABLE_H
#define FACILITYHASHTABLE_H

#include "Facility.h"
#include <cstddef>
#include <vector>
using namespace std;


class FacilityHashTable{
    private:

        int capacity;
        int entryCount;
        int collisionCount;

        size_t hashFunction(const string& id);

        struct Node{
            size_t facilityIndex;
            Node* next;

            Node(size_t index){
                facilityIndex = index;
                next = nullptr;
            }

        };

        vector<Node*> buckets;
        vector<Facility> facilities;


    public:
        FacilityHashTable();
        ~FacilityHashTable();
        bool insert(const Facility& facility);
        Facility* search(const string& id);

        void displayAll();
        void displayDiagnostics();


};

#endif
