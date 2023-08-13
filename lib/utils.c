
#include "utils.h"

void *scalloc(size_t count, size_t size) {

    void *p = calloc(count, size);

    if (p == NULL) {
        // TODO: safe fprintf -> int fnprintf(__sFILE *, size_t size, const char *, ...)
        fprintf(stderr, "Fatal: failed to allocate %zu blocks of %zu bytes.\n", count, size);
        exit(EXIT_FAILURE);
    }

    return p;

}

void *srealloc(void *ptr, size_t size) {

    void *p = realloc(ptr, size);

    if (p == NULL) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", size);
        exit(EXIT_FAILURE);
    }

    return p;

}