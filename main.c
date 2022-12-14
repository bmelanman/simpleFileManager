
#include "main.h"

int main() {

    printf("\n----------\n");

    // Create the root directory
    Directory root = Directory_default;
    root.name = "/";

    // snprintf(target_string, size_of_target_string_in_bytes, "%d", source_int)

    // Create a file called "hello.txt" in the root directory
    createFile(&root, "hello", ".txt");
    // Create a file called "test.c" in the root directory
    createFile(&root, "test", ".c");

    // Create a directory called "docs" in the root directory
    createDirectory(&root, "docs/");
    // Create a directory called "docs" in the root directory
    createDirectory(&root, "user/");

    // Grab the doc directory
    Directory *docs = getDirectory(&root, "docs/");
    // Create a file called "world.txt" in the "docs" directory
    createFile(docs, "hw3", ".pdf");
    // Create a file called "world.txt" in the "docs" directory
    createFile(docs, "lab1", ".py");

    // Create a folder in the "docs" directory
    createDirectory(docs, "taxes/");
    // Create a file called "world.txt" in the "docs" directory
    createFile(getDirectory(&root, "taxes/"), "cat", ".jpg");

    // Find a folder nested 2 folders deep: /docs/taxes/
    printDirInfo(getDirectory(&root, "taxes/"));

    // Search for a file
    File *hello = getFile(&root, "hello");
    printf("Search for hello.txt: %s", getFileLocation(hello));
    printf("Search for world.txt: %s", getFileLocation(getFile(&root, "world")));
}

//void printDirTree(Directory *dir) {
//
//    char *dir_name = dir->name;
//
//    printf("%s\n", dir_name);
//
//    for (int i = 0; i < dir->num_files; i++) {
//        printf("%s\n", getFileLocation(&dir->files[i]));
//    }
//
//    for (int j = 0; j < dir->num_subdirs; j++) {
//        printf("%s\n", getDirLocation(&dir->subdirectories[j]));
//    }
//}

