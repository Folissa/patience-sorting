#include "tape.h"

tape_t *create_tape() {
    tape_t *tape = (tape_t *)malloc(sizeof(tape_t));
    tape->current_page = create_page();
    return tape;
}

void *initialize_tape(tape_t *tape, char *filename) {
    tape->filename = filename;
    tape->current_page_index = 0;
}

void destroy_tape(tape_t *tape) {
    destroy_page(tape->current_page);
    free(tape);
}
