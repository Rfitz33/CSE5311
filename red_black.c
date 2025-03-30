#include <stdio.h>
#include <stdlib.h>

// Define colors for red-black nodes.
typedef enum { RED, BLACK } Color;

// Node structure for the red-black tree.
typedef struct RBNode {
    int data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

// Global sentinel node used for all NIL leaves.
RBNode *NIL;

// Function to create a new red-black tree node.
RBNode* createNode(int data) {
    RBNode* node = (RBNode*) malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;  // New nodes are inserted red.
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    return node;
}

// Left rotate around node x.
void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;
    
    y->parent = x->parent;
    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

// Right rotate around node y.
void rightRotate(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != NIL)
        x->right->parent = y;
    
    x->parent = y->parent;
    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

// Fix-up the tree after insertion to maintain red-black properties.
void RBInsertFixup(RBNode **root, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right; // uncle
            if (y->color == RED) {
                // Case 1: Uncle is red.
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z is a right child.
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3: z is a left child.
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            // Mirror image of above code (left/right exchanged).
            RBNode *y = z->parent->parent->left; // uncle
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert a new node with the given data.
void RBInsert(RBNode **root, int data) {
    RBNode *z = createNode(data);
    RBNode *y = NIL;
    RBNode *x = *root;

    while (x != NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NIL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    
    // New node's children are already set to NIL in createNode.
    RBInsertFixup(root, z);
}

// Inorder traversal prints the tree in sorted order.
void inorder(RBNode *root) {
    if (root != NIL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Search for a node with the given data.
RBNode* RBSearch(RBNode *root, int data) {
    while (root != NIL && data != root->data) {
        if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

// Helper function: Transplant subtree v in place of subtree u.
void RBTransplant(RBNode **root, RBNode *u, RBNode *v) {
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// Helper function: Find the node with minimum key in subtree.
RBNode* treeMinimum(RBNode *node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

// Fix-up the tree after deletion to maintain red-black properties.
void RBDeleteFixup(RBNode **root, RBNode *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            // Mirror image of above code.
            RBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Delete a node with the given data from the red-black tree.
void RBDelete(RBNode **root, int data) {
    RBNode *z = RBSearch(*root, data);
    if (z == NIL) {
        printf("Value %d not found in the tree.\n", data);
        return;
    }
    RBNode *y = z;
    Color y_original_color = y->color;
    RBNode *x;
    
    if (z->left == NIL) {
        x = z->right;
        RBTransplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        RBTransplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            RBTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK)
        RBDeleteFixup(root, x);
}

// Recursively free all nodes in the tree.
void freeTree(RBNode *node) {
    if (node != NIL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    // Initialize the NIL sentinel.
    NIL = (RBNode*) malloc(sizeof(RBNode));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;

    RBNode *root = NIL;

    // ===== Test Insertion =====
    int testData[] = {20, 15, 25, 10, 5, 1, 30, 28, 40};
    int n = sizeof(testData) / sizeof(testData[0]);
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", testData[i]);
        RBInsert(&root, testData[i]);
    }
    printf("\n");

    // Inorder traversal should print sorted values.
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // ===== Test Search =====
    int searchFor = 25;
    RBNode* found = RBSearch(root, searchFor);
    if (found != NIL)
        printf("Found %d in the tree.\n", searchFor);
    else
        printf("%d not found in the tree.\n", searchFor);

    // ===== Test Deletion =====
    // Delete a leaf node.
    printf("Deleting value 1 (leaf node)...\n");
    RBDelete(&root, 1);
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    // Delete a node with one child.
    printf("Deleting value 15 (node with one child)...\n");
    RBDelete(&root, 15);
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    // Delete a node with two children.
    printf("Deleting value 20 (node with two children)...\n");
    RBDelete(&root, 20);
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    // Clean up memory.
    freeTree(root);
    free(NIL); // Free the sentinel node.
    
    return 0;
}
