#include "tape.h"

tape_t *create_tape() {
    tape_t *tape = (tape_t *)malloc(TAPE_SIZE);
    if (tape == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    tape->current_page = create_page();
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        tape->current_page[i] = create_record();
    }
    return tape;
}

tape_t *initialize_tape(tape_t *tape, char *filename) {
    tape->filename = filename;
    tape->current_page_index = 0;
    return tape;
}

void destroy_tape(tape_t *tape) {
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        free(tape->current_page[i]);
    }
    free(tape->current_page);
    free(tape);
}
