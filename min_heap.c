#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int key;
    void *data;
} Node;

typedef struct {
    Node *array;
    int size;
    int capacity;
} MinHeap;

void min_heapify(MinHeap *heap, int i) {
    int l = (i << 1) + 1;
    int r = (i << 1) + 2;
    int smallest = i;
    // Compare with left child.
    if (l < heap->size && heap->array[l].key < heap->array[smallest].key)
        smallest = l;
    // Compare with right child.
    if (r < heap->size && heap->array[r].key < heap->array[smallest].key)
        smallest = r;
    
    // If the smallest key is not at index i, swap and continue heapifying
    if (smallest != i) {
        Node temp = heap->array[i];
        heap->array[i] = heap->array[smallest];
        heap->array[smallest] = temp;
        min_heapify(heap, smallest);
    }
}

void build_min_heap(MinHeap *heap) {
    // Start from the last non-leaf node down to the root
    for (int i = (heap->size >> 1) - 1; i >= 0; i--) {
        min_heapify(heap, i);
    }
}

// Remove and return the root node
Node pop_min(MinHeap *heap) {
    if (heap->size < 1) {
        fprintf(stderr, "Heap has no elements to pop.\n");
        exit(EXIT_FAILURE);
    }
    // Save the root node
    Node min = heap->array[0];
    // Replace the root with the last element
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    // Restore the min-heap from the root
    min_heapify(heap, 0);
    return min;
}

// Prints the keys and the int stored in each Node
void print_heap(MinHeap *heap) {
    printf("Heap (size = %d):\n", heap->size);
    for (int i = 0; i < heap->size; i++) {
        printf("Index %d: key = %d, data = %d\n", i, heap->array[i].key,
               *((int *)heap->array[i].data));
    }
    printf("\n");
}

int main(void) {
    srand(time(NULL));  // Seed the random number generator.

    // Build a heap with 10 elements
    int n = 10;
    MinHeap heap;
    heap.capacity = n;
    heap.size = n;
    heap.array = malloc(sizeof(Node) * heap.capacity);
    if (heap.array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    // Fill the heap array with unsorted random values
    // The key and the data (int) are set to the same random value.
    for (int i = 0; i < n; i++) {
        int random_key = rand() % 99 + 1;  // Random number between 1 and 99
        heap.array[i].key = random_key;
        
        // Allocate memory for the integer data.
        int *data_val = malloc(sizeof(int));
        if (data_val == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        // Store random key value as data  for node
        *data_val = random_key; 
        heap.array[i].data = data_val;
    }
    // Print the unsorted initial array
    printf("Initial array (unsorted):\n");
    print_heap(&heap);
    // Build the min-heap from the unsorted array
    build_min_heap(&heap);
    printf("After build_min_heap (min-heap constructed):\n");
    print_heap(&heap);
    // Pop the minimum element (root of the heap)
    Node minNode = pop_min(&heap);
    printf("Popped min node: key = %d, data = %d\n\n",
           minNode.key, *((int *)minNode.data));
    // Free the popped node's data
    free(minNode.data);
    // Print the heap after the pop
    printf("Heap after pop_min:\n");
    print_heap(&heap);
    // Free the allocated data
    for (int i = 0; i < heap.size; i++) {
        free(heap.array[i].data);
    }
    free(heap.array);
    
    return 0;
}
