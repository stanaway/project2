#include "FacilityHashTable.h"
#include "Facility.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <string>


using namespace std;


FacilityHashTable::FacilityHashTable(){
    capacity = 15;
    entryCount = 0;
    collisionCount = 0;

    buckets.resize(15, nullptr);

}

size_t FacilityHashTable::hashFunction(const string& id){
    string input = id;
    string numPart = "";

    for(char c : input){//extracts the numerical part char by char
        if(isdigit(c)){
            numPart += c;
        }
    }

    int num = stoi(numPart); //converts the numerical part to integer

    int bucketIndex = num % capacity;

    return bucketIndex;


}

FacilityHashTable::~FacilityHashTable(){

    for(int i = 0; i < capacity; i++){
        Node* curr = buckets[i];

        while(curr != nullptr){
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

}

bool FacilityHashTable::insert(const Facility& facility){
    string id = facility.getFacilityID();

    if(!isValidID(id)){
        return false;
    }

    for(char& c : id){
        c = toupper(static_cast<unsigned char> (c)); //avoids negative char values
    }

    Facility newFacility = facility;
    newFacility.setFacilityID(id);
    
    

    if(search(id) != nullptr){//if a duplicate is found -> return false
        return false;
    }

    size_t bucketIndex = hashFunction(id);
    if(buckets[bucketIndex] != nullptr){//if bucket is occupied, increment collisionCount
        collisionCount++;
    }



    facilities.push_back(newFacility); //preserves the order in which the facilities are inserted
    
    Node* newNode = new Node(facilities.size() - 1);
    newNode->next = buckets[bucketIndex]; //points to the current first node
    buckets[bucketIndex] = newNode; //bucket points to the newNode

    entryCount++;
    return true;


}

Facility* FacilityHashTable::search(const string& id){
    string searchID = id;

    for(char& c : searchID){
        c = toupper(static_cast<unsigned char> (c)); //avoids negative char values
    }

    size_t bucketIndex = hashFunction(searchID);
    Node* curr = buckets[bucketIndex];

    while(curr != nullptr){
        Facility* currFacility = &facilities[curr->facilityIndex]; //finds the actual Facility object in the vector and creates a pointer and points to it

        if(currFacility->getFacilityID() == searchID){
            return currFacility;
        }
        else{
            curr = curr->next;
        }
    }

    return nullptr;
}

bool FacilityHashTable::isValidID(const string& id){
    if(id.length() != 4){//returns false if id length is not 4
        return false;
    }
    
    if(toupper(static_cast<unsigned char>(id[0])) != 'F'){//returns false if the first char of the id is not 'F'
        return false;
    }

    for(int i = 1; i < 4; i++){//loops through the numerical part of the id
        if(!isdigit(static_cast<unsigned char>(id[i]))){//returns false if the 1st, 2nd, and 3rd char of the id is not numbers
            return false;
        }
    }

    return true;
}

void FacilityHashTable::displayAll(){
    for(size_t i = 0; i < facilities.size(); i++){
        facilities[i].display();
    }

}

void FacilityHashTable::displayDiagnostics(){

    cout << "Hash Table Capacity: " << capacity << endl;
    cout << "Number of Entries: " << entryCount << endl;
    cout << "Number of Collisions: " << collisionCount << endl;


}
