#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the circular linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the circular linked list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* temp = head;

    if (head == NULL) {
        newNode->next = newNode;  // Circular link
        return newNode;
    } else {
        while (temp->next != head) {  // Find the last node
            temp = temp->next;
        }
        newNode->next = head;  // Point new node to head
        temp->next = newNode;  // Point last node to new node
        head = newNode;        // Make new node the new head
    }

    return head;
}

// Function to insert a node at the end of the circular linked list
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    struct Node* temp = head;

    if (head == NULL) {
        newNode->next = newNode;  // Point to itself, making it circular
        return newNode;
    } else {
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    return head;
}

// Function to insert a node at a given position in the circular linked list
struct Node* insertAtPosition(struct Node* head, int data, int position) {
    struct Node* newNode = createNode(data);
    struct Node* temp = head;

    if (position == 1) {
        return insertAtBeginning(head, data);  // Insert at the beginning if position is 1
    }

    for (int i = 1; i < position - 1 && temp->next != head; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

// Function to delete the first node from the circular linked list
struct Node* deleteBegin(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return head;
    }

    struct Node* temp = head;
    struct Node* last = head;

    // If there is only one node
    if (temp->next == head) {
        free(temp);
        return NULL;
    }

    // Find the last node
    while (last->next != head) {
        last = last->next;
    }

    head = temp->next;
    last->next = head;
    free(temp);

    return head;
}

// Function to delete the last node from the circular linked list
struct Node* deleteEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return head;
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    // If there is only one node
    if (temp->next == head) {
        free(temp);
        return NULL;
    }

    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = head;
    free(temp);

    return head;
}

// Function to delete a node at a given position in the circular linked list
struct Node* deleteAtPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return head;
    }

    if (position == 1) {
        return deleteBegin(head);
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    for (int i = 1; i < position && temp->next != head; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp->next == head && position != 1) {
        printf("Invalid position\n");
        return head;
    }

    prev->next = temp->next;
    free(temp);

    return head;
}

// Function to display the circular linked list
void display(struct Node* head) {
    struct Node* temp = head;
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head)\n");
}

// Driver code
int main() {
    struct Node* head = NULL;
    int choice, value, position;

    do {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete at position\n");
        printf("7. Display list\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            head = insertAtBeginning(head, value);
            break;
        case 2:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            head = insertEnd(head, value);
            break;
        case 3:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            printf("Enter position to insert: ");
            scanf("%d", &position);
            head = insertAtPosition(head, value, position);
            break;
        case 4:
            head = deleteBegin(head);
            break;
        case 5:
            head = deleteEnd(head);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            head = deleteAtPosition(head, position);
            break;
        case 7:
            display(head);
            break;
        case 8:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8); // Loop until the user chooses to exit

    return 0;
}
