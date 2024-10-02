#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Define maximum size of the queue

// Function to check if the queue is full
int isFull(int rear) {
    return rear == MAX - 1;
}

// Function to check if the queue is empty
int isEmpty(int front, int rear) {
    return front == -1 || front > rear;
}

// Function to add an element to the queue (Enqueue)
void enqueue(int queue[], int* front, int* rear, int value) {
    if (isFull(*rear)) {
        printf("Queue is full! Cannot enqueue %d\n", value);
    } else {
        if (*front == -1) {
            *front = 0;  // Initialize front if it's the first element
        }
        (*rear)++;
        queue[*rear] = value;
        printf("%d enqueued to the queue\n", value);
    }
}

// Function to remove an element from the queue (Dequeue)
void dequeue(int queue[], int* front, int* rear) {
    if (isEmpty(*front, *rear)) {
        printf("Queue is empty! Cannot dequeue.\n");
    } else {
        printf("%d dequeued from the queue\n", queue[*front]);
        (*front)++;
        // Reset queue if all elements are dequeued
        if (*front > *rear) {
            *front = -1;
            *rear = -1;
        }
    }
}

// Function to display the front element of the queue
void peek(int queue[], int front, int rear) {
    if (isEmpty(front, rear)) {
        printf("Queue is empty!\n");
    } else {
        printf("Front element is: %d\n", queue[front]);
    }
}

// Function to display the queue
void display(int queue[], int front, int rear) {
    if (isEmpty(front, rear)) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main() {
    int queue[MAX];  // Queue array
    int front = -1, rear = -1;  // Initialize front and rear
    int choice, value;

    do {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, &front, &rear, value);
                break;
            case 2:
                dequeue(queue, &front, rear);
                break;
            case 3:
                peek(queue, front, rear);
                break;
            case 4:
                display(queue, front, rear);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}