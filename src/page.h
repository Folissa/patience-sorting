#pragma once

#include <stdio.h>

#include "record.h"

typedef struct {
    char *filename;
    int current_page_index;
    record_t **current_page;
} xs_t;

// Create new page - allocate memory.
record_t **create_page();

// Destroy a page - free memory.
void destroy_page(record_t **page);

// Write page to a file (tape). Increments number of saves.
void serialize_page(char *filename, record_t **page, int index, int saves);

// Load page from a file (tape). Increments number of loads.
record_t **deserialize_page(char *filename, int index, int loads);