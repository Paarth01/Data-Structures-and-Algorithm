#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Define the maximum size of the stack

// Function to check if the stack is full
int isFull(int top) {
    return top == MAX - 1;
}

// Function to check if the stack is empty
int isEmpty(int top) {
    return top == -1;
}

// Function to push an element onto the stack
void push(int stack[], int *top) {
    if (isFull(*top)) {
        printf("Stack Overflow! Unable to push.\n");
        return;
    }
    int element;
    printf("Enter the element to push: ");
    scanf("%d", &element);
    (*top)++;
    stack[*top] = element;
    printf("Element %d pushed onto the stack.\n", element);
}

// Function to pop an element from the stack
void pop(int stack[], int *top) {
    if (isEmpty(*top)) {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }
    int poppedElement = stack[*top];
    (*top)--;
    printf("Element %d popped from the stack.\n", poppedElement);
}

// Function to display the elements of the stack
void display(int stack[], int top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Main function with menu-driven functionality using do-while loop
int main() {
    int stack[MAX];
    int top = -1;  // Initialize the top of the stack
    int choice;
    
    // Menu-driven interface with do-while loop
    do {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                display(stack, top);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);  // Exit when choice is 4
    
    return 0;
}
