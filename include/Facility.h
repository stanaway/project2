#ifndef FACILITY_H
#define FACILITY_H

#include <string>
using namespace std;

class Facility{
    private:
        string facilityID;
        string facilityName;
        string buildingName;
        string category;

    public:
        Facility();
        Facility(const string& id, const string& name, const string& buildName, const string& categ);
        
        string getFacilityID() const;
        string getFacilityName() const;
        string getBuildingName() const;
        string getCategory() const;

        void setFacilityID(string& id);

        void display();
};

#endif
