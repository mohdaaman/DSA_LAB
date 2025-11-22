#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Function to push onto stack
void push(char c) {
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = c;
}

// Function to pop from stack
char pop() {
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

// Function to return precedence of operators
int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

// Function to convert infix to postfix
void infixToPostfix(char infix[]) {
    char postfix[MAX];
    int i = 0, k = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        if (ch == ' ' || ch == '\t')
            continue;

        // If the character is an operand, add it to output
        if (isalnum(ch))
            postfix[k++] = ch;

        // If it's '(', push to stack
        else if (ch == '(')
            push(ch);

        // If it's ')', pop until '(' is found
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '(' from stack
        }

        // If operator
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(ch))
                postfix[k++] = pop();
            push(ch);
        }
    }

    // Pop remaining operators
    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
    printf("Postfix Expression: %s\n", postfix);
}

// Main function
int main() {
    char infix[MAX];

    printf("Enter an Infix Expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // remove newline

    infixToPostfix(infix);

    return 0;
}
