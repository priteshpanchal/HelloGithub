/*******************************************************************************************
* File Name          : ..
* Description        : Prog8130 - Assignment 3: Queue
*                      This program should implement a queue to enqueue/dequeue a list of
*                      positive numbers
*
* Author:              Pritesh panchal
* Date:                26-03-2022
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY (-1)
// structure used for holding data
typedef struct node {
    int number;
    struct node *next;
} Node;

// queue head and tail
Node *head = NULL;
Node *tail = NULL;

// queue functions
void enqueue(const int number);
int dequeue();

int main(int argc, char *argv[]) {
        int number;             // to store new number
        int i;                  // used in for loop as index

        // put all the numbers into the binary tree
        // numbers will be provided from command line
        for (i = 1; i < argc; i++) {
            // if it is a dequeue operation
            if (!strcmp(argv[i], "dequeue")) {
                printf("%s ", argv[i]);
                printf("%d\n", dequeue(head));
            } else {
                number = atoi(argv[i]);
                printf("enqueue %d\n", number);
                enqueue(number);
            }
        }

        return 0;
}

//====================== You should not modify anything above ==============================//
//==================== You should only modify following functions ==========================//
//============================= do not remove above comments  ==============================//

// FUNCTION      : enqueue
//
// DESCRIPTION   :
//   This function will add a new number into a queue
//
// PARAMETERS    :
//   number - the number that is to be stored in the queue
//
// RETURNS       :
//   Nothing
void enqueue(const int number) {
    // your code

    Node* newNode = (Node *)malloc(sizeof(Node));  //allocate memory to create the newnode.
    if (newNode == NULL) return;                   //if node not created return.

    newNode->number = number;                      //give number to current node.
    newNode -> next = NULL;                        //make its next pointer to point null

    //if tail is not empty attach current node to queue
    if (tail != NULL) {                            
        tail->next = newNode;
    }
    tail = newNode;
    
    //if this is first node make it head.
    if (head == NULL) {
        head = newNode;
    }
}

// FUNCTION      : dequeue
//
// DESCRIPTION   :
//   This function will dequeue a number from a queue
//
// PARAMETERS    :
//   None
//
// RETURNS       :
//   the number dequeued or -1 if the queue is empty
int dequeue() {
    // your code
    if (head == NULL) return EMPTY;                 //if heal is empty or queue is empty return -1.

    Node* tmp = head;                               //make tmp as head.
    int num = tmp->number;                          //take number from current node and give it to num.
    head = head->next;                              //move forward in queue
    if (head == NULL) {                             //if head is NULl make tail NULL
        tail == NULL;
    }
    free(tmp);
    return num;
}

