#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_V 20  // จำนวน vertices สูงสุด

// โครงสร้างของกราฟ
typedef struct {
    int V;                    // จำนวน vertices จริง
    int adjMatrix[MAX_V][MAX_V];  // adjacency matrix
} Graph;

// สร้างกราฟใหม่
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    
    // กำหนดค่าเริ่มต้นเป็น 0 (ไม่มี edge)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}

// เพิ่ม edge ในกราฟ (undirected)
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;  // สำหรับ undirected graph
}

// แสดงกราฟแบบ adjacency matrix
void printGraph(Graph* graph) {
    printf("\nAdjacency Matrix:\n");
    printf("     ");
    for (int i = 0; i < graph->V; i++) {
        printf("%4d", i);
    }
    printf("\n    ");
    for (int i = 0; i < graph->V; i++) {
        printf("----");
    }
    printf("\n");
    
    for (int i = 0; i < graph->V; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < graph->V; j++) {
            if (graph->adjMatrix[i][j] == 0) {
                printf("   -");
            } else {
                printf("%4d", graph->adjMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

// หา vertex ที่มีระยะทางน้อยที่สุดจากเซตของ vertices ที่ยังไม่ได้ประมวลผล
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX;
    int min_index = -1;
    
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

// แสดงเส้นทาง (recursive)
void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%d", vertex);
        return;
    }
    
    printPath(parent, parent[vertex]);
    printf(" -> %d", vertex);
}

// แสดงผลลัพธ์พร้อมเส้นทาง
void printSolution(int dist[], int parent[], int V, int src) {
    printf("\n\nShortest Path from vertex %d:\n", src);
    printf("=========================================\n");
    printf("Destination\tDistance\tPath\n");
    printf("-----------------------------------------\n");
    
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("%d\t\t", i);
            
            if (dist[i] == INT_MAX) {
                printf("INF\t\tNo path\n");
            } else {
                printf("%d\t\t", dist[i]);
                printPath(parent, i);
                printf("\n");
            }
        }
    }
}

// Dijkstra's Shortest Path Algorithm
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX_V];      // เก็บระยะทางที่สั้นที่สุด
    bool visited[MAX_V];  // เช็คว่า vertex ถูกประมวลผลหรือยัง
    int parent[MAX_V];    // เก็บ parent เพื่อ reconstruct path
    
    // 1. กำหนดค่าเริ่มต้น
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;    // ระยะทางเริ่มต้นเป็น infinity
        visited[i] = false;   // ยังไม่ได้เยี่ยมชม
        parent[i] = -1;       // ยังไม่มี parent
    }
    
    dist[src] = 0;  // ระยะทางจาก source ไปยังตัวเองเป็น 0
    
    printf("\nStep-by-step execution:\n");
    printf("========================\n");
    
    // 2. หาเส้นทางที่สั้นที่สุดสำหรับทุก vertex
    for (int count = 0; count < V - 1; count++) {
        // 2.1 เลือก vertex ที่มีระยะทางน้อยที่สุดและยังไม่ได้เยี่ยมชม
        int u = minDistance(dist, visited, V);
        
        if (u == -1) break;  // ไม่มี vertex ที่เข้าถึงได้แล้ว
        
        visited[u] = true;  // ทำเครื่องหมายว่าเยี่ยมชมแล้ว
        
        printf("Step %d: Visit vertex %d (distance = %d)\n", count + 1, u, dist[u]);
        
        // 2.2 อัพเดทระยะทางของ vertices ที่อยู่ติดกับ u
        for (int v = 0; v < V; v++) {
            // อัพเดทถ้า:
            // - ยังไม่ได้เยี่ยมชม v
            // - มี edge จาก u ไป v
            // - ระยะทางผ่าน u สั้นกว่าระยะทางปัจจุบัน
            if (!visited[v] && 
                graph->adjMatrix[u][v] != 0 && 
                dist[u] != INT_MAX && 
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;
                
                printf("   Update: vertex %d, new distance = %d\n", v, dist[v]);
            }
        }
    }
    
    // 3. แสดงผลลัพธ์
    printSolution(dist, parent, V, src);
}

int main() {
    int V = 9;  // จำนวน vertices
    Graph* graph = createGraph(V);
    
    printf("========================================\n");
    printf("  Dijkstra's Shortest Path Algorithm\n");
    printf("  Using Array (Adjacency Matrix)\n");
    printf("========================================\n");
    
    // สร้างกราฟตัวอย่าง
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
    
    // แสดงกราฟ
    printGraph(graph);
    
    // รัน Dijkstra's algorithm
    dijkstra(graph, 0);
    
    // ทดลองจาก source อื่น
    printf("\n\n");
    dijkstra(graph, 4);
    
    free(graph);
    return 0;
}