#include "tape.h"

tape_t *create_tape() {
    tape_t *tape = (tape_t *)malloc(TAPE_SIZE);
    if (tape == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return tape;
}

tape_t *initialize_tape(tape_t *tape, char *filename) {
    tape->filename = filename;
    tape->current_page_index = 0;
    for (int i = 0; i < PAGE_SIZE; i++) {
        tape->current_page[i] = NULL;
    }
    return tape;
}

void destroy_tape(tape_t *tape) {
    free(tape);
}
