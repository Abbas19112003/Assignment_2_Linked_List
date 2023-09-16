#include <iostream>
#include "TheEditor.h"
using namespace std;



//Main program
int main() {
    system("cls");
    system("Cls");
    cout << endl << endl;
    cout << "****************************************************** The Editor ******************************************************";
    cout << endl << endl;
    
    TheEditor editor;

    //File operations.
    cout << "Enter which Testcase you want to access (1, 2, 3, 4, 5): \t\t";
    int tc;
    cin >> tc;
    cout << endl << endl;
    string tcn = to_string(tc);
    ifstream inputFile("04\\Test0" + tcn + ".txt");
    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string operation;
        ss >> operation;

        
    if (operation == "Add") {
            editor.state = true;
            int value;
            ss >> value;
        if (ss.fail()) {
            cout << "Invalid operation format: " << line << endl;
            continue;
        }

        int index = -1; // Default index is -1 (end of the list)

        // Check if there is an additional index provided
        if (ss >> index) {
            // The input contains an index, so insert the value at the specified index
            editor.insertAtIndex(value, index);
        } else {
            // No additional index provided, insert the value at the end of the list
            editor.insertInLinkedList(value);
        }
        editor.printAllLinkedList();
        } else if (operation == "Print") {
            editor.printCursorNodeValue();
        } else if (operation == "Delete") {
             editor.state = true;

            int index;
            // Check if there is an index specified
            if (ss >> index) {
                editor.deleteANumberFromIndex(index);
            } else {
                editor.deleteTail();
            }
            editor.printAllLinkedList();
        } else if (operation == "Undo") {
            editor.undo();
            editor.printAllLinkedList();
        } else if (operation == "MoveForward") {
            int steps;
            ss >> steps;
            editor.moveCursorForward(steps);
        } else if (operation == "MoveBackward") {
            int steps;
            ss >> steps;
            editor.moveCursorBackward(steps);
        } else if (operation == "AddImmediate") {
             editor.state = true;
            int value;
            ss >> value;
            editor.insertImmediateValue(value);
            editor.printAllLinkedList();
        } else if (operation == "Update") {
             editor.state = true;
            int index, value;
            ss >> index >> value;
            editor.updateIndexNumber(index, value);
            editor.printAllLinkedList();
        } else if (operation == "DeleteImmediate"){
             editor.state = true;
            editor.deleteImmediateValue();
            editor.printAllLinkedList();
        } else if (operation == "UpdateImmediate"){
             editor.state = true;
            int value;
            ss >> value;
            editor.updateImmediateNumber(value);
            editor.printAllLinkedList();
        } else if (operation == "Shift"){
             editor.state = true;
            int index;
            ss >> index;
            editor.shiftIndex(index);
            editor.printAllLinkedList();
        }
        else {
            cout << "Unknown operation: " << operation << endl;
        }
    }

    editor.toDeleteAllNode();
    cout << endl << endl;
    inputFile.close();

    system("pause");
    system("Cls");
    return 0;
}




