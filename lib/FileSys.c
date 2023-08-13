
#include "FileSys.h"

Directory *createRootDirectory(){

    Directory *new_directory = scalloc(1, sizeof(Directory));

    new_directory->name = "/root/";

    new_directory->num_subdirs = 0;
    new_directory->subdirectories = NULL;
    new_directory->parent_directory = NULL;

    new_directory->num_files = 0;
    new_directory->files = NULL;

    return new_directory;
}

void createFile(Directory *dir, char *name, char *type) {

    // Make sure that all of our variables exist, and that the directory isn't full,
    // and that the file doesn't already exist in the given directory.
    if (dir == NULL || name == NULL || type == NULL) {
        printf("Error: cannot create file \"%s%s\", one or more inputs are NULL\n\n", name, type);
        return;
    } else if (dir->num_files >= MAX_NUM_FILES) {
        printf("Directory is full. Cannot create file.\n");
        return;
    } else if (getFile(dir, name) != NULL){
        printf("A file by that name already exists in the given directory");
        return;
    }

    // Create the new file
    File new_file = {dir, name, type};

    // Increase the size of the files array by 1
    dir->files = (File *) srealloc(dir->files, sizeof(File) * (dir->num_files + 1));

    // Add the file to the directory
    dir->files[dir->num_files] = new_file;
    dir->num_files++;

    printf("File \"%s\" created successfully.\n", name);
    printf("File location: %s\n\n", getFileLocation(&new_file));
}

void createDirectory(Directory *dir, char *name) {

    if (dir == NULL || name == NULL) {
        printf("Error: cannot create dir \"%s\", given dir is NULL\n\n", name);
        return;
    } else if (dir->num_subdirs >= MAX_NUM_SUBDIRS) {
        printf("Directory is full. Cannot create subdirectory.\n");
        return;
    } else if (getDirectory(dir, name) != NULL) {
        printf("A directory by that name already exists in the given directory");
        return;
    }

    // Create the new subdirectory
    Directory new_dir = {NULL, dir, NULL, name, 0, 0};

    // Increase the size of the subdirectories array by 1
    dir->subdirectories = (Directory *) srealloc(dir->subdirectories, sizeof(Directory) * (dir->num_subdirs + 1));

    // Add the subdirectory to the parent directory
    dir->subdirectories[dir->num_subdirs] = new_dir;
    dir->num_subdirs++;

    printf("Directory %s created successfully.\n", name);
    printf("Directory location: %s\n\n", getDirLocation(&new_dir));
}

// TODO: Create search function using hashmap for internal searches only (private function)
File *getFile(Directory *dir, char *name) {

    if (dir == NULL) {
        printf("Cannot find dir \"%s\", given dir is NULL", name);
        return NULL;
    }

    // Make sure the directory exists and has at least one directory or file to check
    if (dir->num_subdirs == 0 && dir->num_files == 0) {
        return NULL;
    }

    // Create a stack and put the top dir in it
    vector dir_stack = vect_create(1, sizeof(Directory), ZV_BYREF);
    vect_push(dir_stack, dir);

    Directory *current_dir;
    File *current_file;

    // Loop through each directory until the entire tree is traversed
    while (!vect_is_empty(dir_stack)) {

        // Get the next dir off the top of the stack
        current_dir = vect_pop(dir_stack);

        // Look at files within the directory
        for (int i = current_dir->num_files - 1; i >= 0; i--) {
            current_file = &current_dir->files[i];
            // Check if the current file is the one we're looking for
            if (strcmp(current_file->name, name) == 0) {
                return current_file;
            }
        }

        // Otherwise, put each subdir on the stack
        for (int i = current_dir->num_subdirs - 1; i >= 0; i--) {
            vect_push(dir_stack, &current_dir->subdirectories[i]);
        }
    }

    return NULL;
}

Directory *getDirectory(Directory *dir, char *name) {

    if (dir == NULL) {
        printf("Cannot find dir \"%s\", given dir is NULL", name);
        return NULL;
    }

    // Make sure the directory exists and has at least one directory
    if (dir->num_subdirs == 0) {
        return NULL;
    }

    // Create a stack and put the top dir in it
    vector dir_stack = vect_create(1, sizeof(Directory), ZV_BYREF);
    vect_push(dir_stack, dir);

    Directory *current_dir;

    // Loop through each directory until the entire tree is traversed
    while (!vect_is_empty(dir_stack)) {

        // Get the next dir off the top of the stack
        current_dir = vect_pop(dir_stack);

        // Check if it's the one we're looking for
        if (strcmp(current_dir->name, name) == 0) {
            return current_dir;
        }

        // Otherwise, put each subdir on the stack
        for (int i = current_dir->num_subdirs - 1; i >= 0; i--) {
            vect_push(dir_stack, &current_dir->subdirectories[i]);
        }
    }

    return NULL;
}

