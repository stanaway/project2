
#include "DepartmentTree.h"

#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// starts with an empty tree.
DepartmentTree::DepartmentTree()
{
    root = nullptr;
}

// releases all dynamically allocated nodes.
DepartmentTree::~DepartmentTree()
{
    deleteTree(root);
}

// Removes whitespace from the beginning and end of a string.
string DepartmentTree::trim(const string& str) const
{
    size_t first = 0;
    size_t last = str.length();

    while (first < last &&
           isspace(static_cast<unsigned char>(str[first])))
    {
        first++;
    }

    while (last > first &&
           isspace(static_cast<unsigned char>(str[last - 1])))
    {
        last--;
    }

    return str.substr(first, last - first);
}

// Converts a string to lowercase for case-insensitive comparisons.
string DepartmentTree::normalizeName(const string& name) const
{
    string result = name;

    for (size_t i = 0; i < result.length(); i++)
    {
        result[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

// Searches for a department by name.
DepartmentNode* DepartmentTree::findNode(
    const string& departmentName) const
{
    return findNodeRecursive(root, departmentName);
}

// Recursive helper used to search through the tree.
DepartmentNode* DepartmentTree::findNodeRecursive(
    DepartmentNode* current,
    const string& departmentName) const
{
    if (current == nullptr)
    {
        return nullptr;
    }

    if (normalizeName(current->name) ==
        normalizeName(departmentName))
    {
        return current;
    }

    for (DepartmentNode* child : current->children)
    {
        DepartmentNode* result =
            findNodeRecursive(child, departmentName);

        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr;
}

// Calculates how many levels a department is below the root.
int DepartmentTree::getDepth(DepartmentNode* node) const
{
    int depth = 0;

    while (node != nullptr && node->parent != nullptr)
    {
        depth++;
        node = node->parent;
    }

    return depth;
}

// Deletes a node and all of its children recursively.
void DepartmentTree::deleteTree(DepartmentNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    for (DepartmentNode* child : node->children)
    {
        deleteTree(child);
    }

    delete node;
}

// Loads departments from a text file.
void DepartmentTree::loadFromFile(
    const string& fileName,
    const string& displayFileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "ERROR: Could not open file: "
             << displayFileName << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line))
    {
        lineNumber++;

        // Ignore blank lines and comment lines.
        string cleanedLine = trim(line);

        if (cleanedLine.empty() || cleanedLine[0] == '#')
        {
            continue;
        }

        // Check that the line contains exactly one separator.
        size_t separator = cleanedLine.find('|');

        if (separator == string::npos)
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Missing '|' separator." << endl;
            continue;
        }

        size_t secondSeparator =
            cleanedLine.find('|', separator + 1);

        if (secondSeparator != string::npos)
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Extra fields found." << endl;
            continue;
        }

        // Separate department name and parent name.
        string departmentName =
            trim(cleanedLine.substr(0, separator));

        string parentName =
            trim(cleanedLine.substr(separator + 1));

        // Check for missing fields.
        if (departmentName.empty() || parentName.empty())
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Department name or parent name is empty."
                 << endl;
            continue;
        }

        // Check for duplicate department names.
        if (findNode(departmentName) != nullptr)
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Duplicate department name."
                 << endl;
            continue;
        }

        // The first accepted department must be the root.
        if (root == nullptr)
        {
            if (normalizeName(parentName) != "none")
            {
                rejected++;
                cout << "Warning: " << displayFileName
                     << ", line " << lineNumber
                     << ": The first department must have NONE as its parent."
                     << endl;
                continue;
            }

            root = new DepartmentNode(departmentName);
            accepted++;
            continue;
        }

        // Additional departments cannot have NONE as their parent.
        if (normalizeName(parentName) == "none")
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Only the root department can have NONE as its parent."
                 << endl;
            continue;
        }

        // The parent must already exist in the tree.
        DepartmentNode* parentNode = findNode(parentName);

        if (parentNode == nullptr)
        {
            rejected++;
            cout << "Warning: " << displayFileName
                 << ", line " << lineNumber
                 << ": Parent department does not exist."
                 << endl;
            continue;
        }

        // Create the new department and connect it to its parent.
        DepartmentNode* newNode =
            new DepartmentNode(departmentName);

        newNode->parent = parentNode;
        parentNode->children.push_back(newNode);

        accepted++;
    }

    file.close();

    // Display the loading summary.
    cout << "\n----- Department Loading Summary -----" << endl;
    cout << "Accepted Records: " << accepted << endl;
    cout << "Rejected Records: " << rejected << endl;
}

