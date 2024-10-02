#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to check if the queue is empty
int isEmpty(int size) {
    return size == 0;
}

// Function to check if the queue is full
int isFull(int size) {
    return size == MAX;
}

// Function to enqueue an element into the priority queue
void enqueue(int data[], int priority[], int *size, int value, int prio) {
    if (isFull(*size)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    int i;
    // Traverse the queue to find the correct position to insert based on priority
    for (i = *size - 1; i >= 0 && priority[i] > prio; i--) {
        data[i + 1] = data[i];
        priority[i + 1] = priority[i];
    }

    // Insert the new element at the correct position
    data[i + 1] = value;
    priority[i + 1] = prio;
    (*size)++;
    printf("Enqueued: Data = %d, Priority = %d\n", value, prio);
}

// Function to dequeue the highest priority element (lowest priority value)
void dequeue(int data[], int priority[], int *size) {
    if (isEmpty(*size)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    // Dequeue the element with the highest priority (first element)
    printf("Dequeued: Data = %d, Priority = %d\n", data[0], priority[0]);

    // Shift the rest of the elements to the left
    for (int i = 1; i < *size; i++) {
        data[i - 1] = data[i];
        priority[i - 1] = priority[i];
    }
    (*size)--;
}

// Function to peek at the element with the highest priority
void peek(int data[], int priority[], int size) {
    if (isEmpty(size)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Peek: Data = %d, Priority = %d\n", data[0], priority[0]);
}

// Function to display all elements in the priority queue
void display(int data[], int priority[], int size) {
    if (isEmpty(size)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Priority Queue elements:\n");
    for (int i = 0; i < size; i++) {
        printf("Data = %d, Priority = %d\n", data[i], priority[i]);
    }
}

// Main function
int main() {
    int data[MAX];      // Array to store data
    int priority[MAX];  // Array to store priorities
    int size = 0;       // Number of elements in the queue
    int choice, value, prio;

    do {
        printf("\nPriority Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &value);
                printf("Enter priority: ");
                scanf("%d", &prio);
                enqueue(data, priority, &size, value, prio);
                break;
            case 2:
                dequeue(data, priority, &size);
                break;
            case 3:
                peek(data, priority, size);
                break;
            case 4:
                display(data, priority, size);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);  // Continue until the user chooses to exit

    return 0;
}