#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to push a new node to the linked list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to check if linked list is a palindrome
bool isPalindrome(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    struct Node* stack[100];  // Stack to store first half, assuming max length 100 for simplicity
    int top = -1;             // Stack pointer
    
    // Push first half of elements onto the stack
    while (fast != NULL && fast->next != NULL) {
        stack[++top] = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // If odd number of nodes, skip the middle node
    if (fast != NULL) {
        slow = slow->next;
    }

    // Compare elements of the second half with stack (first half reversed)
    while (slow != NULL) {
        if (stack[top--]->data != slow->data) {
            return false; // Not a palindrome
        }
        slow = slow->next;
    }

    return true; // Palindrome
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to push a new node to the linked list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to check if linked list is a palindrome
bool isPalindrome(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    struct Node* stack[100];  // Stack to store first half, assuming max length 100 for simplicity
    int top = -1;             // Stack pointer
    
    // Push first half of elements onto the stack
    while (fast != NULL && fast->next != NULL) {
        stack[++top] = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // If odd number of nodes, skip the middle node
    if (fast != NULL) {
        slow = slow->next;
    }

    // Compare elements of the second half with stack (first half reversed)
    while (slow != NULL) {
        if (stack[top--]->data != slow->data) {
            return false; // Not a palindrome
        }
        slow = slow->next;
    }

    return true; // Palindrome
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);

    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    return 0;
}


int main() {
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);

    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    return 0;
}
