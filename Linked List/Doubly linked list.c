#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the beginning
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}

// Function to insert a node at the end
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to insert a node at a specific position (1-based index)
struct Node* insertAtPosition(struct Node* head, int position, int data) {
    if (position == 1) {
        return insertAtBeginning(head, data);
    }

    struct Node* temp = head;
    int currentPos = 1;

    while (temp != NULL && currentPos < position - 1) {
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Position out of range.\n");
        return head;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;

    printf("Inserted %d at position %d.\n", data, position);
    return head;
}

// Function to insert a node after a specific node
struct Node* insertAfterNode(struct Node* head, int targetData, int data) {
    struct Node* temp = head;

    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Target node not found.\n");
        return head;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;

    printf("Inserted %d after %d.\n", data, targetData);
    return head;
}

// Function to insert a node before a specific node
struct Node* insertBeforeNode(struct Node* head, int targetData, int data) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    if (head->data == targetData) {
        return insertAtBeginning(head, data);
    }

    struct Node* temp = head;

    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Target node not found.\n");
        return head;
    }

    struct Node* newNode = createNode(data);
    newNode->next = temp;
    newNode->prev = temp->prev;

    if (temp->prev != NULL) {
        temp->prev->next = newNode;
    }
    temp->prev = newNode;

    printf("Inserted %d before %d.\n", data, targetData);
    return head;
}

// Function to delete a node from the beginning
struct Node* deleteFromBeginning(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    struct Node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    printf("Node deleted from the beginning.\n");
    return head;
}

// Function to delete a node from the end
struct Node* deleteFromEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        head = NULL;  // If the list had only one node
    }

    free(temp);
    printf("Node deleted from the end.\n");
    return head;
}

// Function to delete a node at a specific position (1-based index)
struct Node* deleteAtPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    if (position == 1) {
        return deleteFromBeginning(head);
    }

    struct Node* temp = head;
    int currentPos = 1;

    while (temp != NULL && currentPos < position) {
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Position out of range.\n");
        return head;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Node deleted at position %d.\n", position);
    return head;
}

// Function to display the doubly linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display the list backwards
void displayListBackwards(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;

    // Traverse to the last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Traverse backward and print the list
    printf("List (Backwards): ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// Main function with menu-driven interface
int main() {
    struct Node* head = NULL;
    int choice, data, targetData, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert after a node\n");
        printf("4. Insert before a node\n");
        printf("5. Insert at a specific position\n");
        printf("6. Delete from beginning\n");
        printf("7. Delete from end\n");
        printf("8. Display list\n");
        printf("9. Display list backwards\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Enter target node data to insert after: ");
                scanf("%d", &targetData);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                head = insertAfterNode(head, targetData, data);
                break;
            case 4:
                printf("Enter target node data to insert before: ");
                scanf("%d", &targetData);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                head = insertBeforeNode(head, targetData, data);
                break;
            case 5:
                printf("Enter position to insert at: ");
                scanf("%d", &position);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                head = insertAtPosition(head, position, data);
                break;
            case 6:
                head = deleteFromBeginning(head);
                break;
            case 7:
                head = deleteFromEnd(head);
                break;
            case 8:
                displayList(head);
                break;
            case 9:
                displayListBackwards(head);
                break;
            case 10:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
