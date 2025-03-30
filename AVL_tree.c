#include <stdio.h>
#include <stdlib.h>

// AVL tree node structure.
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Utility function to get the height of the tree.
int height(Node *n) {
    return n ? n->height : 0;
}

// Utility function to get maximum of two integers.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node with a given key.
Node* createNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // New node is initially at leaf level.
    return node;
}

// Right rotate subtree rooted with y.
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    
    // Perform rotation.
    x->right = y;
    y->left = T2;
    
    // Update heights.
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // Return new root.
    return x;
}

// Left rotate subtree rooted with x.
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    
    // Perform rotation.
    y->left = x;
    x->right = T2;
    
    // Update heights.
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    // Return new root.
    return y;
}

// Get the balance factor of node n.
int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Insert a key into the AVL tree rooted with node and return the new root.
Node* insert(Node *node, int key) {
    // Perform standard BST insertion.
    if (node == NULL)
        return createNode(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Duplicate keys are not allowed.
        return node;
    
    // Update height of this ancestor node.
    node->height = 1 + max(height(node->left), height(node->right));
    
    // Get balance factor to check whether this node became unbalanced.
    int balance = getBalance(node);
    
    // If unbalanced, then there are 4 cases.
    // Left Left Case.
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    // Right Right Case.
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    // Left Right Case.
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case.
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return the (unchanged) node pointer.
    return node;
}

// Helper function to find the node with the smallest key in the subtree.
Node* minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a key from the AVL tree rooted with root and return the new root.
Node* deleteNode(Node *root, int key) {
    // Standard BST deletion.
    if (root == NULL)
        return root;
    
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one child or no child.
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            
            // No child case.
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // One child case: copy the contents of the non-empty child.
                *root = *temp;
            }
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree).
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            // Delete the inorder successor.
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    // If the tree had only one node then return.
    if (root == NULL)
        return root;
    
    // Update height.
    root->height = 1 + max(height(root->left), height(root->right));
    
    // Get balance factor.
    int balance = getBalance(root);
    
    // If unbalanced, then there are 4 cases.
    // Left Left Case.
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Left Right Case.
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case.
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Right Left Case.
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// Search for a key in the AVL tree.
Node* search(Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Inorder traversal to print the tree in sorted order.
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Free all nodes of the AVL tree.
void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node *root = NULL;
    
    // ===== Test Insertion =====
    int testData[] = {20, 4, 15, 70, 50, 100, 10, 5, 30};
    int n = sizeof(testData) / sizeof(testData[0]);
    
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", testData[i]);
        root = insert(root, testData[i]);
    }
    printf("\n");
    
    // Print inorder traversal (should be sorted).
    printf("Inorder traversal after insertions: ");
    inorder(root);
    printf("\n");
    
    // ===== Test Search =====
    int keyToSearch = 15;
    Node *found = search(root, keyToSearch);
    if (found)
        printf("Found key %d in the tree.\n", keyToSearch);
    else
        printf("Key %d not found in the tree.\n", keyToSearch);
    
    // ===== Test Deletion =====
    printf("Deleting key 4...\n");
    root = deleteNode(root, 4);
    printf("Inorder traversal after deleting 4: ");
    inorder(root);
    printf("\n");
    
    printf("Deleting key 70...\n");
    root = deleteNode(root, 70);
    printf("Inorder traversal after deleting 70: ");
    inorder(root);
    printf("\n");
    
    printf("Deleting key 20...\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal after deleting 20: ");
    inorder(root);
    printf("\n");
    
    // Free all nodes.
    freeTree(root);
    
    return 0;
}
