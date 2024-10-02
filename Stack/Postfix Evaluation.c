#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Define maximum stack size

// Function to push an element onto the stack
void push(int stack[], int *top, int value) {
    if (*top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    stack[++(*top)] = value;
}

// Function to pop an element from the stack
int pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow!\n");
        exit(1);  // Exit if there are no operands to pop
    }
    return stack[(*top)--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* expression) {
    int stack[MAX];
    int top = -1;
    int i = 0, operand1, operand2, result;

    // Traverse the postfix expression
    while (expression[i] != '\0') {
        // If the character is a digit (0-9), push it onto the stack
        if (expression[i] >= '0' && expression[i] <= '9') {
            int num = expression[i] - '0';  // Manually convert char to int
            push(stack, &top, num);
        }
        // If the character is an operator, pop two operands and perform the operation
        else {
            operand2 = pop(stack, &top);
            operand1 = pop(stack, &top);

            switch (expression[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero error!\n");
                        exit(1);
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator encountered: %c\n", expression[i]);
                    exit(1);
            }

            // Push the result back onto the stack
            push(stack, &top, result);
        }

        i++;  // Move to the next character in the expression
    }

    // The final result will be the only element in the stack
    return pop(stack, &top);
}

// Main function using do-while loop
int main() {
    char postfix[MAX];
    int result, choice;

    // Menu-driven interface with do-while loop
    do {
        printf("\n--- Postfix Evaluation Menu ---\n");
        printf("1. Evaluate Postfix Expression\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a valid postfix expression: ");
                scanf("%s", postfix);
                result = evaluatePostfix(postfix);
                printf("The result of the postfix expression is: %d\n", result);
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 2);  // Exit when choice is 2

    return 0;
}