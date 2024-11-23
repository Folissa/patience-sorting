#pragma once

#include <stdio.h>

#include "record.h"

typedef struct {
    record_t *records[RECORD_COUNT_PER_PAGE];
    int record_index;
} page_t;

// Create new page - allocate memory.
page_t *create_page();

//
void initialize_page(page_t *page);

// Destroy a page - free memory.
void destroy_page(page_t *page);

//
int is_page_full(page_t page);