#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node {
    int data;
    struct stack_node *next;
} stack_node_t;

typedef struct stack {
    stack_node_t *top;
    size_t size;
} stack;

size_t stack_size(stack *stack)
{
    return stack->size;
}

void stack_push(stack *stack, int data)
{
    stack_node_t *new_node = malloc(sizeof(stack_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}
int stack_pop(stack *stack)
{
    if (stack->top == NULL) {
        fprintf(stderr, "Error: Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    stack_node_t *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}
int stack_peek(stack *stack)
{
    if (stack->top == NULL) {
        fprintf(stderr, "Error: Stack is empty.\n");
        return -1;
    }
    return stack->top->data;
}
void stack_free(stack *stack)
{
    if (stack == NULL) {
        return;
    }
    if (stack->top == NULL) {
        free(stack);
        return;
    }
    // Free all nodes in the stack
    stack_node_t *current = stack->top;
    while (current != NULL) {
        stack_node_t *next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}
void stack_clear(stack *stack)
{
    if (stack == NULL) {
        return;
    }
    // Free all nodes in the stack
    if (stack->top != NULL)
    {
        stack_node_t *current = stack->top;
        while (current != NULL) {
            stack_node_t *next = current->next;
            free(current);
            current = next;
        }
        stack->top = NULL;
        stack->size = 0;
    } else {
        fprintf(stderr, "Error: Stack is already empty\n");
    }
    // Free the stack structure itself
    free(stack);
    stack = NULL;
}
int main(void) {
    // Create a new stack.
    stack *s = malloc(sizeof(stack));
    if (s == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    s->size = 0;
    
    // Test: Push some values onto the stack.
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    
    // Test: Peek at the top element (should be 30).
    printf("Top element after pushes: %d\n", stack_peek(s));
    
    // Test: Pop the top element (should pop 30).
    int popped = stack_pop(s);
    printf("Popped element: %d\n", popped);
    
    // Test: Check size (should be 2).
    printf("Stack size after pop: %zu\n", stack_size(s));
    
    // Pop the remaining elements.
    printf("Popped element: %d\n", stack_pop(s)); // 20
    printf("Popped element: %d\n", stack_pop(s)); // 10
    
    // Try to pop from an empty stack (this will trigger an error).
    // Uncomment the next line to see the error handling.
    // printf("Popped element: %d\n", stack_pop(s));
    
    // Free the stack.
    stack_free(s);
    
    return 0;
}
    