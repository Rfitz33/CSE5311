#include <stdio.h>
#include <stdlib.h>

// Structure for the dynamic array.
typedef struct {
    int *data;      // Pointer to the underlying C-style array.
    int size;       // Number of elements currently stored.
    int capacity;   // Allocated capacity of the array.
} DynamicArray;

// Function to create a dynamic array with a given initial capacity.
DynamicArray* createDynamicArray(int initialCapacity) {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    arr->data = malloc(initialCapacity * sizeof(int));
    if (arr->data == NULL) {
        free(arr);
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = initialCapacity;
    return arr;
}

// Function to destroy the dynamic array and free allocated memory.
void destroyDynamicArray(DynamicArray *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

// Function to resize the dynamic array when more space is needed.
void resize(DynamicArray *arr, int newCapacity) {
    int *newData = realloc(arr->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        fprintf(stderr, "Memory allocation error during resize\n");
        exit(EXIT_FAILURE);
    }
    arr->data = newData;
    arr->capacity = newCapacity;
}

// Function to add an element at the end of the dynamic array.
void pushBack(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        // Double the capacity when the array is full.
        resize(arr, arr->capacity * 2);
    }
    arr->data[arr->size++] = value;
}

// Function to remove the last element from the dynamic array.
void popBack(DynamicArray *arr) {
    if (arr->size > 0) {
        arr->size--;
    }
}

// Function to get the element at a given index with bounds checking.
int get(DynamicArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return arr->data[index];
}

// Function to set the value at a given index with bounds checking.
void set(DynamicArray *arr, int index, int value) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    arr->data[index] = value;
}

// Example usage of the dynamic array.
int main() {
    // Create a dynamic array with an initial capacity of 4.
    DynamicArray *arr = createDynamicArray(4);
    
    // Add elements to the dynamic array.
    pushBack(arr, 10);
    pushBack(arr, 20);
    pushBack(arr, 30);
    pushBack(arr, 40);
    
    // Print the elements in the array.
    printf("Array elements: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", get(arr, i));
    }
    printf("\nSize: %d, Capacity: %d\n", arr->size, arr->capacity);
    
    // Remove the last element.
    pushBack(arr, 50);
    
    // Print the elements after removal.
    printf("After pushBack, array elements: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", get(arr, i));
    }
    printf("\nSize: %d, Capacity: %d\n", arr->size, arr->capacity);
    
    // Clean up the allocated memory.
    destroyDynamicArray(arr);
    
    return 0;
}
