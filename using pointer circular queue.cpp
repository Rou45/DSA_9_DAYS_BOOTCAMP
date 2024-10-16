#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

struct CircularQueue {
    int items[SIZE];
    int front, rear;
};

// Queue ko initialize karte hain (pointer ke through)
void initQueue(struct CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check karte hain agar queue full hai toh
int isFull(struct CircularQueue *q) {
    return (q->front == (q->rear + 1) % SIZE);
}

// Check karte hain agar queue khaali hai toh
int isEmpty(struct CircularQueue *q) {
    return (q->front == -1);
}

// Insert karte hain value ko circular queue mein (pointer use karke)
void enqueue(struct CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear = (q->rear + 1) % SIZE;
        q->items[q->rear] = value;
        printf("Inserted %d\n", value);
    }
}

// Delete karte hain value ko circular queue se
void dequeue(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
    } else {
        printf("Deleted %d\n", q->items[q->front]);
        if (q->front == q->rear) {
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front + 1) % SIZE;
        }
    }
}

// Queue ke elements ko display karte hain
void display(struct CircularQueue *q) {
    int i;
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue elements are: ");
        for (i = q->front; i != q->rear; i = (i + 1) % SIZE)
            printf("%d ", q->items[i]);
        printf("%d\n", q->items[i]);
    }
}

// Main function to handle user inputs
int main() {
    struct CircularQueue q;
    initQueue(&q);
    int choice, value;

    while (1) {
        printf("\nCircular Queue Menu:\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }

    return 0;
}