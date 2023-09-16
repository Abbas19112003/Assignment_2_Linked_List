//2. Survival The Fittest.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Node structure for the linked list
struct SurvivalTheFittest {
    int value;
    SurvivalTheFittest* next;
};

// Class to calculate the median
class MedianCalculator {
private:
    SurvivalTheFittest* head;
    int count;

public:
    MedianCalculator() : head(nullptr), count(0) {}

    // Function to insert a value into the linked list
    void insert(int value) {
        SurvivalTheFittest* newSurvivalTheFittest = (SurvivalTheFittest*)malloc(sizeof(SurvivalTheFittest));
        newSurvivalTheFittest->next = nullptr;
        newSurvivalTheFittest->value = value;
        count++;

        if (!head) {
            head = newSurvivalTheFittest;
            return;
        }else if (value <= head->value){
            SurvivalTheFittest* current = head;
            head = newSurvivalTheFittest;
            head->next = current;
        }else{
            SurvivalTheFittest* previous = head;
            SurvivalTheFittest* current = head->next;
            while (current && current->value < value) {
                previous = current;
                current = current->next;
            }
            newSurvivalTheFittest->next = current;
            previous->next = newSurvivalTheFittest;
        
        }

        
    }

    // Function to find the median
    double findMedian() {
        SurvivalTheFittest* previous = nullptr;
        SurvivalTheFittest* current = head;

        for (int i = 0; i < count / 2; i++) {
            previous = current;
            current = current->next;
        }

        if (count % 2 == 0) {
            return (previous->value + current->value) / 2.0;
        } else {
            return current->value;
        }
    }
};

int organiseProgram(){
    MedianCalculator medianCalculator;
    
    cout << endl << endl << endl << "******************************************* Survival The Fittest ************************************************* " << endl << endl << endl;
    
    cout << "Enter which Testcase you want to access (1, 2, 3, 4, 5): \t\t";
    int tc;
    cin >> tc;
    cout << endl << endl;
    string tcn = to_string(tc);
    ifstream file ("02\\Test0" + tcn + ".txt");
    
    if(!file) {
        cerr << "Error opening file." << endl << endl;
        return 1;
    }

    string line;

    while (file >> line) 
    {
        int num = stoi(line);
        medianCalculator.insert(num);
        cout << medianCalculator.findMedian() << endl;
    }

    
    cout << endl << endl << endl;
    file.close();
    return 0;

}

int main() {
    
    system("Cls");
    organiseProgram();
    system("pause");
    system("Cls");

    return 0;
}
