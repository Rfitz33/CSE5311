#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* A node in the adjacency list */
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

/* A directed graph */
typedef struct {
    int V;        // number of vertices
    Node** adj;   // array of adjacency‑list heads
} Graph;

/* Create a new adjacency‑list node */
Node* newNode(int dest) {
    Node* node = malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

/* Create a graph of V vertices */
Graph* createGraph(int V) {
    Graph* graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = calloc(V, sizeof(Node*));
    return graph;
}

/* Add a directed edge src → dest */
void addEdge(Graph* graph, int src, int dest) {
    Node* node = newNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
}

/* Utility function: recursively visits from vertex v */
void dfsUtil(Graph* graph, int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);

    for (Node* p = graph->adj[v]; p != NULL; p = p->next) {
        if (!visited[p->dest]) {
            dfsUtil(graph, p->dest, visited);
        }
    }
}

/* Performs DFS traversal from a given start vertex. */
void depthFirstSearch(Graph* graph, int start) {
    bool* visited = calloc(graph->V, sizeof(bool));
    printf("DFS starting at vertex %d: ", start);
    dfsUtil(graph, start, visited);
    printf("\n");
    free(visited);
}

int main() {
    /* Create a graph with 6 vertices */
    int V = 6;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    /* Run DFS from vertex 0 */
    depthFirstSearch(graph, 0);

    /* Cleanup */
    for (int i = 0; i < V; i++) {
        Node* p = graph->adj[i];
        while (p) {
            Node* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(graph->adj);
    free(graph);

    return 0;
}
