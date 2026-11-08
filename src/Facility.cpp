#include "Facility.h"
#include <iostream>
#include <cctype>

using namespace std;


Facility::Facility(){
    facilityID = "";
    facilityName = "";
    buildingName = "";
    category = "";
}

Facility::Facility(const string& id, const string& name, const string& buildName, const string& categ){
    facilityID = id;
    facilityName = name;
    buildingName = buildName;
    category = categ;
}

string Facility::getFacilityID() const{
    return facilityID;
}

string Facility::getFacilityName() const{
    return facilityName;
}

string Facility::getBuildingName() const{
    return buildingName;
}

string Facility::getCategory() const{
    return category;
}



void Facility::setFacilityID(string& id){
    facilityID = id;
}

void Facility::display(){
    cout << "Facility ID: " << facilityID << endl;
    cout << "Facility Name: " << facilityName << endl;
    cout << "Building Name: " << buildingName << endl;
    cout << "Category: " << category << endl;
    cout << endl;

}
