#include <stdio.h>
#include <limits.h>

#define V 5
// Use a large value that won’t overflow when added
#define INF (INT_MAX/2)

// Human-readable vertex names
const char* name[V] = { "1", "2", "3", "4", "5" };

int main(void) {
    int dist[V][V];
    int i, j, k;

    // 1) Build initial distance (adjacency) matrix from the corrected graph
    //    Rows and cols correspond to vertices 1–5 in order.
    int G[V][V] = {
        /* 1      2    3      4      5  */
        {   0,    3,    8,  INF,   -4 },  // from 1
        { INF,    0,  INF,    1,    7  },  // from 2
        { INF,    4,    0,  INF,  INF  },  // from 3
        {   2,  INF,   -5,    0,  INF  },  // from 4
        { INF,  INF,  INF,    6,    0  }   // from 5
    };

    // copy into working dist matrix
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = G[i][j];
        }
    }

    // 2) Floyd–Warshall: consider each k as an intermediate
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 3) Print the final shortest-path distance matrix
    printf("      ");
    for (i = 0; i < V; i++) {
        printf(" %2s  ", name[i]);
    }
    printf("\n");

    for (i = 0; i < V; i++) {
        // row label
        printf("%2s |", name[i]);
        for (j = 0; j < V; j++) {
            if (dist[i][j] >= INF/2) // unreachable
                printf("  INF");
            else
                printf(" %4d", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
