//5. As The Method Of Third.
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct asTheMethodOfThird {
    int data;
    asTheMethodOfThird* next;
    asTheMethodOfThird(int value) : data(value), next(nullptr) {}
};

int findThirdLastElement(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return -1;
    }

    asTheMethodOfThird* head = nullptr;
    int length = 0;

    // Read data from the input file and create a linked list
    int num;
    while (inputFile >> num) {
        asTheMethodOfThird* newasTheMethodOfThird = new asTheMethodOfThird(num);
        if (head == nullptr) {
            head = newasTheMethodOfThird;
        } else {
            asTheMethodOfThird* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newasTheMethodOfThird;
        }
        length++;
    }

    inputFile.close();

    // Check if the length of the linked list is less than 3
    if (length < 3) {
        return -1;
    }

    // Traverse the linked list to find the third last element
    asTheMethodOfThird* current = head;
    for (int i = 0; i < length - 3; i++) {
        current = current->next;
    }

    int thirdLastElement = current->data;

    // Clean up memory by deleting the linked list
    while (head != nullptr) {
        asTheMethodOfThird* temp = head;
        head = head->next;
        delete temp;
    }

    return thirdLastElement;
}

int main() {

    system("cls");

    cout << endl << endl << endl << "\t\t\t\t******************************************* As The Method Of Third!! ************************************************* " << endl << endl << endl;
    


    cout << "Enter which Testcase you want to access (1, 2, 3, 4, 5): \t\t";
    int tc;
    cin >> tc;
    cout << endl << endl;
    string tcn = to_string(tc);
    string filename = ("05\\Test0" + tcn + ".txt"); 



    int result = findThirdLastElement(filename);
    if (result != -1) {
        cout << result << endl;
    } else {
        cout << -1 << endl;
    }


    cout << endl << endl;
    system ("pause");
    system ("Cls");
    return 0;
}
