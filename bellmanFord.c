#include <stdio.h>
#include <limits.h>

#define V 5     // number of vertices
#define E 9     // number of edges
#define SRC 0   // source = vertex 0 = s
#define INF INT_MAX

// human-readable names for printing
const char* name[V] = { "s", "t", "x", "y", "z" };

typedef struct {
    int u, v, w;
} Edge;

// the edge list for the graph
Edge edges[E] = {
    {0,1,  6},  // s→t
    {0,3,  7},  // s→y
    {1,2,  5},  // t→x
    {2,1, -2},  // x→t
    {1,3,  8},  // t→y
    {3,2, -3},  // y→x
    {1,4, -4},  // t→z
    {3,4,  9},  // y→z
    {4,2,  7}   // z→x
};

// prints the path from SRC to vertex v
void printPath(int v, int pi[]) {
    if (v == SRC) {
        printf("%s", name[v]);
        return;
    }
    if (pi[v] == -1) {
        // unreachable
        return;
    }
    printPath(pi[v], pi);
    printf(" → %s", name[v]);
}

int main(void) {
    int dist[V], pi[V];

    // 1) initialize distances and predecessors
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pi[i]   = -1;
    }
    dist[SRC] = 0;

    // 2) relax edges repeatedly
    for (int k = 0; k < V - 1; k++) {
        for (int i = 0; i < E; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pi[v]   = u;
            }
        }
    }

    // 3) check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Graph contains a negative-weight cycle\n");
            return 1;
        }
    }

    // 4) output results
    printf("Vertex   Dist   Predecessor    Path from s\n");
    printf("------   ----   -----------    -------------\n");
    for (int v = 0; v < V; v++) {
        // print vertex and distance
        if (dist[v] == INF)      printf("  %-3s     ∞      ", name[v]);
        else                     printf("  %-3s     %-5d ", name[v], dist[v]);

        // print predecessor
        if (pi[v] < 0)           printf("    NIL        ");
        else                     printf("    %-3s        ", name[pi[v]]);

        // print the path
        if (dist[v] != INF) {
            printPath(v, pi);
        }
        printf("\n");
    }

    return 0;
}
