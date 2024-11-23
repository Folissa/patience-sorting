#include "tape.h"

tape_t *create_tape(char *filename) {
    tape_t *tape = (tape_t *)malloc(sizeof(tape_t));
    initialize_tape(tape, filename);
    tape->page = create_page();
    return tape;
}

void *initialize_tape(tape_t *tape, char *filename) {
    tape->filename = filename;
    tape->page_index = 0;
    tape->writes = 0;
    tape->reads = 0;
}

void destroy_tape(tape_t *tape) {
    destroy_page(tape->page);
    free(tape);
}

void handle_full_page(tape_t *tape, int write, int read) {
    if (is_page_full(*(tape->page))) {
        if (write)
            write_page(tape);
            
        tape->page_index++;
        tape->page->record_index = 0;
        if (read)
            read_page(tape);
    }
}

void write_page(tape_t *tape) {
    FILE *file = open_file(tape->filename, "r+");
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        int record_index = tape->page_index * RECORD_COUNT_PER_PAGE + i;
        write_record(file, tape->page->records[i], record_index);
        // TODO: Clear tape
        initialize_record(tape->page->records[i]);
    }
    close_file(file);
    (tape->writes)++;
}

void read_page(tape_t *tape) {
    FILE *file = open_file(tape->filename, "r");
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        int record_index = tape->page_index * RECORD_COUNT_PER_PAGE + i;
        read_record(file, tape->page->records[i], record_index);
    }
    close_file(file);
    (tape->reads)++;
}

int is_at_end(tape_t *tape) {
    // TODO: Fix this?
    return !(record_exists(tape->page->records[tape->page->record_index]));
}

void add_record_to_page(tape_t *tape, record_t *record) {
    if (record_exists(tape->page->records[tape->page->record_index])) {
        (tape->page->record_index)++;
    }
    handle_full_page(tape, 1, 0);
    tape->page->records[tape->page->record_index]->mass = record->mass;
    tape->page->records[tape->page->record_index]->specific_heat_capacity = record->specific_heat_capacity;
    tape->page->records[tape->page->record_index]->temperature_change = record->temperature_change;

}

record_t *get_next_record_from_page(tape_t *tape) {
    tape->page->record_index++;
    handle_full_page(tape, 0, 1);
    return tape->page->records[tape->page->record_index];
}
