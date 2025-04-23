#include <stdio.h>
#include <limits.h>

#define V   5
#define INF INT_MAX

// for printing
const char* name[V] = {"s","t","x","y","z"};

// pick the next vertex u not yet in the SPT with minimal dist[u]
int minDistance(int dist[V], int used[V]) {
    int min = INF, min_index = -1;
    for(int v = 0; v < V; v++) {
        if (!used[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// recursively print the s→...→j path
void printPath(int pi[V], int j) {
    if (pi[j] == -1) {
        printf("%s", name[j]);
        return;
    }
    printPath(pi, pi[j]);
    printf(" → %s", name[j]);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V], used[V], pi[V];

    // initialization
    for(int i = 0; i < V; i++) {
        dist[i] = INF;
        used[i] = 0;
        pi[i]   = -1;
    }
    dist[src] = 0;

    // main loop
    for(int count = 0; count < V-1; count++) {
        int u = minDistance(dist, used);
        if (u < 0) break;        // all reachable done
        used[u] = 1;
        // relax all edges u→v
        for(int v = 0; v < V; v++) {
            if (!used[v] 
                && graph[u][v] != INF 
                && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + graph[u][v];
                pi[v]   = u;
            }
        }
    }

    // print results
    printf("Vertex  Dist  Predecessor   Path from s\n");
    printf("------  ----  -----------   -------------\n");
    for(int i = 0; i < V; i++) {
        // print name and dist
        if (dist[i] == INF) {
            printf("  %-3s    ∞    ", name[i]);
        } else {
            printf("  %-3s    %-3d  ", name[i], dist[i]);
        }
        // print predecessor
        printf("   %-6s     ", (pi[i]<0 ? "NIL" : name[pi[i]]));
        // print path
        if (dist[i] != INF) {
            printPath(pi, i);
        }
        printf("\n");
    }
}

int main() {
    // corrected adjacency‐matrix
    int graph[V][V] = {
      /*  s    t    x    y    z   */
      {   0,  10, INF,   5, INF },  /* s */
      { INF,   0,   1,   2, INF },  /* t */
      { INF, INF,   0, INF,   4 },  /* x */
      { INF,   3,   9,   0,   2 },  /* y */
      {   7, INF,   6, INF,   0 }   /* z */
    };

    dijkstra(graph, 0);  // source = s = index 0
    return 0;
}
