#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the queue
struct Node {
    int data;            // Stores the data in the queue
    struct Node* next;   // Points to the next node in the queue
};

// Define the structure for a circular queue with front and rear
struct CircularQueue {
    struct Node *front, *rear;  // Pointers to the front and rear of the queue
};

// Function to create a circular queue
struct CircularQueue* createQueue() {
    struct CircularQueue* q = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    q->front = q->rear = NULL;  // Initially, front and rear are NULL
    return q;
}

// Function to insert an element at the rear of the queue (enqueue)
void enqueue(struct CircularQueue* q, int value) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;  // Insert the value into the new node

    // If the queue is empty, front and rear both point to the new node
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        q->rear->next = q->front;  // Maintain the circular nature
    } else {
        // Insert the new node after the rear and update rear
        q->rear->next = newNode;
        q->rear = newNode;
        q->rear->next = q->front;  // Maintain the circular link
    }

    printf("%d inserted into the queue\n", value);
}

// Function to remove an element from the front of the queue (dequeue)
int dequeue(struct CircularQueue* q) {
    // If the queue is empty, nothing to dequeue
    if (q->front == NULL) {
        printf("Queue is empty! Cannot dequeue\n");
        return -1;
    }

    // Dequeue the front element
    int value;
    if (q->front == q->rear) {
        // If there is only one element
        value = q->front->data;
        free(q->front);  // Free the memory of the single element
        q->front = q->rear = NULL;  // Set the queue to empty
    } else {
        struct Node* temp = q->front;  // Hold the current front node
        value = temp->data;  // Get the data from the front
        q->front = q->front->next;  // Move the front pointer to the next node
        q->rear->next = q->front;   // Maintain the circular link
        free(temp);  // Free the memory of the old front node
    }

    printf("%d removed from the queue\n", value);
    return value;
}

// Function to display all the elements in the queue
void display(struct CircularQueue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node* temp = q->front;  // Start from the front of the queue
    printf("Queue elements: ");

    do {
        printf("%d -> ", temp->data);  // Print each node's data
        temp = temp->next;  // Move to the next node
    } while (temp != q->front);  // Stop when we reach back to the front
    
    printf("front (Circular Queue)\n");
}

// Main function
int main() {
    struct CircularQueue* q = createQueue();  // Create a new circular queue
    int choice, value;

    printf("1. Insert element into the queue (Enqueue)\n");
    printf("2. Remove element from the queue (Dequeue)\n");
    printf("3. Display the queue\n");
    printf("4. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert into the queue: ");
                scanf("%d", &value);
                enqueue(q, value);  // Insert a new value into the circular queue
                break;
            case 2:
                dequeue(q);  // Remove an element from the circular queue
                break;
            case 3:
                display(q);  // Display the elements of the circular queue
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);  // Exit the program
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
