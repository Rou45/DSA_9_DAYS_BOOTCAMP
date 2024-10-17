#include <stdio.h>
#include <stdlib.h>

// Node ka structure define karna (Stack ke har element ko represent karne ke liye)
struct Node {
    int data;              // Node ke andar ka data (Stack ka element)
    struct Node* next;     // Agle node ka pointer (link to next stack element)
};

// Push operation ka function (Stack ke top pe naya element add karna)
void push(struct Node** top, int value) {
    // Naya node create karte hain
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Agar memory allocate nahi ho rahi, error message dekar program exit karte hain
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;     // Naye node mein value dalte hain
    newNode->next = *top;      // Naya node ab current top ke aage lagta hai
    *top = newNode;            // Naya node ab stack ka top ban jaata hai
    printf("Pushed %d onto the stack\n", value);
}

// Pop operation ka function (Top se element hataana)
int pop(struct Node** top) {
    // Agar stack empty hai to underflow ka message dete hain
    if (*top == NULL) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    }

    // Top node ko remove karne ka process
    struct Node* temp = *top;  // Temporary pointer top node ko hold karne ke liye
    int poppedValue = temp->data;  // Popped value ko store karna
    *top = (*top)->next;  // Top ko agle node pe move karna (stack ka next top)
    free(temp);  // Memory free karte hain (jo humne top ke liye allocate ki thi)
    
    printf("Popped %d from the stack\n", poppedValue);
    return poppedValue;  // Popped value ko return karte hain
}

// Stack ko display karne ka function
void display(struct Node* top) {
    // Agar stack khali hai to message print karte hain
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }

    printf("Stack elements: ");
    // Top se shuru karke sab elements ko print karte hain
    while (top != NULL) {
        printf("%d -> ", top->data);  // Har node ka data print karte hain
        top = top->next;  // Agle node pe move karte hain
    }
    printf("NULL\n");  // Stack ka end (NULL) print karte hain
}

// Main function
int main() {
    struct Node* top = NULL;  // Initially stack khali hai, top ko NULL set karte hain
    int choice, value;

    // User ko option dena stack operations ke liye
    printf("1. Push element\n");
    printf("2. Pop element\n");
    printf("3. Display stack\n");
    printf("4. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&top, value);  // Stack pe element add karte hain (push)
                break;
            case 2:
                pop(&top);  // Stack se element remove karte hain (pop)
                break;
            case 3:
                display(top);  // Stack ko display karte hain
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