// Adds a new department to the tree.
bool DepartmentTree::addDepartment(
    const string& departmentName,
    const string& parentName,
    string& errorMessage)
{
    string cleanedName = trim(departmentName);
    string cleanedParent = trim(parentName);

    // Department name cannot be empty.
    if (cleanedName.empty())
    {
        errorMessage = "Department name cannot be empty.";
        return false;
    }

    // Check for duplicate department names.
    if (findNode(cleanedName) != nullptr)
    {
        errorMessage = "Department already exists.";
        return false;
    }

    // If the tree is empty, create the root.
    if (root == nullptr)
    {
        if (!cleanedParent.empty() &&
            normalizeName(cleanedParent) != "none")
        {
            errorMessage =
                "The first department must be the root.";
            return false;
        }

        root = new DepartmentNode(cleanedName);
        errorMessage = "";
        return true;
    }

    // A parent is required when the tree already has a root.
    if (cleanedParent.empty() ||
        normalizeName(cleanedParent) == "none")
    {
        errorMessage =
            "A valid parent department is required.";
        return false;
    }

    // Find the parent department.
    DepartmentNode* parentNode = findNode(cleanedParent);

    if (parentNode == nullptr)
    {
        errorMessage = "Parent department does not exist.";
        return false;
    }

    // Create and connect the new department.
    DepartmentNode* newNode =
        new DepartmentNode(cleanedName);

    newNode->parent = parentNode;
    parentNode->children.push_back(newNode);

    errorMessage = "";
    return true;
}

// Searches for a department and displays its information.
bool DepartmentTree::searchDepartment(
    const string& departmentName,
    ostream& output) const
{
    DepartmentNode* node = findNode(trim(departmentName));

    if (node == nullptr)
    {
        output << "Department not found." << endl;
        return false;
    }

    string parentName = "None";

    if (node->parent != nullptr)
    {
        parentName = node->parent->name;
    }

    output << "\n----- Department Information -----" << endl;
    output << "Department Name: " << node->name << endl;
    output << "Parent Department: " << parentName << endl;
    output << "Number of Direct Children: "
           << node->children.size() << endl;
    output << "Depth: " << getDepth(node) << endl;

    return true;
}

// Displays the department hierarchy recursively.
void DepartmentTree::displayHierarchyRecursive(
    DepartmentNode* current,
    int depth,
    ostream& output) const
{
    if (current == nullptr)
    {
        return;
    }

    // Four spaces for each level of depth.
    for (int i = 0; i < depth; i++)
    {
        output << "    ";
    }

    output << current->name << endl;

    // Display all children.
    for (DepartmentNode* child : current->children)
    {
        displayHierarchyRecursive(child, depth + 1, output);
    }
}

// Displays the complete department hierarchy.
void DepartmentTree::displayHierarchy(ostream& output) const
{
    if (root == nullptr)
    {
        output << "Department tree is empty." << endl;
        return;
    }

    output << "\n----- Department Hierarchy -----" << endl;

    displayHierarchyRecursive(root, 0, output);
}

// Performs preorder traversal recursively.
void DepartmentTree::preorderRecursive(
    DepartmentNode* current,
    ostream& output,
    bool& first) const
{
    if (current == nullptr)
    {
        return;
    }

    // Visit the current department first.
    if (!first)
    {
        output << " -> ";
    }

    output << current->name;
    first = false;

    // Then visit each child.
    for (DepartmentNode* child : current->children)
    {
        preorderRecursive(child, output, first);
    }
}

// Displays the preorder traversal.
void DepartmentTree::displayPreorder(ostream& output) const
{
    if (root == nullptr)
    {
        output << "Department tree is empty." << endl;
        return;
    }

    output << "\nPreorder Traversal: ";

    bool first = true;

    preorderRecursive(root, output, first);

    output << endl;
}

// Checks whether the department tree is empty or not.
bool DepartmentTree::isEmpty() const
{
    return root == nullptr;
}
