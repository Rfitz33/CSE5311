#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef struct linked_list {
    node_t *head;
    size_t size;
} linked_list_t;

node_t *node_create(int data)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Add a new node to the beginning of the list
void list_insert(linked_list_t *list, node_t *node)
{
    node->next = list->head;
    list->head = node;
    list->size++;
}

void list_delete(linked_list_t *list, node_t *node)
{
    if (list->head == node) {
        // Node to delete is the head
        list->head = node->next;
    } else {
        // Find the node preceding the one to delete
        node_t *current = list->head;
        while (current != NULL && current->next != node) {
            current = current->next;
        }
        if (current != NULL) {
            current->next = node->next;
        }
    }
    free(node);
    list->size--;  // update the size of the list
}
node_t *list_search(linked_list_t *list, int data)
{
    node_t *temp_node = list->head;
    while (temp_node != NULL && temp_node->data != data) {
        temp_node = temp_node->next;
    }
    return temp_node;
} // Return the first node with the given data

size_t list_size(node_t *head)
{
    size_t count = 0;
    node_t *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
} // Return the number of nodes in the list

linked_list_t *linked_list_create()
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    if (list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}
void linked_list_free(linked_list_t *list)
{
    if (list == NULL) {
        return;
    }
    node_t *current = list->head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current);
        current = next;
    }
    free(list);
} // Free all nodes in the list

int main(void) {
    // Create the linked list
    linked_list_t *list = linked_list_create();

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;

    // Create nodes using the data pointers
    node_t *node1 = node_create(val1);
    node_t *node2 = node_create(val2);
    node_t *node3 = node_create(val3);

    // Insert nodes into the list. Note: insertion is at the head.
    list_insert(list, node1);
    list_insert(list, node2);
    list_insert(list, node3);
    // The list now looks like: node3 (30) -> node2 (20) -> node1 (10)

    // Print list contents after insertion
    printf("List after insertion:\n");
    node_t *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Search for a node with value 20.
    int search_val = 20;
    node_t *found = list_search(list, search_val);
    if (found != NULL) {
        printf("Found node with value: %d\n", found->data);
    } else {
        printf("Node with value %d not found\n", search_val);
    }

    // Delete the found node (with value 20)
    if (found != NULL) {
        list_delete(list, found);
    }

    // Print list contents after deletion
    printf("List after deleting node with value 20:\n");
    current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    // Check the size of the list using the stored size field
    printf("List size (tracked): %zu\n", list->size);

    // Alternatively, verify size by traversing the list
    printf("List size (calculated): %zu\n", list_size(list->head));

    // Free the entire linked list
    linked_list_free(list);

    return 0;
}