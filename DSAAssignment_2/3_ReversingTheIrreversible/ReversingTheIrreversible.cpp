//3.Reversing The irreversible.
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct ReversingTheIrreversible {
    int id;
    int amount;
    ReversingTheIrreversible* next;
};

class TransactionList {
public:
    ReversingTheIrreversible* head;

    TransactionList() : head(nullptr) {}

    void insert(int id, int amount) {
        ReversingTheIrreversible* temp = new ReversingTheIrreversible;
        temp->next = nullptr;
        temp->id = id;
        temp->amount = amount;

        if (!head) {
            head = temp;
        } else {
            ReversingTheIrreversible* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = temp;
        }
    }

    void remove(int Id) {
        if (head->id == Id) {
            ReversingTheIrreversible* curr = head;
            head = head->next;
            delete curr;
        } else {
            ReversingTheIrreversible* prev = head;
            ReversingTheIrreversible* curr = head->next;
            while (curr != nullptr) {
                if (curr->id == Id) {
                    prev->next = curr->next;
                    delete curr;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }

    void display() {
        ReversingTheIrreversible* current = head;
        while (current != nullptr) {
            cout << current->id << "," << current->amount << endl;
            current = current->next;
        }
    }

    ~TransactionList() {
        while (head != nullptr) {
            ReversingTheIrreversible* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TransactionList transactions;
    system("cls");

    cout << endl << endl << endl << "\t\t\t\t******************************************* Reversing The Irreversible!! ************************************************* " << endl << endl << endl;
    

    cout << "Enter which Testcase you want to access (1, 2, 3, 4, 5): \t\t";
    int tc;
    cin >> tc;
    cout << endl << endl;
    string tcn = to_string(tc);
    ifstream file ("03\\Test0" + tcn + ".txt");
    
    if(!file) {
        cerr << "Error opening file." << endl << endl;
        return 1;
    }


    int numberOfTransactions, numberOfFraudulentTransactions;
    file >> numberOfTransactions >> numberOfFraudulentTransactions;

    string line;
    getline(file, line);

    for (int i = 0; i < numberOfTransactions; ++i) {
        getline(file, line);
        stringstream ss(line);
        int transactionId, transactionAmount;
        char comma;
        ss >> transactionId >> comma >> transactionAmount;
        transactions.insert(transactionId, transactionAmount);
    }

    for (int i = 0; i < numberOfFraudulentTransactions; ++i) {
        int fraudulentId;
        file >> fraudulentId;
        transactions.remove(fraudulentId);
    }

    file.close();

    cout << "Transactions after Reversing Fraudulent Transactions:" << endl;
    transactions.display();

    cout << endl << endl;
    system ("pause");
    system ("Cls");

    return 0;
}
