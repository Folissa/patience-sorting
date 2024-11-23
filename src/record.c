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

void write_record(FILE *file, record_t *record, int record_index) {
    int record_size = PARAMETERS_COUNT * INT_WIDTH;
    long int offset = record_index * record_size;
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Error seeking in file");
        return;
    }
    fprintf(file, "%0*d%0*d%0*d",
        INT_WIDTH, record->mass,
        INT_WIDTH, record->specific_heat_capacity,
        INT_WIDTH, record->temperature_change);
}

void read_record(FILE *file, record_t *record, int record_index) {
    int record_size = PARAMETERS_COUNT * INT_WIDTH;
    long int offset = record_index * record_size;
    if (fseek(file, offset, SEEK_SET) != 0) {
        perror("Error seeking in file");
    }
    char buffer[PARAMETERS_COUNT * INT_WIDTH + NULL_CHARACTER_SIZE];
    buffer[PARAMETERS_COUNT * INT_WIDTH] = '\0';
    if (fread(buffer, sizeof(char), PARAMETERS_COUNT * INT_WIDTH, file) == PARAMETERS_COUNT * INT_WIDTH) {
        char temp[INT_WIDTH + NULL_CHARACTER_SIZE];
        temp[INT_WIDTH] = '\0';
        memcpy(temp, buffer, INT_WIDTH);
        record->mass = atoi(temp);
        memcpy(temp, buffer + INT_WIDTH, INT_WIDTH);
        record->specific_heat_capacity = atoi(temp);
        memcpy(temp, buffer + 2 * INT_WIDTH, INT_WIDTH);
        record->temperature_change = atoi(temp);
    }
    else {
        // Reached the EOF
    }
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

// TODO: Move this elsewhere?
int calculate_sensible_heat(record_t record) {
    return record.mass * record.specific_heat_capacity * record.temperature_change;
}
