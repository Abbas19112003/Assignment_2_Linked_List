//Asignment_01.
//1. Retrieving The Trump.


#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


typedef struct Customer
{
    int customerNo;
    Customer* next;
    Customer* prev; 
}Customer;

int COUNT = 0;
Customer* firstMidCustomer = NULL;
Customer* secondMidCustomer = NULL;

Customer* firstCustomer = NULL;

//List of whole day customers.
void listOfCustomers(int customerNo){
    COUNT ++;
    Customer* temp = (Customer*)malloc(sizeof (Customer));
    temp -> customerNo = customerNo;

    if (firstCustomer == NULL){
        firstCustomer = temp;
        firstCustomer->prev = NULL;
        firstCustomer->next = NULL;
    }else{
        Customer* curr = firstCustomer;
        while (curr->next != NULL){
            curr = curr->next;
        }
        temp->prev = curr;
        temp->next = NULL;
        curr->next = temp;

    }
}


// To maintain mid.
void setMidCustomer(bool button){ 
    if (firstMidCustomer == NULL && button){
        firstMidCustomer = firstCustomer;
    }else if (firstMidCustomer != NULL && button){
        if  (COUNT % 2 != 0){
            firstMidCustomer = secondMidCustomer;
        }
        else{
             
            secondMidCustomer = firstMidCustomer->next;
            }

    }else if (COUNT % 2 == 0 && !button && COUNT != 0){
        
        secondMidCustomer = firstMidCustomer;
       firstMidCustomer = firstMidCustomer->prev;

    }
   
}

//For deleting customer.
void deleteCustomer(){
    if (COUNT != 0){
        COUNT --;
    }
    Customer *curr;
    if (firstCustomer == NULL){
        
    }
    else if (firstCustomer->next == NULL){
        curr = firstCustomer;
        firstCustomer = NULL;
        firstMidCustomer = NULL;
        free (curr);
    }
    else{
        curr = firstCustomer->next;
        Customer *prev = firstCustomer;

        while (curr->next != NULL )
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(curr);
        
    }
}

//to read data and organise.
int readDataFromFile(){
    cout << "Enter which Testcase you want to access (1, 2, 3, 4, 5): \t\t";
    int tc;
    cin >> tc;
    cout << endl << endl;
    string tcn = to_string(tc);
    ifstream file ("01\\Test0" + tcn + ".txt");
    
    if(!file) {
        cerr << "Error opening file." << endl << endl;
        return 1;
    }
    int customerNo;
    bool button;
    string cursor;
    file >> cursor;
    
    while(cursor != "END"){
        if (cursor == "ADD"){
            button = true;
            file >> cursor;
            customerNo = stoi(cursor);
            listOfCustomers(customerNo);
           setMidCustomer(button);
        }else if(cursor == "DELETE"){
            button = false;
            deleteCustomer();
            setMidCustomer(button);
        }
        file >> cursor;
        
    }   
    return 0;
}

void winnerAnnouncement(){
    if (COUNT % 2 != 0){
    cout << endl << endl << "The Winner of the day is Customer no: " << firstMidCustomer->customerNo << "." << endl << endl;
    }else{
        cout << endl << endl << "The Winner of the day are Customer no: " << firstMidCustomer->customerNo << " and " << secondMidCustomer->customerNo << endl << endl;
    }

}

//Function for printing the complete customer list.
void printAllCustomerList(){
        if (firstCustomer == NULL){
            cout << endl << "Customer List is empty" << endl << endl;
        }else{
            Customer* curr = firstCustomer;
            cout << endl << endl << "Here is the complete customer list:" << endl << endl;
            while (curr != NULL)
            {
                cout << endl << curr->customerNo << "\n";
                curr = curr->next; 
            }
            cout << endl << endl;
        }
}



//MAIN PROGRAM.
int main(){

    system("cls");

    cout << endl << endl << endl << "\t\t\t\t******************************************* Retrieving The Trump!! ************************************************* " << endl << endl << endl;
    
    readDataFromFile();
    printAllCustomerList();
    winnerAnnouncement();



    cout << endl << endl;
    system("pause");
    system ("cls");
    return 0;
}