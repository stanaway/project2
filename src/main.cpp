#include "Facility.h"
#include "FacilityManager.h"
#include "FacilityHashTable.h"
//#include "CampusGraph.h"
//#include "DepartmentTree.h"

#include <iostream>
#include <string>

using namespace std;

void displayMenu(){


    cout << "---------------------------- Smart Campus Navigation and Facility Analytics System ----------------------------" << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" << endl;
    cout << "4. Display graph counts and degrees" << endl;
    cout << "5. Find reachable buildings (BFS)" << endl;
    cout << "6. Add department" << endl;
    cout << "7. Search department" << endl;
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "10. Exit" << endl;


}

int main(){

    FacilityHashTable facilityHTable;
    FacilityManager facilityManager;
    //create DepartmentTree object
    //create CampusGraph object

    facilityManager.loadFacilities("data/facilities.txt", facilityHTable);
    //load the other data files

    int choice;

    do{
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                facilityHTable.displayAll();
                break;

            case 2:{
                string id;
                cout << "Enter Facility ID: ";
                cin >> id;

                Facility* result = facilityHTable.search(id);

                if(result != nullptr){
                    result->display();
                }
                else{
                    cout << "Facility ID not found!" << endl;
                }
                break;
            }

            case 3:

            case 4:

            case 5:

            case 6:

            case 7:

            case 8:

            case 9:

            case 10:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;

        }

    } while(choice != 10);

    return 0;


}
