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
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        destroy_record(page[i]);
    }
    free(page);
}

void serialize_page(char *filename, record_t **page, int index, int saves) {
    FILE *file = open_file(filename, "r+");
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        if (!write_record(file, page[i], index)) {
            break;
        }
    }
    close_file(file);
    destroy_page(page);
    saves++;
}

record_t **deserialize_page(char *filename, int index, int loads) {
    FILE *file = open_file(filename, "r");
    record_t **page = create_page();
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        page[i] = read_record(file, index);
    }
    close_file(file);
    loads++;
    return page;
}
