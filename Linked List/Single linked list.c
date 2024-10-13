#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
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
    return head;
}

// Function to insert a node at a specific position (1-based index)
struct Node* insertAtPosition(struct Node* head, int position, int data) {
    if (position == 1) {
        return insertAtBeginning(head, data);
    }

    struct Node* temp = head;
    int currentPos = 1;

    // Traverse to find the position just before the desired index
    while (temp != NULL && currentPos < position - 1) {
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Position out of range.\n");
        return head;
    }

    // Create the new node
    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", data, position);

    return head;
}

// Function to insert a node after a specific node
struct Node* insertAfterNode(struct Node* head, int targetData, int data) {
    struct Node* temp = head;
    
    // Traverse to find the target node
    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Target node not found.\n");
        return head;
    }

    // Create the new node
    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
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

    // If the target node is the head
    if (head->data == targetData) {
        return insertAtBeginning(head, data);
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    // Traverse to find the target node
    while (temp != NULL && temp->data != targetData) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Target node not found.\n");
        return head;
    }

    // Create the new node
    struct Node* newNode = createNode(data);
    prev->next = newNode;
    newNode->next = temp;
    printf("Inserted %d before %d.\n", data, targetData);

    return head;
}

// Function to delete a node after a specific node
struct Node* deleteAfterNode(struct Node* head, int targetData) {
    struct Node* temp = head;

    // Traverse to find the target node
    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("No node exists after the target node.\n");
        return head;
    }

    // Delete the node after the target node
    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    printf("Node deleted after %d.\n", targetData);

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
    free(temp);
    printf("Node deleted from the beginning.\n");
    return head;
}


// Function to delete a node before a specific node
struct Node* deleteBeforeNode(struct Node* head, int targetData) {
    if (head == NULL || head->next == NULL) {
        printf("List is too short to perform this operation.\n");
        return head;
    }

    // If the target node is the second node, we delete the first node
    if (head->next->data == targetData) {
        return deleteFromBeginning(head);
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    // Traverse to find the node just before the target node
    while (temp->next != NULL && temp->next->data != targetData) {
        prev = temp;
        temp = temp->next;
    }

    if (temp->next == NULL) {
        printf("Target node not found.\n");
        return head;
    }

    // Delete the node before the target node
    prev->next = temp->next;
    free(temp);
    printf("Node deleted before %d.\n", targetData);

    return head;
}

// Function to delete a node at a specific position (1-based index)
struct Node* deleteAtPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    // If the position is 1, delete the first node
    if (position == 1) {
        return deleteFromBeginning(head);
    }

    struct Node* temp = head;
    struct Node* prev = NULL;
    int currentPos = 1;

    // Traverse to find the node at the specified position
    while (temp != NULL && currentPos < position) {
        prev = temp;
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL) {
        printf("Position out of range.\n");
        return head;
    }

    // Delete the node at the specified position
    prev->next = temp->next;
    free(temp);
    printf("Node deleted at position %d.\n", position);

    return head;
}

// Function to delete a node from the end
struct Node* deleteFromEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }
    if (head->next == NULL) {
        free(head);
        printf("Node deleted from the end.\n");
        return NULL;
    }
    struct Node* temp = head;
    struct Node* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
    printf("Node deleted from the end.\n");
    return head;
}

// Function to display the linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
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
        printf("8. Delete after a node\n");
        printf("9. Delete before a node\n");
        printf("10. Delete at a specific position\n");
        printf("11. Display list\n");
        printf("12. Exit\n");
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
                printf("Enter target node data to delete after: ");
                scanf("%d", &targetData);
                head = deleteAfterNode(head, targetData);
                break;
            case 9:
                printf("Enter target node data to delete before: ");
                scanf("%d", &targetData);
                head = deleteBeforeNode(head, targetData);
                break;
            case 10:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                head = deleteAtPosition(head, position);
                break;
            case 11:
                displayList(head);
                break;
            case 12:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
