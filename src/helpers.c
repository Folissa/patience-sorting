#include "helpers.h"

record_t *randomize_record() {
    record_t *record = create_record();
    int upper_bound = pow(10, INT_WIDTH);

    record->mass = rand() % upper_bound;
    record->specific_heat_capacity = rand() % upper_bound;
    record->temperature_change = rand() % upper_bound;

    return record;
}

void randomize_records(int records_count, tape_t tape) {
    init_file(tape.filename);

    for (int i = 0; i < records_count; i++) {
        record_t *record = randomize_record();
        append_record(tape.filename, record);
        destroy_record(record);
    }
}