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
        Facility(string& id, string& name, string& buildName, string& categ);
        
        string getFacilityID() const;
        string getFacilityName() const;
        string getBuildingName() const;
        string getCategory() const;

        void setFacilityID(string& id);

        void display();
};

#endif
