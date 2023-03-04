/*******************************************************************************************
* File Name          : assign1skeleton_v2.c
* Description        : Prog8130 - Assignment 1 (V2): Doubly Linked Lists
*                      This program uses linked lists to hold and print a list of names
*                      organized by order number assosciated with each name. Each name can
*                      consist of maximum 30 characters.
*
* Author:              Priteh panchal
* Date:                19-03-2022
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_length 30								// Total length of the string
#define NUMBER_OF_DATA_ITEMS   4					    // the number of data items to be used in list


// structure/typedef used for holding data
typedef struct {
    char name[30];
    int  order;
} inputData;

// definition of linked list data nodes
typedef struct node {
    char                  name[30];        // the name to be stored
    int                   order;           // the order to be stored
    struct node           *next;           // pointer to next node in list (NULL if the end)
    struct node           *prev;           // pointer to prev node in list (NULL if the front)
} Node;

// define linked list front and rare as global variables
Node *front = NULL;
Node *rare = NULL;

int indexs[NUMBER_OF_DATA_ITEMS]; //declare an array for storing the value of DataIndex, to help add element in LinkedList.

// prototypes
void AddToLinkedList(char *name, int order);
void PrintLinkedListFront(Node *front);
void PrintLinkedListRare(Node *rare);

// data used for test
// start iData
inputData iData[] = {
    { "orange", 3 },
    { "kiwi", 1 },
    { "apple", 2 },
    { "lemon", 4 }
};
// end iData
// end of data for assignment

int main(void) {
    int i;

    // Print out the input data
    printf("Data before Linked List is:\n");
    for (i = 0; i < sizeof(iData)/sizeof(inputData); i++) {
        printf("%s,%d\n", iData[i].name, iData[i].order);
    }
    printf("--\n");

    // insert the data into Linked List
    for (i = 0; i < sizeof(iData)/sizeof(inputData); i++) {
        AddToLinkedList(iData[i].name, iData[i].order);
    }
    
    printf("Data after adding (front):\n");
    PrintLinkedListFront(front);
    printf("--\n");

    printf("Data after adding (rare):\n");
    PrintLinkedListRare(rare);
    printf("--\n");

    return 0;
}

//====================== You should not modify anything above ==============================//
//==================== You should only modify following functions ==========================//

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input a name and an order and
//                 place it in a linked list organized by priority of order number.
// PARAMETERS    : char *name               - Array of Characters with data
//                 int order                - Order of the item
// RETURNS       : void
void AddToLinkedList(char *name, int order) {
    // put code in here to add the item(s) to the linked list
    // malloc to store the new node
    // check if empty
    // check if should insert before front
    // check if should insert after rare
    // general case
    static int nextData = 0;
    Node* NodeNew = NULL;
    Node* temp = NULL;
    static  Node* current = NULL;
    static  Node* prevNode = NULL;

    NodeNew = (Node*)malloc(sizeof(Node));
    indexs[nextData] = order;

    if (NodeNew)
    {
        strcpy(NodeNew->name, name);  //copy string data to node data
        NodeNew->order = order;       //copy order of the name to newnode order variable
        NodeNew->next = NULL;         //make it point to null
        NodeNew->prev = NULL;         //make it point to null


        if (front == NULL)            //check if front is there or not.
        {
            front = NodeNew;          //if front is null make new node front.
        }
        else if ((front)->order >= NodeNew->order) {  // check if front order is greter then newnode order 
            NodeNew->next = front;                    // give nodenew next the address of front 
            NodeNew->next->prev = NodeNew;            // 
            front = NodeNew;                          // make newnode front of the list if its order is smaller then current front
        }
        else
        {
    
        current = front;                              //copy front address to current address.

        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
            current->next->order < order)
            current = current->next;

        /* Make the appropriate links */
        NodeNew->next = current->next;

        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            NodeNew->next->prev = NodeNew;

        //swap the current node with new node if newnode order is smaller then current node
        current->next = NodeNew;                   
        NodeNew->prev = current;
    }
        }
          
        if (NodeNew->next == NULL) {
           rare = NodeNew;
        }
           
        
    

    return;
}

// FUNCTION      : PrintLinkedListFront() / PrintLinkedListRare()
// DESCRIPTION   : These functions take an input of the front/rare of the doubly linked list, then loops through
//                 and prints each word in the doubly linked list.
// PARAMETERS    : Node *
// RETURNS       : void

void PrintLinkedListFront(Node *front) {
    // put code in here to print the linked list out
    Node* temp = front;

    while (temp != NULL)
    {
        printf("%s %d\n", temp->name, temp->order);	     // print Data in current node.
        temp = temp->next;		                         // move forward in list.
    }
}

void PrintLinkedListRare(Node *rare) {
    // put code in here to print the linked list out
    Node* temp = rare;
    if (temp == NULL) return;                               //If temp is not created return without doing anything.

    while (temp->next != NULL) {
        temp = temp->next;                                  //go till the end of the list.
    }

    while (temp != NULL) {
        printf("%s %d\n", temp->name, temp->order);	        // print Data in current node.
        temp = temp->prev;                                  // move backwards in list.
    }
}

