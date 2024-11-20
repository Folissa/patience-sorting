#include "tape.h"

tape_t *create_tape() {
    tape_t *tape = (tape_t *)malloc(sizeof(tape_t));
    if (tape == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return tape;
}

tape_t *initialize_tape(tape_t *tape, char *filename) {
    tape->filename = filename;
    tape->current_page_index = 0;
    return tape;
}

void destroy_tape(tape_t *tape) {
    free(tape);
}