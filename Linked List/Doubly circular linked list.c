#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
}

// Function to insert a node at the end of the list
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }

    struct Node* last = head->prev;

    // Adjusting the pointers for circularity and doubly links
    newNode->next = head;
    head->prev = newNode;
    newNode->prev = last;
    last->next = newNode;

    return head;
}

// Function to insert a node at the beginning of the list
struct Node* insertBegin(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    struct Node* last = head->prev;

    newNode->next = head;
    newNode->prev = last;
    last->next = newNode;
    head->prev = newNode;

    return newNode;  // Return the new node as the new head
}

// Function to delete a node from the list
struct Node* deleteNode(struct Node* head, int key) {
    if (head == NULL)
        return NULL;

    struct Node* temp = head;
    struct Node* prev = NULL;

    while (temp->data != key) {
        if (temp->next == head) {
            printf("Node with value %d not found.\n", key);
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    // Single node case
    if (temp->next == head && temp->prev == head) {
        free(temp);
        return NULL;
    }

    // If the node to be deleted is the head node
    if (temp == head) {
        prev = head->prev;
        head = head->next;
        prev->next = head;
        head->prev = prev;
        free(temp);
        return head;
    }

    // If the node to be deleted is the last node
    if (temp->next == head) {
        prev->next = head;
        head->prev = prev;
        free(temp);
        return head;
    }

    // For other nodes
    struct Node* next = temp->next;
    prev->next = next;
    next->prev = prev;
    free(temp);

    return head;
}

// Function to display the list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Main function
int main() {
    struct Node* head = NULL;
    int choice, value, key;

    do {
        printf("\nDoubly Circular Linked List Operations:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete a Node\n");
        printf("4. Display the List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at beginning: ");
                scanf("%d", &value);
                head = insertBegin(head, value);
                break;
            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                head = insertEnd(head, value);
                break;
            case 3:
                printf("Enter the value to delete: ");
                scanf("%d", &key);
                head = deleteNode(head, key);
                break;
            case 4:
                displayList(head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
