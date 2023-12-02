#include "linked lists.cpp"
#include <math.h>
using namespace std;

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

int digit(int num, int exp){
    int toDevide = pow(10, exp);
    int digit = (num/toDevide) % 10;
    return digit;
}

int maxExp(Node** head){
    int max = (*head)->Value;
    Node* temp = *head;
    while (temp->Next!=NULL){
        if (temp->Value>max){
            max = temp->Value;
        }
        temp = temp->Next;
    }
    int exp = 0;
    while (max>0){
        max = max/10;
        exp++;
    }
    return exp;
}

void reset(){
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

void distribute(Node* temp, int digiti){
    switch (digiti) {
        case 0:
            if (zero == NULL) {
                zero = temp;
                initial0 = zero;
                break;
            } else {
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

Node* countingSort(Node** head, int exp, LinkedList* newList) {
    reset();
    Node *temp = *head;
    newList->head = *head;
    while (temp->Next != NULL) { //counting
        int digiti = digit(temp->Value, exp);
        distribute(temp, digiti);
        temp = temp->Next;
    }
    int digiti = digit(temp->Value, exp);
    distribute(temp, digiti);

    Node* ends[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
    Node* starts[10] = {initial0, initial1, initial2, initial3, initial4, initial5, initial6, initial7, initial8, initial9};

    bool first = true;
    int i, j;
    for (i = 0; i < 9; i++) {
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
    return newList->head;
}

Node* driver (Node** head){
    LinkedList *tempo = new LinkedList();
    int maxexp = maxExp(head);
    int exp = 0;
    Node* temp = *head;
    while (exp<maxexp){
        temp = countingSort(&temp, exp, tempo);
        tempo->printList(tempo->head);
        printf("\n");
        exp++;
    }
    return tempo->head;
}

int main() {
//    setting my array to sort
    LinkedList *arr = new LinkedList();
    int toAdd[] = {195,469, 953,100, 112, 1654, 0, 2, 89, 16, 17, 3, 1, 4, 3000, 32, 5324, 7123, 215, 56, 9, 723, 744, 854, 823, 1, 1, 587, 1234, 876, 546, 19, 87, 69};
    int size = sizeof(toAdd) / sizeof(toAdd[0]);
    int i;
    for (i = 0; i < size; i++) {
        arr->pushToEnd(&arr->head, toAdd[i]);
    }
    printf("Original array: \n");
    arr->printList(arr->head);

    printf("\n\nstart sorting: \n");
    driver(&arr->head);
    return 0;
}