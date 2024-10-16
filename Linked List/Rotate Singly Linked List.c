#include <stdio.h>
#include <stdlib.h>

// Definition of the linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a node at the end of the linked list
struct Node* insertNode(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // If the list is empty, the new node becomes the head
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode; // Add new node at the end
    return head;
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to rotate the linked list k times
struct Node* rotate(struct Node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    // Find the length of the linked list
    struct Node* current = head;
    int length = 1;
    while (current->next != NULL) {
        current = current->next;
        length++;
    }

    // Make the linked list circular
    current->next = head;

    // Calculate the effective number of rotations
    k = k % length;
    int stepsToNewHead = length - k;

    // Move to the new head position
    current = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        current = current->next;
    }

    // Set the new head and break the loop
    head = current->next;
    current->next = NULL;

    return head;
}

int main() {
    struct Node* head = NULL;

    // Inserting nodes into the linked list
    head = insertNode(head, 10);
    head = insertNode(head, 20);
    head = insertNode(head, 30);
    head = insertNode(head, 40);
    head = insertNode(head, 50);

    printf("Original List: \n");
    displayList(head);

    int k = 2;
    head = rotate(head, k);

    printf("\nList after %d rotations: \n", k);
    displayList(head);

    return 0;
}
