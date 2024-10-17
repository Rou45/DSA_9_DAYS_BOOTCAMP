#include <stdio.h>
#include <stdlib.h>

// Node structure for the deque
struct Node {
    int data;             // Queue ke andar store hone wala data
    struct Node* next;    // Next node ke address ko point karega
    struct Node* prev;    // Previous node ke address ko point karega
};

// Double-Ended Queue structure with front and rear
struct Deque {
    struct Node* front;   // Queue ke front ko point karta hai
    struct Node* rear;    // Queue ke rear ko point karta hai
};

// Function to create a new deque
struct Deque* createDeque() {
    struct Deque* dq = (struct Deque*)malloc(sizeof(struct Deque));
    dq->front = dq->rear = NULL;  // Initially front aur rear null honge
    return dq;
}

// Function to insert element at the front
void insertFront(struct Deque* dq, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;

    // Agar deque khali hai
    if (dq->front == NULL) {
        dq->front = dq->rear = newNode;
        newNode->next = newNode->prev = NULL;
    } else {
        newNode->next = dq->front;
        newNode->prev = NULL;
        dq->front->prev = newNode;
        dq->front = newNode;
    }
    printf("%d inserted at front\n", value);
}

// Function to insert element at the rear
void insertRear(struct Deque* dq, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;

    // Agar deque khali hai
    if (dq->rear == NULL) {
        dq->front = dq->rear = newNode;
        newNode->next = newNode->prev = NULL;
    } else {
        newNode->prev = dq->rear;
        newNode->next = NULL;
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
    printf("%d inserted at rear\n", value);
}

// Function to delete element from the front
void deleteFront(struct Deque* dq) {
    // Agar deque khali hai
    if (dq->front == NULL) {
        printf("Deque is empty! Cannot delete from front.\n");
        return;
    }

    struct Node* temp = dq->front;
    printf("%d deleted from front\n", temp->data);

    dq->front = dq->front->next;

    // Agar ek hi element bacha tha
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }

    free(temp);  // Purane front node ko free karte hain
}

// Function to delete element from the rear
void deleteRear(struct Deque* dq) {
    // Agar deque khali hai
    if (dq->rear == NULL) {
        printf("Deque is empty! Cannot delete from rear.\n");
        return;
    }

    struct Node* temp = dq->rear;
    printf("%d deleted from rear\n", temp->data);

    dq->rear = dq->rear->prev;

    // Agar ek hi element bacha tha
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }

    free(temp);  // Purane rear node ko free karte hain
}

// Function to display the deque elements
void displayDeque(struct Deque* dq) {
    if (dq->front == NULL) {
        printf("Deque is empty!\n");
        return;
    }

    struct Node* temp = dq->front;
    printf("Deque elements: ");

    // Front se rear tak print karte hain
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function for user interaction
int main() {
    struct Deque* dq = createDeque();  // Deque create karte hain
    int choice, value;

    printf("1. Insert at front\n");
    printf("2. Insert at rear\n");
    printf("3. Delete from front\n");
    printf("4. Delete from rear\n");
    printf("5. Display deque\n");
    printf("6. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(dq, value);  // Front mein value insert karte hain
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(dq, value);   // Rear mein value insert karte hain
                break;
            case 3:
                deleteFront(dq);  // Front se element delete karte hain
                break;
            case 4:
                deleteRear(dq);   // Rear se element delete karte hain
                break;
            case 5:
                displayDeque(dq);  // Deque ke saare elements ko display karte hain
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);  // Program ko exit karte hain
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
