#include "record.h"

record_t *create_record() {
    record_t *record = (record_t *)malloc(RECORD_SIZE);
    if (record == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return record;
}

void destroy_record(record_t *record) {
    free(record);
}

void append_record(FILE *file, record_t *record) {
    fprintf(file, "%0*u%0*u%0*u",
        INT_WIDTH, record->mass,
        INT_WIDTH, record->specific_heat_capacity,
        INT_WIDTH, record->temperature_change);
}

record_t *read_record(FILE *file, int index) {
    record_t *record = create_record();
    int current_index = 0;
    while (!feof(file)) {
        char buffer[PARAMETERS_COUNT * INT_WIDTH + NULL_CHARACTER_SIZE];
        if (fread(buffer, sizeof(char), PARAMETERS_COUNT * INT_WIDTH, file) == PARAMETERS_COUNT * INT_WIDTH) {
            buffer[PARAMETERS_COUNT * INT_WIDTH] = '\0';
            sscanf(buffer, "%*u%*u%*u",
                INT_WIDTH, &record->mass,
                INT_WIDTH, &record->specific_heat_capacity,
                INT_WIDTH, &record->temperature_change);
            if (current_index == index) {
                return record;
            }
            current_index++;
        } else {
            perror("Error reading from file");
            destroy_record(record);
            return NULL;
        }
    }
    return record;
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

double calculate_sensible_heat(record_t record) {
    double result = record.mass * record.specific_heat_capacity * record.temperature_change;
    return result;
}
