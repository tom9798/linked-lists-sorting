#include "linked lists.cpp"
#include <math.h>
using namespace std;

LinkedList* generateRandomLinkedList(int size){ //generates random linked list
    LinkedList *arr = new LinkedList();
    int i;
    for (i = 0; i < size; i++) {
        arr->pushToEnd(&arr->head, rand() % 10000);
    }
    return arr;
}

//I know it looks bad, but it's pretty cheap comparing to other options
Node* zero = NULL;
Node* one = NULL;
Node* two = NULL;
Node* three = NULL;
Node* four = NULL;
Node* five = NULL;
Node* six = NULL;
Node* seven = NULL;
Node* eight = NULL;
Node* nine = NULL;

Node* initial0 = NULL;
Node* initial1 = NULL;
Node* initial2 = NULL;
Node* initial3 = NULL;
Node* initial4 = NULL;
Node* initial5 = NULL;
Node* initial6 = NULL;
Node* initial7 = NULL;
Node* initial8 = NULL;
Node* initial9 = NULL;

int digit(int num, int exp){ //returns digit of a number by its exponent
    int toDevide = pow(10, exp);
    int digit = (num/toDevide) % 10;
    return digit;
}

void reset(){ //resets all the pointers
    zero = NULL;
    one = NULL;
    two = NULL;
    three = NULL;
    four = NULL;
    five = NULL;
    six = NULL;
    seven = NULL;
    eight = NULL;
    nine = NULL;

    initial0 = NULL;
    initial1 = NULL;
    initial2 = NULL;
    initial3 = NULL;
    initial4 = NULL;
    initial5 = NULL;
    initial6 = NULL;
    initial7 = NULL;
    initial8 = NULL;
    initial9 = NULL;
}

void distribute(Node* temp, int digiti){ //distributes nodes by their digit
    switch (digiti) {
        case 0:
            if (zero == NULL) { //if the list is empty - initialize it with the new node and save the first node, so we can connect it later
                zero = temp;
                initial0 = zero;
                break;
            } else { //if the list is not empty - connect the last node to the new node, and save the new node as the last node
                zero->Next = temp;
                zero = zero->Next;
                break;
            }

        case 1:
            if (one == NULL) {
                one = temp;
                initial1 = one;
                break;
            } else {
                one->Next = temp;
                one = one->Next;
                break;
            }

        case 2:
            if (two == NULL) {
                two = temp;
                initial2 = two;
                break;
            } else {
                two->Next = temp;
                two = two->Next;
                break;
            }

        case 3:
            if (three == NULL) {
                three = temp;
                initial3 = three;
                break;
            } else {
                three->Next = temp;
                three = three->Next;
                break;
            }

        case 4:
            if (four == NULL) {
                four = temp;
                initial4 = four;
                break;
            } else {
                four->Next = temp;
                four = four->Next;
                break;
            }

        case 5:
            if (five == NULL) {
                five = temp;
                initial5 = five;
                break;
            } else {
                five->Next = temp;
                five = five->Next;
                break;
            }

        case 6:
            if (six == NULL) {
                six = temp;
                initial6 = six;
                break;
            } else {
                six->Next = temp;
                six = six->Next;
                break;
            }

        case 7:
            if (seven == NULL) {
                seven = temp;
                initial7 = seven;
                break;
            } else {
                seven->Next = temp;
                seven = seven->Next;
                break;
            }

        case 8:
            if (eight == NULL) {
                eight = temp;
                initial8 = eight;
                break;
            } else {
                eight->Next = temp;
                eight = eight->Next;
                break;
            }

        case 9:
            if (nine == NULL) {
                nine = temp;
                initial9 = nine;
                break;
            } else {
                nine->Next = temp;
                nine = nine->Next;
                break;
            }
    }
}

int countExp = 0; //static variables for the counting sort, in bigger lists it saves a lot of iterations
int maxNum = 0;

Node* countingSort(Node** head, int exp, LinkedList* newList) { //counting sort
    reset();
    Node *temp = *head;
    newList->head = *head;
    while (temp->Next != NULL) { //counting
        if (countExp == 0 && temp->Value > maxNum) { //getting the max number
            maxNum = temp->Value;
        }
        int digiti = digit(temp->Value, exp); // sorry for the bad variable names
        distribute(temp, digiti);
        temp = temp->Next;
    }
    if (countExp == 0) { //getting the max exponent
        if (temp->Value > maxNum) {
            maxNum = temp->Value;
        }
        while (maxNum > 0) { //that'll happen only once
            maxNum = maxNum / 10;
            countExp++;
        }
    }
    int digiti = digit(temp->Value, exp); //distributing the last node
    distribute(temp, digiti);

    Node* ends[10] = {zero, one, two, three, four, five, six, seven, eight, nine}; //array of the last nodes of each list
    Node* starts[10] = {initial0, initial1, initial2, initial3, initial4, initial5, initial6, initial7, initial8, initial9}; //array of the first nodes of each list
    // I could've used a linked list, but it would take longer. I know that each list will be 10 nodes because it's only for each digit, which is not that expansive memory-wise when comparing to big lists,
    //and a lot quicker when accessing the nodes, because I don't have to iterate through the list to get to the last node, I can just access it by its index (happens each iteration).
    //plus it doesn't need to be created each iteration, it's always the same order, the nodes contain the data.

    bool first = true;
    int i, j;
    for (i = 0; i < 9; i++) { //connecting the lists
        if (starts[i] != NULL) {
            if (first) {
                newList->head = starts[i];
                first = false;
            }
            for (j = i+1; j < 10; j++) {
                if (starts[j] != NULL) {
                    ends[i]->Next = starts[j];
                    ends[j]->Next = NULL;
                    break;
                }
            }
        }
    }
    newList->printList(newList->head); //printing the list after each iteration to see the progress (optional)
    printf("\n");
    return newList->head;
}

Node* driver (Node** head){
    LinkedList *tempo = new LinkedList();
    int exp = 0;
    Node* temp = *head;
    temp = countingSort(&temp, exp, tempo); //first iteration, getting the max exponent
    exp++;
    while (exp<countExp){ //sorting by each exponent
        temp = countingSort(&temp, exp, tempo);
        exp++;
    }
    countExp = 0; //resetting the static variables, so the function can be called again
    maxNum = 0;
    return tempo->head;
}

int main() {
    printf("start generating random linked list: \n");
    LinkedList* arr = generateRandomLinkedList(100);
    arr->printList(arr->head);
    printf("\n\nstart sorting: \n");
    driver(&arr->head);

    printf("\nfinished sorting: \n");
    arr->printList(arr->head);
    return 0;
}