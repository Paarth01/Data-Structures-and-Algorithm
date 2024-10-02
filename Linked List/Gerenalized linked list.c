#include <stdio.h>
#include <stdlib.h>

// Structure definition for a node in the generalized linked list
struct GLLNode {
    struct GLLNode* sublist;  // Pointer to a sublist (another GLLNode)
    struct GLLNode* next;     // Pointer to the next node in the list
};

// Function to create a new node (initially with NULL sublist)
struct GLLNode* createNode() {
    struct GLLNode* node = (struct GLLNode*) malloc(sizeof(struct GLLNode));
    node->sublist = NULL;
    node->next = NULL;
    return node;
}

// Function to insert a sublist into a generalized linked list
struct GLLNode* insertSublist(struct GLLNode* head, struct GLLNode* sublist) {
    struct GLLNode* newNode = createNode();
    newNode->sublist = sublist;
    newNode->next = head;
    return newNode;
}

// Function to print a generalized linked list
void printGLL(struct GLLNode* head) {
    struct GLLNode* temp = head;
    printf("(");
    while (temp != NULL) {
        if (temp->sublist != NULL) {
            printGLL(temp->sublist);  // Recursively print the sublist
        } else {
            printf("NULL");
        }
        temp = temp->next;
        if (temp != NULL) {
            printf(", ");
        }
    }
    printf(")");
}

// Function to free the memory of a generalized linked list
void freeGLL(struct GLLNode* head) {
    struct GLLNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        if (temp->sublist != NULL) {
            freeGLL(temp->sublist);  // Free the sublist recursively
        }
        free(temp);
    }
}

// Main function to demonstrate the GLL operations
int main() {
    struct GLLNode* list = NULL;
    struct GLLNode* sublist1 = NULL;
    struct GLLNode* sublist2 = NULL;

    // Creating a sublist (NULL, NULL)
    sublist1 = insertSublist(sublist1, NULL);
    sublist1 = insertSublist(sublist1, NULL);

    // Creating another sublist (NULL, (NULL, NULL))
    sublist2 = insertSublist(sublist2, sublist1); // Insert sublist1 into sublist2
    sublist2 = insertSublist(sublist2, NULL);

    // Inserting sublist2 into the main list
    list = insertSublist(list, sublist2);

    // Inserting another NULL node
    list = insertSublist(list, NULL);

    // The final list is: (NULL, ((NULL, NULL), NULL))

    printf("Generalized Linked List: ");
    printGLL(list);
    printf("\n");

    // Free the allocated memory
    freeGLL(list);

    return 0;
}