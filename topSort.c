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
    /* Example usage from figure 22.8 */
    int V = 14;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 4);
    addEdge(graph, 0, 5);
    addEdge(graph, 0, 11);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 8);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 2, 9);
    addEdge(graph, 3, 2);
    addEdge(graph, 3, 6);
    addEdge(graph, 3, 13);
    addEdge(graph, 4, 7);
    addEdge(graph, 5, 8);
    addEdge(graph, 5, 12);
    addEdge(graph, 6, 5);
    addEdge(graph, 8, 7);
    addEdge(graph, 9, 10);
    addEdge(graph, 9, 11);
    addEdge(graph, 10, 13);
    addEdge(graph, 12, 9);

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
