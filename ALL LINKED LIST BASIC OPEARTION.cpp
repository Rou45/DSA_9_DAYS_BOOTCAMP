#include <stdio.h>
#include <stdlib.h>

// Node structure define kar rahe hain
struct Node {
    int data;             // Node ka data
    struct Node* next;    // Pointer to the next node
};

// Naya node create karne ka function
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Beginning mein insert karne ka function
void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);   // Naya node create karo
    newNode->next = *head;                      // Naye node ka next ko current head se link karo
    *head = newNode;                            // Head ko naye node pe set karo
}

// End mein insert karne ka function
void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);   // Naya node create karo
    if (*head == NULL) {                        // Agar list khali hai toh
        *head = newNode;                        // Naye node ko head banao
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {                // Last node tak traverse karo
        temp = temp->next;
    }
    temp->next = newNode;                       // Last node ke next mein naye node ko add karo
}

// Middle mein insert karne ka function
void insertAtMiddle(struct Node** head, int value, int position) {
    struct Node* newNode = createNode(value);
    if (position == 1) {
        insertAtBeginning(head, value);         // Agar position 1 hai to beginning mein insert karo
        return;
    }

    struct Node* temp = *head;
    for (int i = 1; i < position - 1; i++) {    // Middle tak pahuchne ke liye position tak traverse karo
        if (temp == NULL) {
            printf("Position out of range\n");
            return;
        }
        temp = temp->next;
    }
    newNode->next = temp->next;                 // Naye node ko middle mein insert karo
    temp->next = newNode;
}

// Beginning se delete karne ka function
void deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {                        // Agar list khali hai
        printf("List empty hai!\n");
        return;
    }
    struct Node* temp = *head;                  // Head ko temporary pointer mein store karo
    *head = (*head)->next;                      // Head ko agle node pe shift karo
    free(temp);                                 // Purane node ko free karo
    printf("Deleted node from beginning\n");
}

// End se delete karne ka function
void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List empty hai!\n");
        return;
    }
    struct Node* temp = *head;
    if (temp->next == NULL) {                   // Agar ek hi node ho
        free(temp);
        *head = NULL;
        printf("Deleted node from end\n");
        return;
    }
    while (temp->next->next != NULL) {          // Second last node tak traverse karo
        temp = temp->next;
    }
    free(temp->next);                           // Last node ko free karo
    temp->next = NULL;                          // Second last node ke next ko NULL set karo
    printf("Deleted node from end\n");
}

// Middle se delete karne ka function
void deleteFromMiddle(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List empty hai!\n");
        return;
    }
    struct Node* temp = *head;
    if (position == 1) {
        deleteFromBeginning(head);              // Agar position 1 hai to beginning se delete karo
        return;
    }
    for (int i = 1; i < position - 1; i++) {    // Middle tak traverse karo
        if (temp == NULL || temp->next == NULL) {
            printf("Position out of range\n");
            return;
        }
        temp = temp->next;
    }
    struct Node* delNode = temp->next;          // Delete hone wale node ko temporary pointer mein store karo
    temp->next = delNode->next;                 // Previous node ke next ko agle node pe shift karo
    free(delNode);                              // Node ko free karo
    printf("Deleted node from middle\n");
}

// List ko display karne ka function
void displayList(struct Node* head) {
    struct Node* temp = head;
    if (temp == NULL) {                         // Agar list khali hai
        printf("List empty hai!\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {                      // Jab tak temp NULL nahi hota list ke nodes ko print karo
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function jahan user input denge
int main() {
    struct Node* head = NULL;
    int choice, value, position;

    while (1) {
        printf("\nLinked List Operations:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at middle\n");
        printf("3. Insert at end\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from middle\n");
        printf("6. Delete from end\n");
        printf("7. Display the list\n");
        printf("8. Exit\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;
            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtMiddle(&head, value, position);
                break;
            case 3:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;
            case 4:
                deleteFromBeginning(&head);
                break;
            case 5:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteFromMiddle(&head, position);
                break;
            case 6:
                deleteFromEnd(&head);
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
