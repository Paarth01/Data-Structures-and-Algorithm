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
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* last = (*head)->prev;

    // Adjusting the pointers for circularity and doubly links
    newNode->next = *head;
    (*head)->prev = newNode;
    newNode->prev = last;
    last->next = newNode;
}

// Function to insert a node at the beginning of the list
void insertBegin(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;
    last->next = newNode;
    (*head)->prev = newNode;

    *head = newNode;
}

// Function to delete a node from the list
void deleteNode(struct Node** head, int key) {
    if (*head == NULL)
        return;

    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp->data != key) {
        if (temp->next == *head) {
            printf("Node with value %d not found.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    if (temp->next == *head && prev == NULL) {
        free(temp);
        *head = NULL;
        return;
    }

    if (temp == *head) {
        prev = (*head)->prev;
        *head = (*head)->next;
        prev->next = *head;
        (*head)->prev = prev;
        free(temp);
    } else if (temp->next == *head) {
        prev->next = *head;
        (*head)->prev = prev;
        free(temp);
    } else {
        struct Node* next = temp->next;
        prev->next = next;
        next->prev = prev;
        free(temp);
    }
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
                insertBegin(&head, value);
                break;
            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                insertEnd(&head, value);
                break;
            case 3:
                printf("Enter the value to delete: ");
                scanf("%d", &key);
                deleteNode(&head, key);
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