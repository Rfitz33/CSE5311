#include <stdio.h>
#include <stdlib.h>

#define V 9    // number of vertices (a,b,c,d,e,f,g,h,i)
#define E 14   // number of edges

// an edge from src→dest with given weight
typedef struct {
    int src, dest, weight;
} Edge;

// for union–find
typedef struct {
    int parent, rank;
} Subset;

// find set with path compression
int findSet(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = findSet(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// union by rank
void unionSets(Subset subsets[], int x, int y) {
    int xroot = findSet(subsets, x);
    int yroot = findSet(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// sort edges by ascending weight
int cmpEdge(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskalMST(Edge edges[]) {
    // will store the edges of the MST (we need V–1 of them)
    Edge result[V - 1];
    int e = 0;  // result[] counter
    int i = 0;  // sorted edges counter

    // 1) sort all edges by weight
    qsort(edges, E, sizeof(Edge), cmpEdge);

    // 2) create V subsets with single elements
    Subset *subsets = malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank   = 0;
    }

    // 3) pick the smallest edge and see if it forms a cycle
    while (e < V - 1 && i < E) {
        Edge next = edges[i++];
        int x = findSet(subsets, next.src);
        int y = findSet(subsets, next.dest);

        // if it doesn't form a cycle, include it
        if (x != y) {
            result[e++] = next;
            unionSets(subsets, x, y);
        }
    }

    // 4) print the MST
    char name[V] = {'a','b','c','d','e','f','g','h','i'};
    int totalWeight = 0;
    printf("Edges in the MST:\n");
    for (i = 0; i < e; i++) {
        printf("  %c - %c  : %d\n",
               name[result[i].src],
               name[result[i].dest],
               result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST = %d\n", totalWeight);

    free(subsets);
}

int main() {
    // Example graph from figure 23.4
    Edge edges[E] = {
        {0, 1,  4},  // a-b
        {0, 7,  8},  // a-h
        {1, 7, 11},  // b-h
        {1, 2,  8},  // b-c
        {2, 3,  7},  // c-d
        {3, 4,  9},  // d-e
        {4, 5, 10},  // e-f
        {3, 5, 14},  // d-f
        {2, 5,  4},  // c-f
        {2, 8,  2},  // c-i
        {8, 7,  7},  // i-h
        {8, 6,  6},  // i-g
        {7, 6,  1},  // h-g
        {5, 6,  2}   // f-g
    };

    kruskalMST(edges);
    return 0;
}
