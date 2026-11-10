#include "Facility.h"
#include "FacilityManager.h"
#include "FacilityHashTable.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"
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
    DepartmentTree deptTree;
    CampusGraph campusGraph;

    facilityManager.loadFacilities("data/facilities.txt", facilityHTable);
    //load the other data files

    int choice = 0;

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

            case 3: //display campus graph
                campusGraph.displayGraph();
                break;

            case 4: //display cg counts and degrees
                campusGraph.displayCountsAndDegrees();
                break;

            case 5:
            {
                //bfs find reachanble buildings
                string startBuilding;
                cout << "Enter starting building name: ";
                getline(cin, startBuilding);
                if (startBuilding.empty()){
                    cout << "[ERROR] Building name cannot be empty." << endl;
                }
                else
                {
                    campusGraph.findReachable(startBuilding);
                }
                break;
            }

            case 6:
                break;

            case 7:
                break;

            case 8:
                break;

            case 9:
                break;

            case 10:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;

        }

    } while(choice != 10);

    return 0;


}
