#include <iostream>
#include <cstdlib>

using namespace std;


//Stack.
class Stack {
public:
    enum OperationType {
        INSERTION,
        DELETION,
        UPDATION,
        DOUBLEUPDATION,
        DELETIONALL
    };

    int value;
    Stack* next;
    Stack* Snext;
    OperationType type;
    int position;

    Stack(int val, OperationType type , int pos) : value(val), next(nullptr), Snext(nullptr), type(type), position(pos) {}
};


//Class to handle stack operations.
class StackManager {
private:
    Stack* top;
    Stack* start;
    const int max_size;

public:
    int size;
    int Value;
    int position;
    Stack::OperationType type;

    StackManager() : top(nullptr), start(nullptr) , size(0), max_size(6) {}

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == max_size;
    }

    //1. Push data in stack.
    void push(int value, Stack::OperationType type, int pos) {
        if (!isFull()) {
            Stack* newNode = new Stack(value , type , pos);
            newNode->next = top;
            top = newNode;
            if (!start){
                start = newNode;
                newNode->Snext = nullptr;
            }else{
                Stack* curr = start;
                while (curr->Snext != nullptr)
                {
                    curr = curr->Snext;
                }
                curr->Snext = newNode;
                newNode->Snext = nullptr;
                
            }
            size++;
        } else {
            cout << "<Stack Overflow!!>" << endl;
        }
    }


    //2. Pop data of stack.
    void pop() {
        if (!isEmpty()) {
            Value = top->value;
            type = top->type;
            position = top->position;
            Stack* temp = top;
            top = top->next;
            if(!top){
                start = nullptr;
            }else{
                top->Snext = nullptr;
            }
            
            delete temp;
            size--;
        } else {
            cout << "<Stack Underflow!!>" << endl;
        }
    }


    //3. Reverse pop data of stack.
    void reversePop() {
        if (!isEmpty()) {
            Stack* temp = start;
            if (start->Snext != nullptr) {
                start = start->Snext;
                start->next = nullptr;
            } else {
                start = nullptr; 
            }
            delete temp;
            size--;
        } else {
            cout << "<Stack Underflow!!>" << endl;
        }
    }



    //To delete all.
    void toDeleteAllStack(){
        Stack* curr;
        while (start != NULL){
            curr = start;
            start = start->Snext;
            free(curr);
        }
    }



};