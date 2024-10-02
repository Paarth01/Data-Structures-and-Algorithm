#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Maximum size of the stack

// Function prototypes
void push(char stack[], int *top, char value);
char pop(char stack[], int *top);
char peek(char stack[], int top);
int precedence(char symbol);
int isOperator(char symbol);
int isOperand(char symbol);
void infixToPostfix(char infix[], char postfix[], char stack[], int *top);

// Main function
int main() {
    char infix[MAX], postfix[MAX], stack[MAX];
    int top = -1;

    printf("Enter an infix expression: ");
    gets(infix);  // Read infix expression

    infixToPostfix(infix, postfix, stack, &top);  // Convert infix to postfix

    printf("Postfix expression: %s\n", postfix);  // Output postfix expression
    return 0;
}

// Function to push an element onto the stack
void push(char stack[], int *top, char value) {
    if (*top == (MAX - 1)) {
        printf("Stack overflow!\n");
        exit(1);
    } else {
        stack[++(*top)] = value;
    }
}

// Function to pop an element from the stack
char pop(char stack[], int *top) {
    if (*top == -1) {
        printf("Stack underflow!\n");
        exit(1);
    } else {
        return stack[(*top)--];
    }
}

// Function to peek the top element of the stack
char peek(char stack[], int top) {
    if (top == -1) {
        return -1;
    } else {
        return stack[top];
    }
}

// Custom function to check if a character is an operator
int isOperator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^');
}

// Custom function to check if a character is an operand (letter or digit)
int isOperand(char symbol) {
    return ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9'));
}

// Function to determine the precedence of operators
int precedence(char symbol) {
    switch (symbol) {
        case '^':
            return 3;  // Highest precedence
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char infix[], char postfix[], char stack[], int *top) {
    int i = 0, j = 0;  // Initialize indices for infix and postfix expressions
    char symbol, temp;

    while ((symbol = infix[i++]) != '\0') {
        // If the symbol is an operand, add it to the postfix expression
        if (isOperand(symbol)) {
            postfix[j++] = symbol;
        }
        // If the symbol is '(', push it onto the stack
        else if (symbol == '(') {
            push(stack, top, symbol);
        }
        // If the symbol is ')', pop from the stack and add to postfix until '(' is found
        else if (symbol == ')') {
            while ((temp = pop(stack, top)) != '(') {
                postfix[j++] = temp;
            }
        }
        // If the symbol is an operator
        else if (isOperator(symbol)) {
            while (*top != -1 && precedence(peek(stack, *top)) >= precedence(symbol)) {
                postfix[j++] = pop(stack, top);
            }
            push(stack, top, symbol);  // Push the current operator onto the stack
        }
    }

    // Pop all remaining operators from the stack
    while (*top != -1) {
        postfix[j++] = pop(stack, top);
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
}