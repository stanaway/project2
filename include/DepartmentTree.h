#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H


#include <string>
#include <vector>
#include <iostream>


using namespace std;


struct DepartmentNode
{
    string name;
    DepartmentNode* parent;
    vector<DepartmentNode*> children;


    DepartmentNode(const string& departmentName)
    {
        name = departmentName;
        parent = nullptr;
    }
};


// Manages the department hierarchy and its operations.
class DepartmentTree
{
private:
    DepartmentNode* root;


    // Removes whitespace from the beginning and end of a string.
    string trim(const string& str) const;


    // Converts a name to lowercase for case-insensitive comparisons.
    string normalizeName(const string& name) const;


    // Uses names to find a deparment
    DepartmentNode* findNode(const string& departmentName) const;


    // helper for searching the tree.
    DepartmentNode* findNodeRecursive(
        DepartmentNode* current,
        const string& departmentName) const;


    // Displays the hierarchy recursively.
    void displayHierarchyRecursive(
        DepartmentNode* current,
        int depth,
        ostream& output) const;


    // Performs preorder traversal recursively.
    void preorderRecursive(
        DepartmentNode* current,
        ostream& output,
        bool& first) const;


    // Calculates the depth of a department.
    int getDepth(DepartmentNode* node) const;


    // Releases dynamically allocated nodes.
    void deleteTree(DepartmentNode* node);


public:
    // Constructor and destructor.
    DepartmentTree();
    ~DepartmentTree();


    // Prevents copying of a tree that owns dynamically allocated nodes.
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;


    // Loads department records from a file.
    void loadFromFile(
        const string& fileName,
        const string& displayFileName = "departments.txt");


    // Adds a department to the tree.
    bool addDepartment(
        const string& departmentName,
        const string& parentName,
        string& errorMessage);


    // Searches for a department and displays its information.
    bool searchDepartment(
        const string& departmentName,
        ostream& output = cout) const;


    // Displays the complete department hierarchy.
    void displayHierarchy(ostream& output = cout) const;


    // Displays the preorder traversal.
    void displayPreorder(ostream& output = cout) const;


    // Checks whether the tree is empty or not.
    bool isEmpty() const;
};


#endif
