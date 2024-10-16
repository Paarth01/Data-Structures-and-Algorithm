#include <stdio.h>

#define MAX 100 // Define the maximum size of the queue

// Function prototypes
void insert(int[], int*, int);
void delete(int[], int*);
void display(int[], int);

// Main function
int main() {
    int queue[MAX];
    int size = 0; // Initially the queue is empty
    int choice, element;

    while (1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert element\n");
        printf("2. Delete highest priority element\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (size == MAX) {
                    printf("Queue is full!\n");
                } else {
                    printf("Enter element to insert: ");
                    scanf("%d", &element);
                    insert(queue, &size, element);
                }
                break;

            case 2:
                if (size == 0) {
                    printf("Queue is empty!\n");
                } else {
                    delete(queue, &size);
                }
                break;

            case 3:
                if (size == 0) {
                    printf("Queue is empty!\n");
                } else {
                    display(queue, size);
                }
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Function to insert an element into the priority queue
void insert(int queue[], int* size, int element) {
    int i;

    // Shift elements to the right to find the correct position
    for (i = *size - 1; i >= 0 && queue[i] > element; i--) {
        queue[i + 1] = queue[i];
    }

    // Insert the element at the correct position
    queue[i + 1] = element;
    (*size)++;
    printf("Inserted %d into the queue.\n", element);
}

// Function to delete the highest-priority element (smallest value)
void delete(int queue[], int* size) {
    printf("Deleted %d from the queue.\n", queue[0]);

    // Shift elements to the left
    for (int i = 0; i < *size - 1; i++) {
        queue[i] = queue[i + 1];
    }

    (*size)--;
}

// Function to display the priority queue
void display(int queue[], int size) {
    printf("Priority Queue: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}
