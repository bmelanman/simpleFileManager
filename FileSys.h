
#ifndef FILE_MANAGER_FILESYS_H
#define FILE_MANAGER_FILESYS_H

// Imports
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include "zvector.h"

// Defines
#define MAX_NUM_FILES 20
#define MAX_NUM_SUBDIRS 20

// Type definitions
typedef struct File_struct File;

#define DIR_STRUCT
typedef struct Directory_struct Directory;

// Structs
static struct File_struct {
    Directory *parent_directory;
    char *name;
    char *type;
} File_default = {NULL, "", ""};

static struct Directory_struct {
    char *name;
    File *files;
    int num_files;
    Directory *subdirectories;
    int num_subdirs;
    Directory *parent_directory;
} Directory_default = {"", NULL, 0, NULL, 0, NULL};

// Prototypes
void createFile(Directory *dir, char *name, char *type);

void createDirectory(Directory *dir, char *name);

char *getDirLocation(Directory *dir);

char *getFileLocation(File *file);

File *getFile(Directory *dir, char *name);

Directory *getDirectory(Directory *dir, char *name);

void printDirInfo(Directory *dir);

#endif //FILE_MANAGER_FILESYS_H