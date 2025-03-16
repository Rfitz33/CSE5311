#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef struct queue {
    node_t *head;
    node_t *tail;
    size_t size;
} queue_t;

// Create a new node with the given data.
node_t *node_create(int data) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Create an empty queue.
queue_t *queue_create() {
    queue_t *queue = malloc(sizeof(queue_t));
    if (queue == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

// Enqueue: add an element to the end of the queue.
void enqueue(queue_t *queue, int data) {
    node_t *new_node = node_create(data);
    if (queue->tail == NULL) { // Queue is empty.
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
}

// Dequeue: remove an element from the front of the queue.
int dequeue(queue_t *queue) {
    if (queue->head == NULL) {
        fprintf(stderr, "Error: Queue underflow.\n");
        exit(EXIT_FAILURE);
    }
    node_t *temp = queue->head;
    int data = temp->data;
    queue->head = temp->next;
    if (queue->head == NULL) { // If the queue becomes empty, update tail.
        queue->tail = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

// Return the current size of the queue.
size_t queue_size(queue_t *queue) {
    return queue->size;
}

// Free all nodes and the queue structure.
void queue_free(queue_t *queue) {
    if (queue == NULL)
        return;
    node_t *current = queue->head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

int main(void) {
    // Create a new queue.
    queue_t *queue = queue_create();

    // Enqueue some elements.
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    // Print the queue by dequeuing all elements.
    printf("Queue elements (FIFO order):\n");
    while (queue_size(queue) > 0) {
        printf("%d \n", dequeue(queue));
    }
    printf("\n");

    // Free the queue.
    queue_free(queue);

    return 0;
}
