#include <stdio.h>
#include <stdlib.h>

// Define a structure for a polynomial term
struct Node {
    int coeff;  // Coefficient
    int exp;    // Exponent
    struct Node* next;  // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node in a sorted order (by exponent)
struct Node* insertNode(struct Node* head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);

    if (head == NULL || head->exp < exp) {
        newNode->next = head;
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->exp >= exp) {
        temp = temp->next;
    }

    if (temp->exp == exp) {
        temp->coeff += coeff;  // Combine like terms
        free(newNode);  // No need to insert a new node, so free it
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return head;
}

// Function to display a polynomial
void displayPoly(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->exp);
        head = head->next;
        if (head != NULL)
            printf(" + ");
    }
    printf("\n");
}

// Function to add two polynomials
struct Node* addPoly(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            result = insertNode(result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            result = insertNode(result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            result = insertNode(result, poly1->coeff + poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Add remaining terms of poly1, if any
    while (poly1 != NULL) {
        result = insertNode(result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    // Add remaining terms of poly2, if any
    while (poly2 != NULL) {
        result = insertNode(result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;
    int n, coeff, exp;

    // Input for first polynomial
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        poly1 = insertNode(poly1, coeff, exp);
    }

    // Input for second polynomial
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        poly2 = insertNode(poly2, coeff, exp);
    }

    printf("Polynomial 1: ");
    displayPoly(poly1);

    printf("Polynomial 2: ");
    displayPoly(poly2);

    // Add the two polynomials
    sum = addPoly(poly1, poly2);

    printf("Sum: ");
    displayPoly(sum);

    return 0;
}
