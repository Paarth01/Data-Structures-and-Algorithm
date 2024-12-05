#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Function to initialize the hash table
void initializeTable(int table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = -1; // Use -1 to represent an empty slot
    }
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key into the hash table
void insert(int table[], int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Handle collisions using linear probing
    while (table[index] != -1 && table[index] != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Hash table is full, unable to insert key %d.\n", key);
            return;
        }
    }

    table[index] = key;
}

// Function to search for a key in the hash table
int search(int table[], int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (table[index] != -1) {
        if (table[index] == key) {
            return index; // Key found
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break; // Full loop, key not found
        }
    }

    return -1; // Key not found
}

// Function to display the hash table
void displayTable(int table[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != -1) {
            printf("Index %d: %d\n", i, table[i]);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    int table[TABLE_SIZE];
    initializeTable(table);

    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Display Table\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert(table, key);
                break;

            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                int result = search(table, key);
                if (result != -1) {
                    printf("Key %d found at index %d.\n", key, result);
                } else {
                    printf("Key %d not found in the hash table.\n", key);
                }
                break;

            case 3:
                displayTable(table);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}