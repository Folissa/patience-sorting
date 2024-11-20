#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct { 
    char *filename;
    int current_page_index;
} tape_t;

//
tape_t *create_tape();

//
tape_t *initialize_tape(tape_t *tape, char *filename);

//
void destroy_tape(tape_t *tape);
