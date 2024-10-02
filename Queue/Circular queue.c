#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Function prototypes
void initializeQueue(int* front, int* rear);
int isFull(int front, int rear);
int isEmpty(int front, int rear);
void enqueue(int queue[], int* front, int* rear, int value);
int dequeue(int queue[], int* front, int* rear);
int peek(int queue[], int front);
void display(int queue[], int front, int rear);

int main() {
    int queue[SIZE];  // Circular queue array
    int front, rear;  // Front and rear pointers
    initializeQueue(&front, &rear);  // Initialize front and rear
    
    int choice, value;

    do {
        printf("\nCircular Queue Operations Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, &front, &rear, value);
                break;

            case 2:
                value = dequeue(queue, &front, &rear);
                if (value != -1)
                    printf("Dequeued value: %d\n", value);
                break;

            case 3:
                value = peek(queue, front);
                if (value != -1)
                    printf("Peeked value: %d\n", value);
                break;

            case 4:
                display(queue, front, rear);
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Initialize the queue by setting front and rear to -1
void initializeQueue(int* front, int* rear) {
    *front = -1;
    *rear = -1;
}

// Check if the queue is full
int isFull(int front, int rear) {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1)) {
        return 1;
    }
    return 0;
}

// Check if the queue is empty
int isEmpty(int front, int rear) {
    if (front == -1) {
        return 1;
    }
    return 0;
}

// Enqueue operation
void enqueue(int queue[], int* front, int* rear, int value) {
    if (isFull(*front, *rear)) {
        printf("Queue is full! Cannot enqueue.\n");
    } else {
        if (*front == -1) {
            *front = 0;  // Set front to 0 if the queue is empty
        }
        *rear = (*rear + 1) % SIZE;
        queue[*rear] = value;
        printf("Enqueued %d to the queue.\n", value);
    }
}

// Dequeue operation
int dequeue(int queue[], int* front, int* rear) {
    int value;
    if (isEmpty(*front, *rear)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    } else {
        value = queue[*front];
        if (*front == *rear) {
            *front = -1;  // Reset front and rear if the queue is empty
            *rear = -1;
        } else {
            *front = (*front + 1) % SIZE;
        }
        return value;
    }
}

// Peek operation
int peek(int queue[], int front) {
    if (isEmpty(front, -1)) {
        printf("Queue is empty! Nothing to peek.\n");
        return -1;
    } else {
        return queue[front];
    }
}

// Display the queue
void display(int queue[], int front, int rear) {
    if (isEmpty(front, rear)) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (i != rear) {
            printf("%d ", queue[i]);
            i = (i + 1) % SIZE;
        }
        printf("%d\n", queue[i]);
    }
}