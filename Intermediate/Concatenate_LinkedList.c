#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createList() {
    struct Node *head = NULL, *temp = NULL, *newNode;
    int n, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter value: ");
        scanf("%d", &value);

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL) {
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    return head;
}

void display(struct Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

struct Node* concatenate(struct Node *head1, struct Node *head2) {
    if (head1 == NULL)
        return head2;

    struct Node *temp = head1;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = head2;
    return head1;
}

int main() {
    struct Node *head1, *head2, *head3;

    printf("Create first list:\n");
    head1 = createList();

    printf("Create second list:\n");
    head2 = createList();

    head3 = concatenate(head1, head2);

    printf("\nAfter concatenation:\n");
    display(head3);

    return 0;
}
