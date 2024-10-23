#include <stdio.h>
#include <stdlib.h>

// AVL Tree ka node structure define kar rahe hain
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get height of a node (Ek node ka height nikalne ke liye function)
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Create new node (Naya node banane ke liye)
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;  // Initially height 1 hoti hai
    return newNode;
}

// Get max of two numbers (Do numberon mein se maximum ka pata lagao)
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right rotate (Right rotation karna)
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Rotation perform kar rahe hain
    x->right = y;
    y->left = T2;

    // Heights ko update kar rahe hain
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;  // Naya root node return karenge
}

// Left rotate (Left rotation karna)
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Rotation perform kar rahe hain
    y->left = x;
    x->right = T2;

    // Heights ko update kar rahe hain
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;  // Naya root node return karenge
}

// Balance factor nikalne ka function
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insert node in AVL tree (Node insert karna AVL tree mein)
struct Node* insertNode(struct Node* node, int data) {
    // Normal BST insertion pehle perform karenge
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;  // Duplicate values allowed nahi hain

    // Height update karenge
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance factor check karenge
    int balance = getBalance(node);

    // LL (Left Left case) ke liye
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // RR (Right Right case) ke liye
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // LR (Left Right case) ke liye
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL (Right Left case) ke liye
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // Agar balancing theek hai to node return karenge
}

// Minimum value node find karna (delete ke liye help karta hai)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete node from AVL tree (AVL tree se node delete karna)
struct Node* deleteNode(struct Node* root, int data) {
    // Pehle BST style deletion karenge
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            // Node with two children: get the inorder successor
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Height update karna
    root->height = 1 + max(height(root->left), height(root->right));

    // Balance factor check karenge
    int balance = getBalance(root);

    // LL case ke liye
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR case ke liye
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR case ke liye
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL case ke liye
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;  // Return the (potentially) balanced root node
}

// Preorder traversal (Pehele root, phir left, phir right)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Inorder traversal (Left, phir root, phir right)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Postorder traversal (Left, right, phir root)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert Node\n2. Delete Node\n3. Preorder Traversal\n4. Inorder Traversal\n5. Postorder Traversal\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Preorder traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Inorder traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
