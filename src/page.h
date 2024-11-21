#pragma once

#include <stdio.h>

#include "record.h"

typedef struct {
    record_t **records;
} page_t;

// Create new page - allocate memory.
page_t *create_page();

// Destroy a page - free memory.
void destroy_page(page_t *page);

// Write page to a file (tape). Increments number of saves.
void write_page(char *filename, page_t *page, int page_index, int *saves);

// Load page from a file (tape). Increments number of loads.
page_t *read_page(char *filename, int page_index, int *loads);