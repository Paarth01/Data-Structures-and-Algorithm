#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the singly linked list
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

// Function to detect cycle and return the node where the cycle begins
struct Node* detectCycle(struct Node* head) {
    struct Node *slow = head, *fast = head;

    // Detect if there is a cycle
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // Move slow pointer by 1 step
        fast = fast->next->next;     // Move fast pointer by 2 steps

        if (slow == fast) {          // Cycle detected
            // Find the starting point of the cycle
            struct Node* start = head;
            while (start != slow) {
                start = start->next;
                slow = slow->next;
            }
            return start;            // Cycle start node
        }
    }

    return NULL;  // No cycle detected
}

// Main function to test the cycle detection
int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    // Create a cycle for testing
    head->next->next->next->next->next = head->next->next; // 5 -> 3

    struct Node* cycleNode = detectCycle(head);
    if (cycleNode != NULL) {
        printf("Cycle detected at node with data: %d\n", cycleNode->data);
    } else {
        printf("No cycle detected.\n");
    }

    return 0;
}
