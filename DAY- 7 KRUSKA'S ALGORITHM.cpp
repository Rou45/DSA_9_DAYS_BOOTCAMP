#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 9999

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge edge[MAX];
};

// Create a new graph
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    return graph;
}

// Find root of the vertex using union-find
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

// Union operation to join two subsets
void unionSet(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);

    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

// Compare two edges by their weights
int compare(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight - e2->weight;
}

// Kruskal's algorithm to find MST
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;  // Number of edges in MST
    int i = 0;  // Index for sorted edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    int parent[V], rank[V];
    for (i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    i = 0;
    while (e < V - 1 && i < graph->E) {
        struct Edge nextEdge = graph->edge[i++];

        int u = find(parent, nextEdge.u);
        int v = find(parent, nextEdge.v);

        if (u != v) {
            result[e++] = nextEdge;
            unionSet(parent, rank, u, v);
        }
    }

    printf("Edges in MST:\n");
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].u, result[i].v, result[i].weight);
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter edges (u, v, weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].u, &graph->edge[i].v, &graph->edge[i].weight);
    }

    kruskalMST(graph);

    return 0;
}
