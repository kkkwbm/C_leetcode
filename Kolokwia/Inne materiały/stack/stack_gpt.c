#include <stdio.h>

#define MAXLENGTH 100

struct stack {
    int top;
    int elements[MAXLENGTH];
};

int top(struct stack S) {
    if (S.top == -1) {
        printf("Stack is empty.\n");
        return -1;
    } else {
        return S.elements[S.top];
    }
}

int pop(struct stack* S) {
    if (S->top == -1) {
        printf("Stack is empty.\n");
        return -1;
    } else {
        int element = S->elements[S->top];
        S->top--;
        return element;
    }
}

int empty(struct stack S) {
    return (S.top == -1);
}

void print(struct stack S) {
    if (S.top == -1) {
        printf("Stack is empty.\n");
    } else {
        printf("Stack elements: ");
        for (int i = 0; i <= S.top; i++) {
            printf("%d ", S.elements[i]);
        }
        printf("\n");
    }
}

void makenull(struct stack* S) {
    S->top = -1;
}

void push(int x, struct stack* S) {
    if (S->top == MAXLENGTH - 1) {
        printf("Stack is full. Cannot push element.\n");
    } else {
        S->top++;
        S->elements[S->top] = x;
    }
}

int main() {
    struct stack myStack;
    makenull(&myStack);

    push(5, &myStack);
    push(10, &myStack);
    push(15, &myStack);

    printf("Top element: %d\n", top(myStack));
    print(myStack);

    pop(&myStack);

    printf("Top element after pop: %d\n", top(myStack));
    print(myStack);

    return 0;
}