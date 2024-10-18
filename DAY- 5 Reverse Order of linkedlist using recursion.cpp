#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;            // Node ka data part
    struct Node* next;   // Node ka next pointer
};

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head;

    newNode->data = value;
    newNode->next = NULL;

    // Agar linked list khali hai toh naya node banake usko head banate hain
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Agar linked list mein pehle se nodes hain, to end tak traverse karke insert karte hain
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

// Function to reverse the linked list using recursion
struct Node* reverseListRecursively(struct Node* head) {
    // Base case: Agar list khali ho ya sirf ek node ho toh wahi return karo
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Recursive call: Pichle nodes ko reverse karte raho
    struct Node* rest = reverseListRecursively(head->next);

    // Ab current node ko reverse karte hain
    head->next->next = head;
    head->next = NULL;

    // Return the new head of the reversed list
    return rest;
}

// Function to display the linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty!\n");
        return;
    }

    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Main function for user input and testing
int main() {
    struct Node* head = NULL;
    int choice, value;

    printf("1. Insert a value at end\n");
    printf("2. Reverse the linked list\n");
    printf("3. Display the list\n");
    printf("4. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertEnd(&head, value);  // End pe value insert karte hain
                break;
            case 2:
                head = reverseListRecursively(head);  // Linked list ko reverse karte hain
                printf("List has been reversed.\n");
                break;
            case 3:
                displayList(head);  // Linked list ko display karte hain
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);  // Program ko exit karte hain
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
