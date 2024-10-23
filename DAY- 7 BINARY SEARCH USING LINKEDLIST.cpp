#include <stdio.h>
#include <stdlib.h>

// BST node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Function to search for a node in BST
struct Node* searchNode(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    if (key < root->data)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// Inorder traversal to display BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert Node\n2. Search Node\n3. Display (Inorder Traversal)\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("%d inserted into the tree.\n", value);
                break;
            }

            case 2: {
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node* searchResult = searchNode(root, value);  // Declare searchResult within braces
                if (searchResult != NULL)
                    printf("%d found in the tree.\n", value);
                else
                    printf("%d not found in the tree.\n", value);
                break;
            }

            case 3: {
                printf("Inorder traversal of the tree: ");
                inorderTraversal(root);
                printf("\n");
                break;
            }

            case 4:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
