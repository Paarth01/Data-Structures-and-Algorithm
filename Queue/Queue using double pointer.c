#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the queue

// Function to check if the queue is empty
int isEmpty(int front, int rear) {
    return front == rear; // Queue is empty if front equals rear
}

// Function to check if the queue is full
int isFull(int rear) {
    return rear == MAX; // Queue is full if rear equals the maximum size
}

// Function to add an element to the queue
void enqueue(int** queue, int* rear, int data) {
    if (isFull(*rear)) {
        printf("Queue is full! Cannot enqueue %d\n", data);
        return;
    }
    (*queue)[*rear] = data; // Add data to the queue
    (*rear)++; // Move rear index up
    printf("%d enqueued to queue\n", data);
}

// Function to remove an element from the queue
int dequeue(int** queue, int* front, int rear) {
    if (isEmpty(*front, rear)) {
        printf("Queue is empty! Cannot dequeue\n");
        return -1; // Indicate that the queue is empty
    }
    int data = (*queue)[*front]; // Get the data from the front of the queue
    (*front)++; // Move front index up
    printf("%d dequeued from queue\n", data);
    return data;
}

// Function to display the queue
void displayQueue(int** queue, int front, int rear) {
    if (isEmpty(front, rear)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i < rear; i++) {
        printf("%d ", (*queue)[i]);
    }
    printf("\n");
}

// Main function with a menu-driven interface
int main() {
    int* queue = (int*)malloc(MAX * sizeof(int)); // Dynamic array to hold the queue elements
    int front = 0; // Index for the front of the queue
    int rear = 0; // Index for the rear of the queue
    int choice, data;

    do {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, &rear, data);
                break;
            case 2:
                dequeue(&queue, &front, rear);
                break;
            case 3:
                displayQueue(&queue, front, rear);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    free(queue); // Free the dynamically allocated queue
    return 0;
}
