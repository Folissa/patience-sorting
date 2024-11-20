#include "page.h"

record_t **create_page() {
    record_t **page = (record_t **)malloc(PAGE_SIZE);
    if (page == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return page;
}

void destroy_page(record_t **page) {
    for (int i = 0; i < PAGE_SIZE; i++) {
        destroy_record(page[i]);
    }
    free(page);
}

void serialize_page(char *filename, record_t **page, int saves) {
    FILE *file = open_file(filename, "a");
    for (int i = 0; i < PAGE_SIZE; i++) {
        append_record(file, page[i]);
    }
    close_file(file);
    destroy_page(page);
    saves++;
}

record_t **deserialize_page(char *filename, int index, int loads) {
    FILE *file = open_file(filename, "r");
    record_t **page = create_page();
    for (int i = 0; i < PAGE_SIZE; i++) {
        page[i] = read_record(file, index);
    }
    close_file(file);
    loads++;
    return page;
}
