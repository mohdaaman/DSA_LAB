#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;     // stack
struct Node *front = NULL;   // queue
struct Node *rear = NULL;    // queue

// -------- STACK --------
void push() {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter value: ");
    scanf("%d", &newNode->data);

    newNode->next = top;
    top = newNode;

    printf("Pushed into stack\n");
}

void pop() {
    if (top == NULL) {
        printf("Stack is empty\n");
    } else {
        struct Node *temp = top;
        top = top->next;
        free(temp);
        printf("Popped element\n");
    }
}

void displayStack() {
    struct Node *temp = top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// -------- QUEUE --------
void enqueue() {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    printf("Enter value: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("Inserted in queue\n");
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
    } else {
        struct Node *temp = front;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        free(temp);
        printf("Deleted from queue\n");
    }
}

void displayQueue() {
    struct Node *temp = front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int ch;

    while (1) {
        printf("\n1.Push 2.Pop 3.Display Stack");
        printf("\n4.Enqueue 5.Dequeue 6.Display Queue 7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: displayStack(); break;
            case 4: enqueue(); break;
            case 5: dequeue(); break;
            case 6: displayQueue(); break;
            case 7: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}
