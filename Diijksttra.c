#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20
#define NO_EDGE 0
#define INFINITY_DIST INT_MAX

typedef struct
{
    int vertexCount;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;
Graph *createGraph(int vertexCount)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertexCount;

    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            graph->adjMatrix[i][j] = NO_EDGE;
        }
    }

    return graph;
}

void addEdge(Graph *graph, int source, int destination, int weight)
{
    graph->adjMatrix[source][destination] = weight;
    graph->adjMatrix[destination][source] = weight;
}

void printGraph(Graph *graph)
{
    printf("\nAdjacency Matrix:\n");

    printf("     ");
    for (int i = 0; i < graph->vertexCount; i++)
    {
        printf("%4d", i);
    }
    printf("\n    ");

    for (int i = 0; i < graph->vertexCount; i++)
    {
        printf("----");
    }
    printf("\n");

    for (int i = 0; i < graph->vertexCount; i++)
    {
        printf("%2d | ", i);
        for (int j = 0; j < graph->vertexCount; j++)
        {
            if (graph->adjMatrix[i][j] == NO_EDGE)
            {
                printf("   -");
            }
            else
            {
                printf("%4d", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

int findMinDistanceVertex(int distance[], bool visited[], int vertexCount)
{
    int minDistance = INFINITY_DIST;
    int minVertex = -1;

    for (int v = 0; v < vertexCount; v++)
    {
        if (!visited[v] && distance[v] <= minDistance)
        {
            minDistance = distance[v];
            minVertex = v;
        }
    }
    return minVertex;
}

void printPath(int parent[], int vertex)
{

    if (parent[vertex] == -1)
    {
        printf("%d", vertex);
        return;
    }

    printPath(parent, parent[vertex]);
    printf(" -> %d", vertex);
}

void showShortestPaths(int distance[], int parent[], int vertexCount, int source)
{

    printf("=========================================\n");
    printf("Destination\tDistance\tPath\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < vertexCount; i++)
    {
        if (i != source)
        {
            printf("%d\t\t", i);

            if (distance[i] != INFINITY_DIST)
            {
                printf("%d\t\t", distance[i]);
                printPath(parent, i);
                printf("\n");
            }
            else
            {
                printf("No path\n");
            }
        }
    }
    printf("=========================================\n");
}

void dijkstra(Graph *graph, int source)
{
    int vertexCount = graph->vertexCount;
    int distance[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    for (int i = 0; i < vertexCount; i++)
    {
        distance[i] = INFINITY_DIST;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[source] = 0;

    printf("\n\nShortest Path from vertex %d:\n", source);
    printf("-----------------------------------------\n");

    for (int count = 0; count < vertexCount - 1; count++)
    {
        int currentVertex = findMinDistanceVertex(distance, visited, vertexCount);

        if (currentVertex == -1)
        {
            break;
        }
        visited[currentVertex] = true;

        printf("Step %d: Visit vertex %d (distance = %d)\n",
               count + 1, currentVertex, distance[currentVertex]);

        for (int neighbor = 0; neighbor < vertexCount; neighbor++)
        {
            int edgeWeight = graph->adjMatrix[currentVertex][neighbor];

            bool hasEdge = (edgeWeight != NO_EDGE);
            bool isReachable = (distance[currentVertex] != INFINITY_DIST);
            bool isShorterPath = (distance[currentVertex] + edgeWeight < distance[neighbor]);

            if (!visited[neighbor] && hasEdge && isReachable && isShorterPath)
            {
                distance[neighbor] = distance[currentVertex] + edgeWeight;
                parent[neighbor] = currentVertex;

                printf("   Update: vertex %d, new distance = %d\n",
                       neighbor, distance[neighbor]);
            }
        }
    }

    showShortestPaths(distance, parent, vertexCount, source);
}

int main()
{
    printf("========================================\n");
    printf("  Dijkstra's Algorithm\n");
    printf("  Using Adjacency Matrix\n");
    printf("========================================\n");

    int vertexCount = 9;
    Graph *graph = createGraph(vertexCount);

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    printGraph(graph);

    printf("\n========================================");

    dijkstra(graph, 0);

    printf("\n");

    dijkstra(graph, 4);

    free(graph);

    return 0;
}