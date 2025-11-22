#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for isdigit()

#define MAX 100

int stack[MAX];
int top = -1;

// Function to push an element onto the stack
void push(int value) {
    if (top == MAX - 1)
        printf("Stack Overflow!\n");
    else
        stack[++top] = value;
}

// Function to pop an element from the stack
int pop() {
    if (top == -1) {
        printf("Stack Underflow!\n");
        exit(1);
    } else {
        return stack[top--];
    }
}

// Function to evaluate a postfix expression
int evaluatePostfix(char exp[]) {
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        char ch = exp[i];

        // Skip spaces
        if (ch == ' ' || ch == '\t')
            continue;

        if (isdigit(ch)) {
            // Convert character digit to integer
            int num = ch - '0';
            push(num);
        } else {
            // Operator encountered
            int val2 = pop();
            int val1 = pop();

            switch (ch) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        exit(1);
                    }
                    push(val1 / val2); 
                    break;
                default:
                    printf("Error: Invalid operator '%c'\n", ch);
                    exit(1);
            }
        }
    }
    return pop();
}

int main() {
    char exp[MAX];

    printf("Enter a Postfix Expression (single-digit operands): ");
    fgets(exp, MAX, stdin);  // read expression including spaces

    int result = evaluatePostfix(exp);
    printf("Result = %d\n", result);

    return 0;
}
