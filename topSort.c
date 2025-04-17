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
    Node** adj;   // array of adjacency‐list heads
} Graph;

/* Create a new adjacency‐list node */
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
    graph->adj = malloc(V * sizeof(Node*));
    for (int i = 0; i < V; ++i)
        graph->adj[i] = NULL;
    return graph;
}

/* Add a directed edge src→dest */
void addEdge(Graph* graph, int src, int dest) {
    Node* node = newNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
}

/* Utility function for DFS-based topological sort */
void tsUtil(int v, bool visited[], int stack[], int *top, Graph* graph) {
    visited[v] = true;
    for (Node* p = graph->adj[v]; p != NULL; p = p->next) {
        if (!visited[p->dest])
            tsUtil(p->dest, visited, stack, top, graph);
    }
    /* push current vertex onto stack */
    stack[++(*top)] = v;
}

/* Perform topological sort and print the result */
void topologicalSort(Graph* graph) {
    int V = graph->V;
    bool* visited = calloc(V, sizeof(bool));
    int* stack = malloc(V * sizeof(int));
    int top = -1;

    /* Call recursive helper for all vertices */
    for (int i = 0; i < V; i++)
        if (!visited[i])
            tsUtil(i, visited, stack, &top, graph);

    /* Print contents of stack (reverse finishing times) */
    printf("Topological order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");

    free(visited);
    free(stack);
}

int main() {
    /* Example usage */
    int V = 6;
    Graph* graph = createGraph(V);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    /* Cleanup adjacency lists */
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
