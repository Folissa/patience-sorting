#include "tape.h"

tape_t *create_tape(char *filename) {
    tape_t *tape = (tape_t *)malloc(sizeof(tape_t));
    initialize_tape(tape, filename);
    tape->page = create_page();
    return tape;
}

void initialize_tape(tape_t *tape, char *filename) {
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
        if (!record_exists(tape->page->records[i]))
            break;
        write_record(file, tape->page->records[i], record_index);
        initialize_record(tape->page->records[i]);
    }
    close_file(file);
    (tape->writes)++;
}

void read_page(tape_t *tape) {
    FILE *file = open_file(tape->filename, "r");
    int page_index = tape->page_index;
    int record_size = PARAMETERS_COUNT * INT_WIDTH;
    int records_size = RECORD_COUNT_PER_PAGE * record_size;
    long int page_offset = page_index * records_size;
    if (fseek(file, page_offset, SEEK_SET) != 0) {
        perror("Error seeking in file");
    }
    char buffer[records_size + NULL_CHARACTER_SIZE];
    for (int i = 0; i < records_size + NULL_CHARACTER_SIZE; i++) {
        buffer[i] = '\0';
    }
    if (fread(buffer, sizeof(char), records_size, file)) {
        for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
            int record_offset = i * record_size;
            // Situation: there are records to read, but it will not fill the whole page,
            // so we initalize as they do not exist
            if (buffer[record_offset] == '\0') {
                initialize_record(tape->page->records[i]);
                continue;
            }
            char temp[INT_WIDTH + NULL_CHARACTER_SIZE];
            temp[INT_WIDTH] = '\0';
            memcpy(temp, buffer + record_offset, INT_WIDTH);
            tape->page->records[i]->mass = atoi(temp);
            memcpy(temp, buffer + record_offset + INT_WIDTH, INT_WIDTH);
            tape->page->records[i]->specific_heat_capacity = atoi(temp);
            memcpy(temp, buffer + record_offset + 2 * INT_WIDTH, INT_WIDTH);
            tape->page->records[i]->temperature_change = atoi(temp);
        }
    } else {
        // Reached EOF, mark whole page as non existing
        for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
            initialize_record(tape->page->records[i]);
        }
    }
    close_file(file);
    (tape->reads)++;
}

int is_at_end(tape_t *tape) {
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

void reset_tape(tape_t *tape) {
    reset_page(tape);
    tape->page_index = 0;
}

void reset_page(tape_t *tape) {
    tape->page->record_index = 0;
    for (int i = 0; i < RECORD_COUNT_PER_PAGE; i++) {
        initialize_record(tape->page->records[i]);
    }
}

void move_to_start(tape_t *tape) {
    tape->page->record_index = 0;
    tape->page_index = 0;
    read_page(tape);
}

record_t *get_next_record_from_page(tape_t *tape) {
    tape->page->record_index++;
    handle_full_page(tape, 0, 1);
    return tape->page->records[tape->page->record_index];
}
