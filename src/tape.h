#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "record.h"

typedef struct {
    char *filename;
    int current_page_index;
    record_t **current_page;
} tape_t;

// Create new tape - allocate memory.
tape_t *create_tape();

// Initialize all fields of a tape.
tape_t *initialize_tape(tape_t *tape, char *filename);

// Destroy a tape - free memory.
void destroy_tape(tape_t *tape);
