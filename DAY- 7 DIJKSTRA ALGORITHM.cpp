#include <stdio.h>
#define INF 9999
#define MAX 5

void dijkstra(int graph[MAX][MAX], int n, int start) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, minDistance, nextNode, i, j;

    // Create cost matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (graph[i][j] == 0)
                cost[i][j] = INF;
            else
                cost[i][j] = graph[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1) {
        minDistance = INF;

        for (i = 0; i < n; i++) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                nextNode = i;
            }
        }

        visited[nextNode] = 1;
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                if (minDistance + cost[nextNode][i] < distance[i]) {
                    distance[i] = minDistance + cost[nextNode][i];
                    pred[i] = nextNode;
                }
            }
        }
        count++;
    }

    for (i = 0; i < n; i++) {
        if (i != start) {
            printf("\nDistance from node %d to node %d is: %d", start, i, distance[i]);
        }
    }
}

int main() {
    int graph[MAX][MAX] = {
        {0, 10, 0, 0, 5},
        {10, 0, 1, 0, 2},
        {0, 1, 0, 4, 0},
        {0, 0, 4, 0, 3},
        {5, 2, 0, 3, 0}
    };
    int n = 5;
    int start = 0;

    printf("Dijkstra's Algorithm\n");
    dijkstra(graph, n, start);
    return 0;
}
