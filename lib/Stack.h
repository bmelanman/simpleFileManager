
#ifndef FILE_MANAGER_STACK_H
#define FILE_MANAGER_STACK_H

#include <stdlib.h>
#include <stdbool.h>

#ifndef DIR_STRUCT
#define DIR_STRUCT
typedef struct Directory_struct Directory;
#endif

typedef struct Stack_struct Stack;

struct Stack_struct {
    Directory *dir;
    struct Stack_struct *next;
};

void push(Directory *dir);
Directory *pop();
bool isEmpty();
void reset_stack();

#endif //FILE_MANAGER_STACK_H
