#include <stdio.h>
#include <stdlib.h>

// Define BST node structure
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Create a new node with the given data
Node* createNode(int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Insert a new node with the given data into the BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) { // assuming no duplicate values
        root->right = insert(root->right, data);
    }
    return root;
}

// Search for a node with the given data in the BST
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Find the node with the minimum value (used in deletion)
Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete a node with the given data from the BST
Node* delete(Node* root, int data) {
    if (root == NULL)
        return root;
    
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: get the inorder successor
        Node* temp = findMin(root->right);
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Inorder traversal to print the BST (should print the data in sorted order)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Free the entire tree
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main function to test the BST operations
int main() {
    Node* root = NULL;
    int testData[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(testData) / sizeof(testData[0]);

    // Inserting values into the BST
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", testData[i]);
        root = insert(root, testData[i]);
    }
    printf("\n");

    // Inorder traversal (should print the values in sorted order)
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Testing search operation
    int searchFor = 40;
    Node* found = search(root, searchFor);
    if (found != NULL)
        printf("Found %d in the tree.\n", searchFor);
    else
        printf("%d not found in the tree.\n", searchFor);

    // Testing deletion:
    // 1. Deleting a leaf node (20)
    printf("Deleting leaf node: 20\n");
    root = delete(root, 20);
    printf("Inorder traversal after deleting 20: ");
    inorder(root);
    printf("\n");

    // 2. Deleting a node with one child (30)
    printf("Deleting node with one child: 30\n");
    root = delete(root, 30);
    printf("Inorder traversal after deleting 30: ");
    inorder(root);
    printf("\n");

    // 3. Deleting a node with two children (50)
    printf("Deleting node with two children: 50\n");
    root = delete(root, 50);
    printf("Inorder traversal after deleting 50: ");
    inorder(root);
    printf("\n");

    // Free all allocated memory
    freeTree(root);
    return 0;
}
