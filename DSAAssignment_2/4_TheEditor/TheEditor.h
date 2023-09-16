#include "MyStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

//Main linked list.
typedef struct node
{
    int value;
    int index;
    struct node* next;
    struct node* prev; 
}node;


//Editor class to handle all editor functions.
class TheEditor{
    
    private:
    node* start = NULL;
    node* cursor = NULL;
    int COUNT = -1;
    int count = 0;
    StackManager stack;

    public:
    bool state = true;

    //1. Function for insert in linked list at tail.
    void insertInLinkedList(int value){
        COUNT ++;
        node* temp = (node*)malloc(sizeof (node));
        temp->next = NULL;
        temp->value = value;
        temp->index = COUNT;
        if (start == NULL){
            start = temp;
            temp->prev = NULL;
            cursor = start;

        }else{
            node* curr = start;
            while (curr->next != NULL){
                curr = curr->next;
            }
            temp->prev = curr;
            curr->next = temp;
            count++;
        }
        if (stack.size <= 5 && state){
            stack.push(value , Stack::INSERTION , COUNT);
        }else if (stack.size > 5 && state){
            stack.reversePop();
            stack.push(value , Stack::INSERTION , COUNT);


        }
    }


    //2. Function for delete node tail.
    void deleteTail(){
        if (COUNT != -1){
            COUNT --;
        }
        if (start == NULL){
            cout << endl << endl << "Invalid!!" << endl << endl;
        }
        else if (start->next == NULL){

            if (stack.size <= 5 && state){
                stack.push(start->value , Stack::DELETION , count);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(start->value , Stack::DELETION , count);
            }

            free(start);
            count--;
            start = NULL;
            cursor = NULL;
            
        }
        else{
            node *curr = start->next;

            while (curr->next != NULL )
            {
                curr = curr->next;
            }
            curr->prev->next = NULL;

            if (stack.size <= 5 && state){
                stack.push(curr->value , Stack::DELETION , count);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(curr->value , Stack::DELETION , count);
            }

            free(curr);
            count--;
        }
    }

