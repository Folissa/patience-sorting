#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "page.h"
#include "record.h"

typedef struct {
    char *filename;
    int page_index;
    page_t *page;
    int writes;
    int reads;
} tape_t;

// Create new tape.
tape_t *create_tape(char *filename);

// Initialize all fields of the tape.
void *initialize_tape(tape_t *tape, char *filename);

// Destroy a tape - free memory.
void destroy_tape(tape_t *tape);

//
void handle_full_page(tape_t *tape, int write, int read);

// Write page to a file. Increments number of saves.
void write_page(tape_t *tape);

// Load page from a file. Increments number of loads.
void read_page(tape_t *tape);

int is_at_end(tape_t *tape);

//
void add_record_to_page(tape_t *tape, record_t *record);

//
record_t *get_next_record_from_page(tape_t *tape);