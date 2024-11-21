#include "page.h"

page_t *create_page() {
    page_t *page = (page_t *)malloc(sizeof(page_t));
    page->records = (record_t **)malloc(RECORD_COUNT_PER_PAGE * sizeof(record_t *));
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        page->records[i] = create_record();
    }
    page->current_record = create_record();
    return page;
}

void initialize_page(page_t *page) {
    page->current_record_index = 0;
}

void destroy_page(page_t *page) {
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        destroy_record(page->records[i]);
    }
    free(page->records);
    free(page);
}

void write_page(char *filename, page_t *page, int page_index, int *saves) {
    FILE *file = open_file(filename, "r+");
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        if (!write_record(file, page->records[i], page_index)) {
            break;
        }
    }
    close_file(file);
    (*saves)++;
}

page_t *read_page(char *filename, int page_index, int *loads) {
    FILE *file = open_file(filename, "r");
    page_t *page = create_page();
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        page->records[i] = read_record(file, page_index);
    }
    close_file(file);
    (*loads)++;
    return page;
}