    //3. Function to add number at specific index;
    void insertAtIndex(int index , int value){
        

        if(COUNT == -1 && index != 0){
            cout << endl << "Invalid!!" << endl;
        } else if (index > COUNT + 1){
            cout << endl << "Invalid!!" << endl;
        }
        else{
        
            
            if (index == 0){
                node* temp = (node*)malloc(sizeof (node));
                temp->value = value;
                if (cursor->index == index){
                    cursor = temp;
                }
                if (start != NULL){
            
                    temp->next = start;
                    start->prev = temp;
                    temp->prev = NULL;
                    temp->index = index;
                    start = temp;
                    COUNT ++;
                    node * curr = start->next;
                    while(curr != NULL){
                        curr->index = curr->index + 1;
                        curr = curr->next;
                    }


                }else{
                    temp->prev = NULL;
                    temp->next = NULL;
                    temp->index = 0;
                    start = temp;
                    COUNT ++;
                }
        }else{
            if (index == COUNT + 1){
                insertInLinkedList(value);
            }
            
            else{

                node* temp = (node*)malloc(sizeof (node));
                temp->value = value;
                temp->index = index;
                if (cursor->index == index){
                    cursor = temp;
                }
                COUNT ++;
                int i = 0;

                node *curr = start;
                while(i != index){
                    curr = curr->next;
                    i ++;
                }
                curr->prev->next = temp;
                temp->prev = curr->prev;
                temp->next = curr;
                curr->prev = temp;
                while (curr != NULL)
                {
                    curr->index = curr->index + 1;
                    curr = curr->next;
                }
                
            }
        }
        count++;

            if (stack.size <= 5 && state){
                stack.push(value , Stack::INSERTION , index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(value , Stack::INSERTION , index);
            }

            
        }
    }


    //4. Function to delete the number at specific index;
    void deleteANumberFromIndex(int index){
        

        if(COUNT == -1){
            cout << endl << "Invalid!!" << endl;
        } else if (index > COUNT){
            cout << endl << "Invalid!!" << endl;
        }else if (index == COUNT){
            deleteTail();
        }
        else{
            if (index == cursor->index){
                cursor = cursor->next;
            }
            
            if (index == 0){
            node* curr = start;
            start = start->next;
            start->prev = NULL;

            if (stack.size <= 5 && state){
                stack.push(curr->value,  Stack::DELETION , index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(curr->value,  Stack::DELETION , index);
            }
            count--;
            free(curr);
            COUNT --;
            curr = start;
            while (curr != NULL)
            {
                curr->index = curr->index - 1;
                curr = curr->next;
            }
        }else{
                int i = 0;
                node *curr = start;
                while(i != index){
                    curr = curr->next;
                    i ++;
                }
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;

                if (stack.size <= 5 && state){
                    stack.push(curr->value,  Stack::DELETION , index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(curr->value,  Stack::DELETION , index);
                }

                count--;
                free(curr);
                curr = curr->next;
                while (curr != NULL)
                {
                    curr->index = curr->index - 1;
                    curr = curr->next;
                }
                
                COUNT--;
                
        }

        
        }
    }


    //5. To Move cursor forward.
    void moveCursorForward(int steps){
        if (COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }
        else {
            node * temp = cursor;
            int i = 0;
            while (i < steps && temp != NULL){
                if (temp->next == NULL){
                    break;
                }
                temp = temp->next;
                i++;
            }
            cursor = temp;
            cout << endl << "Cursor moved forward by " << steps <<  " step(s)." << endl;
        }
        
    }


    //6. To Move Cursor Backward.
    void moveCursorBackward(int steps){
        if (COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }
        else {
            node * temp = cursor;
            int i = 0;
            while (i < steps && temp != NULL){
                if (temp->prev == NULL){
                    break;
                }
                temp = temp->prev;
                i++;
            }
            cursor = temp;
            cout << endl << "Cursor moved backwards by " << steps <<  " step(s)." << endl;
        }
        
    }


    //7. For enter value immediate in cursor.
    void insertImmediateValue(int value){
        if (COUNT == -1){
            cout << endl << endl << "INVALID" << endl << endl;
        }else if (cursor == NULL){
            cout << endl << endl << "INVALID" << endl << endl;
        }else if (cursor->next == NULL){
                COUNT ++;
                node* temp = (node*)malloc(sizeof(node));
                temp->value = value;
                temp->prev = cursor;
                temp->index = COUNT;
                temp->next = NULL;
                cursor->next = temp;
                count++;


                if (stack.size <= 5 && state){
                    stack.push(value,  Stack::INSERTION , temp->index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(value,  Stack::INSERTION , temp->index);
                }

        }
        else{
            if (cursor == start ){
                COUNT ++;
                node* temp = (node*)malloc(sizeof(node));
                temp->value = value;
                temp->prev = start;
                temp->next = start->next;
                start->next->prev = temp;
                temp->index = cursor->next->index;
                start->next = temp;
                node* curr = temp->next;
                while (curr != NULL){
                    curr->index = curr->index + 1;
                    curr = curr->next;
                }
                count++;

                if (stack.size <= 5 && state){
                    stack.push(value,  Stack::INSERTION , temp->index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(value,  Stack::INSERTION , temp->index);
                }
                
            }else{
                COUNT ++;
                node* temp = (node*)malloc(sizeof(node));
                temp->value = value;
                temp->index = cursor->next->index;
                temp->prev = cursor;
                temp->next = cursor->next;
                cursor->next->prev = temp;
                cursor->next = temp;
                node* curr = temp->next;
                while (curr != NULL){
                    curr->index = curr->index + 1;
                    curr = curr->next;
                }
                count++;

                if (stack.size <= 5 && state){
                    stack.push(value,  Stack::INSERTION , temp->index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(value,  Stack::INSERTION , temp->index);
                }

            }
        }
    }


    //8. For delete immediate value in cursor.
    void deleteImmediateValue(){
        if (COUNT == -1){
            cout << endl << endl << "INVALID" << endl << endl;
        }else if (cursor == NULL){
            cout << endl << endl << "INVALID" << endl << endl;
        }else if (cursor->next == NULL){
            deleteTail();
        }
        else{
            if (cursor == start ){


                if (stack.size <= 5 && state){
                    stack.push(cursor->value,  Stack::DELETION , cursor->index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(cursor->value,  Stack::DELETION , cursor->index);
                }

                COUNT --;
                start = start->next;
                start->prev = NULL;
                free(cursor);
                cursor = start;
                node* curr = start;
                while (curr != NULL)
                {
                    curr->index = curr->index - 1;
                    curr = curr->next;
                }
                

            }else{

                if (stack.size <= 5 && state){
                    stack.push(cursor->value,  Stack::DELETION , cursor->index);
                }else if (stack.size > 5 && state){
                    stack.reversePop();
                    stack.push(cursor->value,  Stack::DELETION , cursor->index);
                }

                COUNT --;
                node *curr = cursor;
                cursor->next->prev = cursor->prev;
                cursor->prev->next = cursor->next;
                cursor = cursor->next;
                free(curr);
                curr = cursor;
                while (curr != NULL){
                    curr->index = curr->index - 1;
                    curr = curr->next;
                }
                
            }
        }
    }


    //9. print cursor node value.
    void printCursorNodeValue(){
        if(COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }else if(cursor == NULL){
            cout << endl << "INVALID!!" << endl;
        }else{
            cout << endl << cursor->value << endl;
        }

    }


    //10. Update the value at specified index.
    void updateIndexNumber(int index , int value){
        if (COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }else if(index > COUNT){
            cout << endl << "INVALID!!" << endl;
        }else {

            if (stack.size <= 5 && state){
                stack.push(value,  Stack::UPDATION , index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(value,  Stack::UPDATION , index);
            }

            node* curr = start;
            int i = 0; 
            while (i < index){
                curr = curr->next;
                i ++;
            }

            if (stack.size <= 5 && state){
                stack.push(curr->value,  Stack::UPDATION , index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(curr->value,  Stack::UPDATION , index);
            }

            curr->value = value;
        }
    }


    //11. Update the number in which cursor is pointing to.
    void updateImmediateNumber(int value){
        if (COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }else if (cursor == NULL){
            cout << endl << "INVALID" << endl;
        }else{

            if (stack.size <= 5 && state){
                stack.push(cursor->value,  Stack::UPDATION , cursor->index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(cursor->value,  Stack::UPDATION , cursor->index);
            }
            
            cursor->value = value;
        }
    }


    //12. interchange values between cursor and index.
    void shiftIndex(int index){
        if (COUNT == -1){
            cout << endl << "INVALID!!" << endl;
        }else if (cursor == NULL){
            cout << endl << "INVALID" << endl;
        }else{
            node* curr = start;
            
            int i = 0; 
            while (i < index){
                curr = curr->next;
                i ++;
            }
            

            if (stack.size <= 5 && state){
                stack.push(curr->value,  Stack::UPDATION , index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(curr->value,  Stack::UPDATION , index);
            }



            if (stack.size <= 5 && state){
                stack.push(cursor->value,  Stack::DOUBLEUPDATION , cursor->index);
            }else if (stack.size > 5 && state){
                stack.reversePop();
                stack.push(cursor->value,  Stack::DOUBLEUPDATION , cursor->index);
            }

            int temp = curr->value;
            curr->value = cursor->value;
            cursor->value = temp;

        }
    }


    // 13. Undo the last operation
    void undo() {
        if (!(stack.isEmpty())) {

            state = false;
            stack.pop();
            if (stack.type == Stack::INSERTION) {
                deleteANumberFromIndex(stack.position);
            }else if (stack.type == Stack::DELETION) {
                insertAtIndex(stack.position, stack.Value);
            }else if (stack.type == Stack::UPDATION){
                updateIndexNumber(stack.position , stack.Value);
            }else if (stack.type == Stack::DOUBLEUPDATION){
                updateIndexNumber(stack.position, stack.Value);
                stack.pop();
                updateIndexNumber(stack.position, stack.Value);
            }else if (stack.type == Stack::DELETIONALL){
                stack.toDeleteAllStack();
            }
        } else {
            cout << "Undo stack is empty." << endl;
        }
    }

    //To delete all.
    void toDeleteAllNode(){
        node* curr;
        while (start != NULL){
            curr = start;
            start = start->next;
            free(curr);
        }
        stack.push(0, Stack::DELETIONALL, 0);
        undo();
    }

    //Last Function for printing the linked list.
    void printAllLinkedList(){
            if (start == NULL){
                cout << endl << "Linked LIst is empty" << endl;
            }else{
                node* curr = start;
                cout << endl;
                cout << "List: [";
                while (curr != NULL)
                {
                    cout << curr->value;
                    curr = curr->next;
                    if (curr != NULL){
                        cout << ", ";
                    }
                }
                cout << "]";
                cout << endl;
            }
    }


};

