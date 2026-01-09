#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_Vertices 20

typedef struct
{
    int V;
    int adjMatrix[MAX_Vertices][MAX_Vertices];
} Graph;

Graph *createGraph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

void printGraph(Graph *graph)
{
    printf("\nAdjacency Matrix:\n");
    printf("     ");
    for (int i = 0; i < graph->V; i++)
    {
        printf("%4d", i);
    }
    printf("\n    ");
    for (int i = 0; i < graph->V; i++)
    {
        printf("----");
    }
    printf("\n");

    for (int i = 0; i < graph->V; i++)
    {
        printf("%2d | ", i);
        for (int j = 0; j < graph->V; j++)
        {
            if (graph->adjMatrix[i][j] == 0)
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

int minDistance(int dist[], bool visited[], int V)
{
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
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

void showResult(int dist[], int parent[], int V, int src)
{
    printf("=========================================\n");
    printf("Destination\tDistance\tPath\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < V; i++)
    {
        if (i != src)
        {
            printf("%d\t\t\t", i);

            if (dist[i] != INT_MAX)
            {
                printf("%d\t\t\t", dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    }
}

void dijkstra(Graph *graph, int src)
{
    int V = graph->V;
    int dist[MAX_Vertices];
    bool visited[MAX_Vertices];
    int parent[MAX_Vertices];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;
    printf("\n");
    printf("\n\nShortest Path from vertex %d:\n", src);

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited, V);

        if (u == -1)
            break;

        visited[u] = true;

        printf("Step %d: Visit vertex %d (distance = %d)\n", count + 1, u, dist[u]);

        for (int v = 0; v < V; v++)
        {

            if (!visited[v] &&
                graph->adjMatrix[u][v] != 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph->adjMatrix[u][v] < dist[v])
            {

                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;

                printf("   Update: vertex %d, new distance = %d\n", v, dist[v]);
            }
        }
    }

    showResult(dist, parent, V, src);
}

int main()
{
    int V = 9;
    Graph *graph = createGraph(V);

    printf("========================================\n");
    printf("  Dijkstra's Algorithm\n");
    printf("  Using Adjacency Matrix\n");
    printf("========================================\n");

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

    printf("========================================");

    dijkstra(graph, 0);

    printf("\n");

    dijkstra(graph, 4);

    free(graph);
    return 0;
}