#include "iostream"
#include "stdio.h"

using namespace std;


int PrintArray(int arry[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arry[i]);
    }
    printf("\n");
}



class Node {
public:
    int Value;
    Node* Next;
};

class LinkedList {
public:
    Node* head;
    int length;
    LinkedList(){
        this->head = NULL;
        this->length = 0;
    }

    void printList(Node* n){
        while (n != NULL){
            cout << n->Value << " ";
            n = n->Next;
        }
    }

    void pushToStart(Node** head_ref, int new_value){
        if (*head_ref == NULL){
            *head_ref = new Node();
            (*head_ref)->Value = new_value;
            (*head_ref)->Next = NULL;
            return;
        }
        Node*new_node = new Node();
        new_node->Value = new_value;
        new_node->Next = *head_ref;
        *head_ref = new_node;
    }

    void pushToEnd(Node** head_ref, int new_value){
        Node* new_node = new Node();
        new_node->Value = new_value;
        new_node->Next = NULL;
        if (*head_ref == NULL){
            *head_ref = new_node;
            return;
        }
        Node* last_node = *head_ref;
        while (last_node->Next!=NULL){
            last_node = last_node->Next;
        }
        last_node->Next = new_node;
    }

    void pushAfter(Node* prev_node, int new_value){
        if (prev_node == NULL){
            cout << "The given previous node cannot be NULL";
            return;
        }
//    set node
        Node* new_node = new Node();
        new_node->Value = new_value;
//  push between prev and next
        new_node->Next = prev_node->Next;
        prev_node->Next = new_node;
    }

    void pushAfterIndex(int index, int value, Node** head_ref){
        Node* new_node = new Node();
        new_node->Value = value;
        int i = 0;
        Node* indexedNode = *head_ref;
        Node* nodeAfter = indexedNode->Next;
        while(i!=index){
            indexedNode = indexedNode->Next;
            i++;
            nodeAfter = indexedNode->Next;
            printf("i: %d\n", i);
        }
        indexedNode->Next = new_node;
        new_node->Next = nodeAfter;
    }

    int getValAtIndex(int index, Node** head_ref){
        Node* indexedNode = *head_ref;
        int i = 0;
        while(i!=index){
            indexedNode = indexedNode->Next;
            i++;
        }
        return indexedNode->Value;
    }

    void pushArrayToEnd(int arr[], int size, Node** head_ref){
        int i;
        for (i = 0; i < size; i++) {
            Node *new_node = new Node();
            new_node->Value = arr[i];
            new_node->Next = NULL;
            if (*head_ref == NULL) {
                *head_ref = new_node;
                return;
            }
            Node *last_node = *head_ref;
            while (last_node->Next != NULL) {
                last_node = last_node->Next;
                cout<<last_node<< " ";
            }
            last_node->Next = new_node;
        }
    }

    void replace(Node** origin_head_ref, Node ** replacing_head_ref){
        Node* origin = *origin_head_ref;
        Node* replacing = *replacing_head_ref;
        while (origin->Next != NULL){
            origin->Value = replacing->Value;
            origin = origin->Next;
            replacing = replacing->Next;
        }
        origin->Value = replacing->Value;
    }

    void attachToHead(Node** head_ref){
        this->head = *head_ref;
    }

};