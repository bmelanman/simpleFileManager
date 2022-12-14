
#include "Stack.h"

// Global Variables
Stack *dir_stack = NULL;

void push(Directory *new_dir) {
    // Make a new node
    Stack *node_ptr = malloc(sizeof(Stack));
    // Add dir and next
    node_ptr->dir = new_dir;
    node_ptr->next = dir_stack;
    // Set the top of the dir_stack to the new node
    dir_stack = node_ptr;
}

Directory *pop() {
    // Make sure the Stack_struct contains data
    if (dir_stack == NULL) {
        return NULL;
    }

    // Store the top of the Stack_struct temporarily
    Directory *temp = dir_stack->dir;
    // Remove the top from the Stack_struct
    dir_stack = dir_stack->next;

    // Return the popped value
    return temp;
}

bool isEmpty(){
    return dir_stack->dir == NULL;
}

void reset_stack(){
    dir_stack = NULL;
}