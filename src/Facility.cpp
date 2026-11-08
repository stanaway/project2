#include "Facility.h"
#include <iostream>

using namespace std;


Facility::Facility(){
    facilityID = "";
    facilityName = "";
    buildingName = "";
    category = "";
}

Facility::Facility(string& id, string& name, string& buildName, string& categ){
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

}
