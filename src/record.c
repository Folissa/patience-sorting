#include "record.h"

record_t *create_record() {
    record_t *record = (record_t *)malloc(sizeof(record_t));
    initialize_record(record);
    return record;
}

void initialize_record(record_t *record) {
    record->mass = NOT_POSSIBLE_MASS;
    record->specific_heat_capacity = 0;
    record->temperature_change = 0;
}

int record_exists(record_t *record) {
    if (record->mass == NOT_POSSIBLE_MASS)
        return 0;
    return 1;
}

void destroy_record(record_t *record) {
    free(record);
}

void append_record(FILE *file, record_t *record) {
    fprintf(file, "%0*d%0*d%0*d",
        INT_WIDTH, record->mass,
        INT_WIDTH, record->specific_heat_capacity,
        INT_WIDTH, record->temperature_change);
}

int count_records(char *filename) {
    FILE *file = open_file(filename, "r");
    int records_count = 0;
    char buffer[PARAMETERS_COUNT * INT_WIDTH + NULL_CHARACTER_SIZE];
    while (fread(buffer, sizeof(char), PARAMETERS_COUNT * INT_WIDTH, file) == PARAMETERS_COUNT * INT_WIDTH) {
        records_count++;
    }
    fclose(file);
    return records_count;
}

long long calculate_sensible_heat(record_t record) {
    return (long long)(record.mass * record.specific_heat_capacity * record.temperature_change);
}

void copy_record(record_t *source, record_t *destination) {
    destination->mass = source->mass;
    destination->specific_heat_capacity = source->specific_heat_capacity;
    destination->temperature_change = source->temperature_change;
}