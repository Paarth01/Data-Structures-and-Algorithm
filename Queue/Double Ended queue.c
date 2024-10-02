#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Function prototypes
int isFull(int front, int rear);
int isEmpty(int front);
void enqueueFront(int deque[], int* front, int* rear, int x);
void enqueueRear(int deque[], int* front, int* rear, int x);
int dequeueFront(int deque[], int* front, int* rear);
int dequeueRear(int deque[], int* front, int* rear);
int peekFront(int deque[], int front);
int peekRear(int deque[], int rear);
void displayDeque(int deque[], int front, int rear);

int main() {
    int deque[MAX];
    int front = -1, rear = -1;  // Initialize front and rear to -1
    int choice, element;

    do {
        printf("\n--- Double Ended Queue Operations ---");
        printf("\n1. Enqueue from Front");
        printf("\n2. Enqueue from Rear");
        printf("\n3. Dequeue from Front");
        printf("\n4. Dequeue from Rear");
        printf("\n5. Peek Front");
        printf("\n6. Peek Rear");
        printf("\n7. Display");
        printf("\n8. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to enqueue from front: ");
                scanf("%d", &element);
                enqueueFront(deque, &front, &rear, element);
                break;
            case 2:
                printf("Enter element to enqueue from rear: ");
                scanf("%d", &element);
                enqueueRear(deque, &front, &rear, element);
                break;
            case 3:
                element = dequeueFront(deque, &front, &rear);
                if (element != -1)
                    printf("Dequeued element from front: %d\n", element);
                break;
            case 4:
                element = dequeueRear(deque, &front, &rear);
                if (element != -1)
                    printf("Dequeued element from rear: %d\n", element);
                break;
            case 5:
                element = peekFront(deque, front);
                if (element != -1)
                    printf("Front element is: %d\n", element);
                break;
            case 6:
                element = peekRear(deque, rear);
                if (element != -1)
                    printf("Rear element is: %d\n", element);
                break;
            case 7:
                displayDeque(deque, front, rear);
                break;
            case 8:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);  // Continue until the user chooses to exit

    return 0;
}

// Check if Deque is full
int isFull(int front, int rear) {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

// Check if Deque is empty
int isEmpty(int front) {
    return (front == -1);
}

// Enqueue from front
void enqueueFront(int deque[], int* front, int* rear, int x) {
    if (isFull(*front, *rear)) {
        printf("Deque is full! Cannot enqueue.\n");
        return;
    }
    if (*front == -1) { // If deque is empty
        *front = *rear = 0;
    } else if (*front == 0) { // Circular enqueue
        *front = MAX - 1;
    } else {
        (*front)--;
    }
    deque[*front] = x;
}

// Enqueue from rear
void enqueueRear(int deque[], int* front, int* rear, int x) {
    if (isFull(*front, *rear)) {
        printf("Deque is full! Cannot enqueue.\n");
        return;
    }
    if (*front == -1) { // If deque is empty
        *front = *rear = 0;
    } else if (*rear == MAX - 1) { // Circular enqueue
        *rear = 0;
    } else {
        (*rear)++;
    }
    deque[*rear] = x;
}

// Dequeue from front
int dequeueFront(int deque[], int* front, int* rear) {
    if (isEmpty(*front)) {
        printf("Deque is empty! Cannot dequeue.\n");
        return -1;
    }
    int data = deque[*front];
    if (*front == *rear) { // If deque has only one element
        *front = *rear = -1;
    } else if (*front == MAX - 1) { // Circular dequeue
        *front = 0;
    } else {
        (*front)++;
    }
    return data;
}

// Dequeue from rear
int dequeueRear(int deque[], int* front, int* rear) {
    if (isEmpty(*front)) {
        printf("Deque is empty! Cannot dequeue.\n");
        return -1;
    }
    int data = deque[*rear];
    if (*front == *rear) { // If deque has only one element
        *front = *rear = -1;
    } else if (*rear == 0) { // Circular dequeue
        *rear = MAX - 1;
    } else {
        (*rear)--;
    }
    return data;
}

// Peek front element
int peekFront(int deque[], int front) {
    if (isEmpty(front)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque[front];
}

// Peek rear element
int peekRear(int deque[], int rear) {
    if (isEmpty(rear)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return deque[rear];
}

// Display the deque
void displayDeque(int deque[], int front, int rear) {
    if (isEmpty(front)) {
        printf("Deque is empty!\n");
        return;
    }

    printf("Deque elements are: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}