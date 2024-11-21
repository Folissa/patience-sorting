#pragma once

#include <stdio.h>

#include "record.h"

// Create new page - allocate memory.
record_t **create_page();

// Destroy a page - free memory.
void destroy_page(record_t **page);

// Write page to a file (tape). Increments number of saves.
void write_page(char *filename, record_t **page, int page_index, int *saves);

// Load page from a file (tape). Increments number of loads.
record_t **read_page(char *filename, int page_index, int *loads);