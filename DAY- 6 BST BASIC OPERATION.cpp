#include <stdio.h>
#include <stdlib.h>

// Binary Search Tree ke liye ek node structure banaya
struct Node {
    int data; // Node ka data
    struct Node* left;  // Left subtree pointer
    struct Node* right; // Right subtree pointer
};

// Ek naya node banane ka function
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // Naya node ke liye memory allocate karta hai
    newNode->data = value;  // Node ka data set karta hai
    newNode->left = NULL;   // Left child NULL hota hai initially
    newNode->right = NULL;  // Right child bhi NULL hota hai initially
    return newNode;
}

// BST mein ek naya node insert karne ka function
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {  // Agar tree khaali hai, toh naya node return karo
        return createNode(value);
    }

    if (value < root->data) {  // Agar value root se chhoti hai, toh left subtree mein insert karo
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {  // Agar value root se badi hai, toh right subtree mein insert karo
        root->right = insertNode(root->right, value);
    }

    return root;  // Root ko return karo jo update ho chuka hai
}

// Inorder traversal (Left -> Root -> Right)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);    // Left subtree ko traverse karo
        printf("%d ", root->data);       // Root ka data print karo
        inorderTraversal(root->right);   // Right subtree ko traverse karo
    }
}

// Preorder traversal (Root -> Left -> Right)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);       // Root ka data print karo
        preorderTraversal(root->left);   // Left subtree ko traverse karo
        preorderTraversal(root->right);  // Right subtree ko traverse karo
    }
}

// Postorder traversal (Left -> Right -> Root)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);   // Left subtree ko traverse karo
        postorderTraversal(root->right);  // Right subtree ko traverse karo
        printf("%d ", root->data);        // Root ka data print karo
    }
}

// BST mein ek node ko search karne ka function
struct Node* searchNode(struct Node* root, int key) {
    if (root == NULL || root->data == key) {  // Agar root NULL ya key mil gayi ho
        return root;
    }

    if (key < root->data) {  // Agar key chhoti hai, toh left mein search karo
        return searchNode(root->left, key);
    } else {  // Agar key badi hai, toh right mein search karo
        return searchNode(root->right, key);
    }
}

// Node with minimum value ko find karne ka function (delete ke liye use hota hai)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Leftmost leaf tak jao jo minimum value hoti hai
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// BST se ek node ko delete karne ka function
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;  // Agar tree khaali hai toh kuch mat karo
    }

    if (key < root->data) {  // Agar key chhoti hai, toh left subtree mein jao
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {  // Agar key badi hai, toh right subtree mein jao
        root->right = deleteNode(root->right, key);
    } else {  // Agar key mil gayi
        // Case 1: Node ke paas koi child nahi (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: Node ke paas ek child hai
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Node ke paas do child hain
        struct Node* temp = minValueNode(root->right);  // Inorder successor ko find karo
        root->data = temp->data;  // Inorder successor ka value copy karo
        root->right = deleteNode(root->right, temp->data);  // Successor ko delete karo
    }
    return root;
}

// Main function
int main() {
    struct Node* root = NULL;  // Root ko initialize kiya
    struct Node* searchResult = NULL;  // Yeh variable yahan define kiya, taaki switch ke har case mein access ho sake

    int choice, value;
    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Insert operation
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("%d inserted into the tree.\n", value);
                break;

            case 2:  // Delete operation
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("%d deleted from the tree.\n", value);
                break;

            case 3:  // Search operation
                printf("Enter value to search: ");
                scanf("%d", &value);
                searchResult = searchNode(root, value);  // Ab searchResult ko case ke andar use kar rahe hain
                if (searchResult != NULL) {
                    printf("%d found in the tree.\n", value);
                } else {
                    printf("%d not found in the tree.\n", value);
                }
                break;

            case 4:  // Inorder Traversal (sorted order)
                printf("Inorder traversal of the tree: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 5:  // Preorder Traversal
                printf("Preorder traversal of the tree: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 6:  // Postorder Traversal
                printf("Postorder traversal of the tree: ");
                postorderTraversal(root);
                printf("\n");
                break;

            case 7:  // Exit the program
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
