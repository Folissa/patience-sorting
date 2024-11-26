#include "helpers.h"

record_t *randomize_record() {
    record_t *record = create_record();
    int upper_bound = pow(10, INT_WIDTH);
    record->mass = rand() % upper_bound;
    record->specific_heat_capacity = rand() % upper_bound;
    record->temperature_change = rand() % upper_bound;
    return record;
}

void randomize_records(int records_count, int *series, tape_t tape) {
    init_file(tape.filename);
    FILE *file = open_file(tape.filename, "a");
    record_t *last_record = create_record();
    for (int i = 0; i < records_count; i++) {
        record_t *record = randomize_record();
        if (record_exists(last_record) && calculate_sensible_heat(*record) < calculate_sensible_heat(*last_record))
            (*series)++;
        copy_record(record, last_record);
        append_record(file, record);
        destroy_record(record);
    }
    destroy_record(last_record);
    close_file(file);
}
