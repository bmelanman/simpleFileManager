
#ifndef FILE_MANAGER_FILESYS_H
#define FILE_MANAGER_FILESYS_H

// Imports
#include <stdio.h>
#include <string.h>
#include "Stack.h"
#include "zvector/src/zvector.h"

// Defines
#define MAX_NUM_FILES 20
#define MAX_NUM_SUBDIRS 20

// Type definitions
typedef struct File_struct File;
typedef struct Directory_struct Directory;

// Structs
struct File_struct {
    Directory *parent_directory;
    char *name;
    char *type;
};

struct Directory_struct {
    Directory *subdirectories;
    Directory *parent_directory;
    File *files;
    char *name;
    int num_files;
    int num_subdirs;
};

// Prototypes
Directory *createRootDirectory();

void createFile(Directory *dir, char *name, char *type);

void createDirectory(Directory *dir, char *name);

char *getDirLocation(Directory *dir);

char *getFileLocation(File *file);

File *getFile(Directory *dir, char *name);

Directory *getDirectory(Directory *dir, char *name);

void printFileInfo(File *file);

void printDirInfo(Directory *dir);

void printDirTree(Directory *dir);

#endif //FILE_MANAGER_FILESYS_H