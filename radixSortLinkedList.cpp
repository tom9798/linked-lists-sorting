#include "linked lists.cpp"
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

LinkedList* generateRandomLinkedList(int size){ //generates random linked list
    LinkedList *arr = new LinkedList();
    int i;
    for (i = 0; i < size; i++) {
        Node*temp = new Node();
        temp->Value = rand() % 1000;
        temp->Next = arr->head;
        arr->head = temp;
//        arr->pushToEnd(&arr->head, rand() % 10000);
    }
    return arr;
}

Node* endings[10] = {new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node};
Node* starts[10] = {new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node, new Node};
// I could've used a linked list, but it would take longer. I know that each list will be 10 nodes because it's only for each digit, which is not that expansive memory-wise when comparing to big lists,
//and a lot quicker when accessing the nodes, because I don't have to iterate through the list to get to the last node, I can just access it by its index (happens each iteration).
//plus it doesn't need to be created each iteration, it's always the same order, the nodes contain the data.

int digit(int num, int exp){ //returns digit of a number by its exponent
    int toDevide = pow(10, exp);
    int digit = (num/toDevide) % 10;
    return digit;
}

void resetDriver(Node* start[], Node* end[], int i){ //resets all the pointers
    start[i] = NULL;
    end[i] = NULL;
}

void reset(Node* start[], Node* end[]){ //resets all the pointers
    int num_threads = 10;
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(std::thread(resetDriver, start, end, i));
    }
    for (auto& t : threads) {
        t.join();
    }
}

//void connectingListsDriver(int i,int max){
//    if (starts[i] != NULL) {
//        for (int j = i+1; j < 10; j++) {
//            if (starts[j] != NULL) {
//                endings[i]->Next = starts[j];
//                if (endings[j]->Value == max) {
//                    endings[j]->Next = NULL;
//                }
//                break;
//            }
//        }
//    }
//}
//
//void connectingLists(LinkedList* arr, int max){ //connects the lists using threads
//    int num_threads = 9;
//    std::vector<std::thread> threads;
//    int i;
//    for (i = 0; i < 10; i++) {
//        if (starts[i] != NULL) {
//            arr->head = starts[i]; //saving the first node of the new list, so we can return the head
//            break;
//        }
//    }
//    for (i; i < num_threads; i++) {
//        if (starts[i] != NULL) {
//            threads.push_back(std::thread(connectingListsDriver, i, max));
//        }
//    }
//    for (auto& t : threads) {
//        t.join();
//    }
//}

int countExp = 0; //static variables for the counting sort, in bigger lists it saves a lot of iterations
int maxNum = 0;
//int maxExp = 0; //for the threads option
//int maxDigit = 0;
Node* countingSort(Node** head, int exp, LinkedList* newList) { //counting sort
    reset(starts, endings); //resetting the pointers
    Node *temp = *head;
    newList->head = *head;
    while (temp->Next != NULL) { //counting
        if (countExp == 0 && temp->Value > maxNum) { //getting the max number
            maxNum = temp->Value;
        }
        //distributing the nodes
        int digiti = digit(temp->Value, exp); // sorry for the bad variable names
        if(endings[digiti] == NULL){ //if it's the first node of the list, initialize it
            endings[digiti] = temp;
            starts[digiti] = endings[digiti];
        }else{
            endings[digiti]->Next = temp;
            endings[digiti] = endings[digiti]->Next;
        }
//        if (digiti >= maxDigit) { //getting the max digit, for the threads option
//            maxDigit = digiti;
//            maxExp = temp->Value;
//        }
        temp = temp->Next;
    }

    //distributing the last node
    int digiti = digit(temp->Value, exp);
    if(endings[digiti] == NULL){
        endings[digiti] = temp;
        starts[digiti] = endings[digiti];
    }else{
        endings[digiti]->Next = temp;
        endings[digiti] = endings[digiti]->Next;
    }

    if (countExp == 0) { //getting the max exponent
        if (temp->Value > maxNum) {
            maxNum = temp->Value;
        }
        int maxNumTemp = maxNum;
        while (maxNumTemp > 0) { //that'll happen only once
            maxNumTemp = maxNumTemp / 10;
            countExp++;
        }
    }

    bool first = true;
    int i, j;
    for (i = 0; i < 9; i++) { //connecting the lists
        if (starts[i] != NULL) {
            if (first) {
                newList->head = starts[i]; //saving the first node of the new list, so we can return the head
                first = false;
            }
            for (j = i+1; j < 10; j++) {
                if (starts[j] != NULL) {
                    endings[i]->Next = starts[j];
                    endings[j]->Next = NULL; //making sure the last node is NULL so the list won't be infinite
                    break;
                }
            }
        }
    }

//    connectingLists(newList, maxExp); //connecting the lists using threads option, not really faster int this case because the lists are small
//    maxExp = 0;
//    maxDigit = 0;

//    newList->printList(newList->head); //printing the list after each iteration to see the progress (optional)
//    printf("\n");
    return newList->head;
}

Node* driver (LinkedList* arr){
    LinkedList *tempo = new LinkedList();
    int exp = 0;
    Node* temp = arr->head;
    temp = countingSort(&temp, exp, tempo); //first iteration, getting the max exponent
    exp++;
    while (exp<countExp){ //sorting by each exponent
        temp = countingSort(&temp, exp, tempo);
        exp++;
    }


    countExp = 0; //resetting the static variables, so the function can be called again
    maxNum = 0;

    arr->head = tempo->head;
    return tempo->head;
}

LinkedList* arr = generateRandomLinkedList(1000);
int main() {
//    arr->printList(arr->head);
    printf("\n\nstart sorting: \n");
    clock_t start = clock();
    driver(arr);
    clock_t end = clock();
    printf("\nfinished sorting in: %ld\n", (end-start)/CLOCKS_PER_SEC);
//    arr->printList(arr->head);
    return 0;
}