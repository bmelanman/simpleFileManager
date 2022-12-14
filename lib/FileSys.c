
#include "FileSys.h"

void createFile(Directory *dir, char *name, char *type) {

    if (dir == NULL) {
        printf("Error: cannot create file \"%s%s\", given dir is NULL\n\n", name, type);
        return;
    }

    // check if the directory is full
    if (dir->num_files >= MAX_NUM_FILES) {
        printf("Directory is full. Cannot create file.\n");
        return;
    }

    // TODO: Check if file already exists

    // Create the new file
    File new_file = File_default;
    new_file.name = name;
    new_file.type = type;
    new_file.parent_directory = dir;

    // Increase the size of the files array by 1
    dir->files = (File *) realloc(dir->files, sizeof(File) * (dir->num_files + 1));
    // Memory allocation error handling
    if (dir->files == NULL) {
        exit(-1);
    }

    // Add the file to the directory
    dir->files[dir->num_files] = new_file;
    dir->num_files++;

    printf("File \"%s%s\" created successfully.\n", name, type);
    printf("File location: %s\n\n", getFileLocation(&new_file));
}

void createDirectory(Directory *dir, char *name) {

    if (dir == NULL) {
        printf("Error: cannot create dir \"%s\", given dir is NULL\n\n", name);
        return;
    }

    // check if the directory is full
    if (dir->num_subdirs >= MAX_NUM_SUBDIRS) {
        printf("Directory is full. Cannot create subdirectory.\n");
        return;
    }

    // TODO: Check if directory already exists

    // Create the new subdirectory
    Directory new_dir = Directory_default;
    new_dir.name = name;
    new_dir.parent_directory = dir;

    // Increase the size of the subdirectories array by 1
    dir->subdirectories = (Directory *) realloc(dir->subdirectories, sizeof(Directory) * (dir->num_subdirs + 1));
    // Memory allocation error handling
    if (dir->subdirectories == NULL) {
        exit(-1);
    }

    // Add the subdirectory to the parent directory
    dir->subdirectories[dir->num_subdirs] = new_dir;
    dir->num_subdirs++;

    printf("Directory %s created successfully.\n", name);
    printf("Directory location: %s\n\n", getDirLocation(&new_dir));
}

File *getFile(Directory *dir, char *name) {

    if (dir == NULL) {
        printf("Cannot find dir \"%s\", given dir is NULL", name);
        return NULL;
    }

    // Make sure the directory exists and has at least one directory or file to check
    if (dir->num_subdirs == 0 && dir->num_files == 0) {
        printf("Directory unavailable\n");
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

        // Look at files within the directory
        for (int i = current_dir->num_files - 1; i >= 0; i--) {
            File *current_file = &current_dir->files[i];
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
        printf("Directory unavailable\n");
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
    char *file_dir = (char *) malloc(strlen(file->name) + strlen(file->type) + 1);
    // Memory allocation error handling
    if (file_dir == NULL) {
        printf("Malloc error occurred in getFileLocation - file_dir");
        free(file_dir);
        exit(-1);
    }

    // Concatenate the name and type together and store in the file dir: "test" + ".txt" = "test.txt"
    snprintf(file_dir, strlen(file->name) + strlen(file->type) + 1, "%s%s", file->name, file->type);

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
