#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX], front = -1, rear = -1;
int visited[MAX];

// Add an element to the queue
void enqueue(int vertex) {
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = vertex;
}

// Remove an element from the queue
int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

// BFS traversal
void bfs(int graph[MAX][MAX], int startVertex, int vertices) {
    enqueue(startVertex);
    visited[startVertex] = 1;

    while (front <= rear) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int graph[MAX][MAX] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    int vertices = 4;
    for (int i = 0; i < vertices; i++)
        visited[i] = 0;

    printf("BFS Traversal:\n");
    bfs(graph, 0, vertices);
    return 0;
}
