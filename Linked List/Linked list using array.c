#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Define maximum size of the array

// Define a structure for a linked list node
struct Node {
    int data;     // Data part of the node
    int next;     // Index of the next node in the array
};

// Initialize the free list
void initializeFreeList(struct Node list[], int *freeList) {
    for (int i = 0; i < MAX - 1; i++) {
        list[i].next = i + 1; // Link each node to the next free node
    }
    list[MAX - 1].next = -1; // End of free list
    *freeList = 0;           // Set freeList to start at 0
}

// Allocate a node from the free list
int allocateNode(struct Node list[], int *freeList) {
    if (*freeList == -1) {
        printf("No free space available!\n");
        return -1; // No free space available
    }
    int newNode = *freeList;
    *freeList = list[*freeList].next; // Update the free list
    return newNode;
}

// Deallocate a node and add it back to the free list
void deallocateNode(struct Node list[], int *freeList, int index) {
    list[index].next = *freeList;
    *freeList = index;
}

// Insert an element at the beginning of the linked list
void insertAtBeginning(struct Node list[], int *head, int *freeList, int data) {
    int newNode = allocateNode(list, freeList);
    if (newNode == -1) return; // No space available

    list[newNode].data = data;
    list[newNode].next = *head;
    *head = newNode; // Update head to point to the new node
}

// Insert an element at the end of the linked list
void insertAtEnd(struct Node list[], int *head, int *freeList, int data) {
    int newNode = allocateNode(list, freeList);
    if (newNode == -1) return; // No space available

    list[newNode].data = data;
    list[newNode].next = -1;

    if (*head == -1) {
        // List is empty, set the head to newNode
        *head = newNode;
    } else {
        // Traverse to the end of the list
        int temp = *head;
        while (list[temp].next != -1) {
            temp = list[temp].next;
        }
        list[temp].next = newNode; // Append the new node at the end
    }
}

// Delete the first occurrence of an element from the linked list
void deleteElement(struct Node list[], int *head, int *freeList, int data) {
    if (*head == -1) {
        printf("List is empty!\n");
        return;
    }

    int temp = *head, prev = -1;

    // Traverse the list to find the node to be deleted
    while (temp != -1 && list[temp].data != data) {
        prev = temp;
        temp = list[temp].next;
    }

    if (temp == -1) {
        // Element not found
        printf("Element %d not found in the list!\n", data);
        return;
    }

    if (prev == -1) {
        // Element to be deleted is the head node
        *head = list[temp].next;
    } else {
        // Remove the node by linking the previous node to the next node
        list[prev].next = list[temp].next;
    }

    // Deallocate the node
    deallocateNode(list, freeList, temp);
}

// Display the linked list
void displayList(struct Node list[], int head) {
    if (head == -1) {
        printf("List is empty!\n");
        return;
    }

    int temp = head;
    while (temp != -1) {
        printf("%d -> ", list[temp].data);
        temp = list[temp].next;
    }
    printf("NULL\n");
}

// Menu-driven program
int main() {
    struct Node list[MAX]; // Array of nodes to simulate linked list
    int head = -1;         // Head pointer (index of the first element)
    int freeList;          // Free list to manage available space in the array

    initializeFreeList(list, &freeList); // Initialize the free list

    int choice, data;
    
    do {
        printf("\nMenu:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete an Element\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter the element to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(list, &head, &freeList, data);
                break;
            case 2:
                printf("Enter the element to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(list, &head, &freeList, data);
                break;
            case 3:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                deleteElement(list, &head, &freeList, data);
                break;
            case 4:
                printf("Linked list: ");
                displayList(list, head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}