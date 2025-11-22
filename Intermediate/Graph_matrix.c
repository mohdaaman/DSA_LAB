#include <stdio.h>

int graph[10][10], vertices;

// Create graph
void createGraph() {
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }
    printf("Graph created\n");
}

// Insert edge
void insertEdge() {
    int u, v;
    printf("Enter two vertices (0 to %d): ", vertices-1);
    scanf("%d%d", &u, &v);

    graph[u][v] = 1;
    graph[v][u] = 1;

    printf("Edge inserted\n");
}

// Display matrix
void printGraph() {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Print adjacent vertices
void adjacentVertices() {
    int v;
    printf("Enter vertex: ");
    scanf("%d", &v);

    printf("Adjacent vertices of %d: ", v);
    for (int i = 0; i < vertices; i++) {
        if (graph[v][i] == 1)
            printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1.Create Graph\n2.Insert Edge");
        printf("\n3.Print Adjacency Matrix\n4.Find Adjacent Vertices\n5.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createGraph(); break;
            case 2: insertEdge(); break;
            case 3: printGraph(); break;
            case 4: adjacentVertices(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