char *getFileLocation(File *file) {

    if (file == NULL) {
        printf("Cannot get file location, given file is NULL!\n");
        return NULL;
    }

    // TODO: Memory Leak
    // Create and allocate a variable for the file directory
    char *file_dir = (char *) scalloc(1, strlen(file->name) + 1);
    // Memory allocation error handling
    if (file_dir == NULL) {
        printf("Malloc error occurred in getFileLocation - file_dir");
        free(file_dir);
        exit(-1);
    }

    // Copy the file name to the file_dir
    strcpy(file_dir, file->name);

    // Create a temp variable for the file_dir
    char *temp;

    // Get the parent dir of the file
    Directory *parent_dir = file->parent_directory;

    while (parent_dir != NULL) {

        // TODO: Memory Leak
        temp = malloc(strlen(file_dir) + 1);
        // Memory allocation error handling
        if (temp == NULL) {
            printf("Malloc error occurred in getFileLocation loop");
            free(file_dir);
            exit(-1);
        }

        // Move the file dir to a temp variable
        strcpy(temp, file_dir);

        // Add the parent dir and temp together and store in file_dir: "/" + "test.txt" = "/test.txt"
        snprintf(file_dir, strlen(parent_dir->name) + strlen(temp) + 1, "%s%s", parent_dir->name, temp);

        // Continue to the next parent
        parent_dir = parent_dir->parent_directory;
    }

    return file_dir;
}

char *getDirLocation(Directory *dir) {

    if (dir == NULL) {
        printf("Cannot get dir location, given dir is NULL!\n");
        return NULL;
    }

    // TODO: Memory Leak
    char *abs_dir = (char *) malloc(strlen(dir->name) + 1);
    // Memory allocation error handling
    if (abs_dir == NULL) {
        printf("Malloc error occurred in getDirLocation");
        free(abs_dir);
        exit(-1);
    }
    sprintf(abs_dir, "%s", dir->name);

    // TODO: Memory Leak
    char *temp = malloc(strlen(abs_dir) + 1);
    // Memory allocation error handling
    if (temp == NULL) {
        printf("Malloc error occurred in getFileLocation - temp");
        free(abs_dir);
        exit(-1);
    }
    Directory *parent_dir = dir->parent_directory;

    while (parent_dir != NULL) {

        strcpy(temp, abs_dir);
        snprintf(abs_dir, strlen(parent_dir->name) + strlen(temp) + 1, "%s%s", parent_dir->name, temp);

        parent_dir = parent_dir->parent_directory;
    }

    return abs_dir;
}

void printDirInfo(Directory *dir) {

    if (dir == NULL) {
        printf("Cannot find dir info, given dir is NULL!");
        return;
    }

    printf("Directory Info: \n");
    printf("Directory: %s\n", dir->name);
    printf("Location: %s\n", getDirLocation(dir));
    if (dir->num_files > 0) {
        printf("Files: \n");
        for (int i = 0; i < dir->num_files; i++) {
            printf("- %s\n", dir->files[i].name);
        }
    } else {
        printf("No files in dir\n");
    }
    if (dir->num_subdirs > 0) {
        printf("Subdirectories: \n");
        for (int j = 0; j < dir->num_subdirs; j++) {
            printf("- %s\n", dir->subdirectories[j].name);
        }
    } else {
        printf("No subdirectories in dir\n");
    }
    if (dir->parent_directory != NULL) {
        printf("Parent dir: %s\n", dir->parent_directory->name);
    } else {
        printf("No parent directory\n");
    }
    printf("\n");
}

void printFileInfo(File *file) {

    if (file == NULL) {
        printf("Cannot find dir info, given dir is NULL!");
        return;
    }

    printf("File Info: \n");
    printf("File name: %s\n", file->name);
    printf("File type: %s\n", file->type);
    printf("File location: %s\n", getFileLocation(file));
    printf("\n");
}

void printDirTree(Directory *dir) {

    // Create a stack and put the top dir in it
    vector dir_stack = vect_create(1, sizeof(Directory), ZV_BYREF);
    vect_push(dir_stack, dir);

    Directory *current_dir;
    printf("\nDirectory Tree: \n");

    // Loop through each directory until the entire tree is traversed
    while (!vect_is_empty(dir_stack)) {

        // Get the next dir off the top of the stack
        current_dir = vect_pop(dir_stack);
        printf("%s\n", getDirLocation(current_dir));

        // Look at files within the directory
        for (int i = current_dir->num_files - 1; i >= 0; i--) {
            printf("- %s\n", current_dir->files[i].name);
        }

        // Otherwise, put each subdir on the stack
        for (int i = current_dir->num_subdirs - 1; i >= 0; i--) {
            vect_push(dir_stack, &current_dir->subdirectories[i]);
        }
    }
}
