#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Graph structure using adjacency matrix
struct Graph {
    int adjMatrix[MAX][MAX];  // Matrix to represent graph
    int numVertices;          // Number of vertices in the graph
};

// Function to create a graph
void createGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;  // Initialize matrix with 0s
        }
    }
}

// Add edge between two vertices
void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;  // For undirected graph
}

// Display the adjacency matrix
void displayGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph graph;
    createGraph(&graph, 4);
    
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    
    printf("Adjacency Matrix:\n");
    displayGraph(&graph);

    return 0;
}
