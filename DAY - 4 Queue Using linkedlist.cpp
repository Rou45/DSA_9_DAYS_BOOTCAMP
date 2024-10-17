#include <stdio.h>
#include <stdlib.h>

// Node ka structure define karte hain (Queue ke har element ko represent karne ke liye)
struct Node {
    int data;              // Node ke andar ka data (Queue ka element)
    struct Node* next;     // Agle node ka pointer (link to next queue element)
};

// Queue structure define karte hain jo front aur rear pointers ko hold karega
struct Queue {
    struct Node *front, *rear;  // Queue ke front aur rear pointers
};

// Nayi queue ko initialize karne ka function
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));  // Queue ke liye memory allocate karte hain
    q->front = q->rear = NULL;  // Initially, front aur rear NULL hain
    return q;
}

// Enqueue operation ka function (Queue ke rear pe naya element add karna)
void enqueue(struct Queue* q, int value) {
    // Naya node create karte hain
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Agar memory allocate nahi ho rahi, error message dekar program exit karte hain
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;  // Naye node mein value dalte hain
    newNode->next = NULL;   // Naya node aakhri node hoga to uska next NULL set karte hain

    // Agar queue khali hai, to front aur rear dono naya node pe point karenge
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        printf("Enqueued %d\n", value);
        return;
    }

    // Agar queue khali nahi hai to rear ke baad naya node lagate hain aur rear ko update karte hain
    q->rear->next = newNode;
    q->rear = newNode;
    printf("Enqueued %d\n", value);
}

// Dequeue operation ka function (Queue ke front se element remove karna)
int dequeue(struct Queue* q) {
    // Agar queue khali hai to underflow ka message print karte hain
    if (q->front == NULL) {
        printf("Queue Underflow! Cannot dequeue\n");
        return -1;
    }

    // Front node ko remove karne ka process
    struct Node* temp = q->front;  // Temporary pointer front node ko hold karne ke liye
    int dequeuedValue = temp->data;  // Front node ka data (jo dequeue karenge)
    q->front = q->front->next;  // Front ko agle node pe move karte hain

    // Agar front NULL ho jaye, to rear bhi NULL ho jata hai (queue khali ho jata hai)
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);  // Front node ko free karte hain
    printf("Dequeued %d\n", dequeuedValue);
    return dequeuedValue;  // Dequeued value ko return karte hain
}

// Queue ko display karne ka function
void display(struct Queue* q) {
    struct Node* temp = q->front;  // Queue ko front se start karke elements ko print karte hain

    // Agar queue khali hai to message print karte hain
    if (temp == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    // Front se shuru karke sab elements ko print karte hain
    while (temp != NULL) {
        printf("%d -> ", temp->data);  // Har node ka data print karte hain
        temp = temp->next;  // Agle node pe move karte hain
    }
    printf("NULL\n");  // Queue ka end (NULL) print karte hain
}

// Main function
int main() {
    struct Queue* q = createQueue();  // Queue create karte hain
    int choice, value;

    // User ko option dena queue operations ke liye
    printf("1. Enqueue element\n");
    printf("2. Dequeue element\n");
    printf("3. Display queue\n");
    printf("4. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(q, value);  // Queue mein element add karte hain (enqueue)
                break;
            case 2:
                dequeue(q);  // Queue se element remove karte hain (dequeue)
                break;
            case 3:
                display(q);  // Queue ko display karte hain
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);  // Program ko exit karte hain
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
