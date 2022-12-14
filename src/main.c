
#include "main.h"

int main() {

    printf("\n----------\n");

    // Create the root directory
    Directory root = Directory_default;
    root.name = "/root/";

    // snprintf(target_string, size_of_target_string_in_bytes, "%d", source_int)

    // Create a file called "hello.txt" in the root directory
    createFile(&root, "hello.txt", ".txt");
    // Create a file called "test.c" in the root directory
    createFile(&root, "test.c", ".c");

    // Create a directory called "docs" in the root directory
    createDirectory(&root, "docs/");
    // Create a directory called "docs" in the root directory
    createDirectory(&root, "user/");

    // Grab the doc directory
    Directory *docs = getDirectory(&root, "docs/");
    // Create a file called "world.txt" in the "docs" directory
    createFile(docs, "hw3.pdf", ".pdf");
    // Create a file called "world.txt" in the "docs" directory
    createFile(docs, "lab1.py", ".py");

    // Create a folder in the "docs" directory
    createDirectory(docs, "taxes/");
    // Create a file called "world.txt" in the "docs" directory
    createFile(getDirectory(&root, "taxes/"), "cat.jpg", ".jpg");

    // Find a folder nested 2 folders deep: /docs/taxes/
    printDirInfo(getDirectory(&root, "taxes/"));
    // Print info about a file
    printFileInfo(getFile(&root, "cat.jpg"));

    // Search for a file
    File *hello = getFile(&root, "hello.txt");
    // Print the location of the file in the dir
    printf("Search for hello.txt: %s\n", getFileLocation(hello));
    printf("Search for cat.jpg: %s\n", getFileLocation(getFile(&root, "cat.jpg")));

    // Print out a directory tree
    printDirTree(&root);
}
