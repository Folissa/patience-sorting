#include "records.h"

void serialize_page(FILE *file) {
    // TODO: Implement
}

void deserialize_page(FILE *file) {
    // TODO: Implement
}

record_t *create_record() {
    record_t *record = (record_t *)malloc(sizeof(record_t));
    if (record == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return record;
}

void destroy_record(record_t *record) {
    free(record);
}

void append_record(char *filename, record_t *record) {
    FILE *file = open_file(filename, "a");

    fprintf(file, "%.2f %.2f %.2f ", record->mass, record->specific_heat_capacity, record->temperature_change);

    close_file(file);
}

record_t *read_record(char *filename, int index) {
    FILE *file = open_file(filename, "r");

    record_t *record = create_record();

    int current_index = 0;
    while (current_index <= index && !feof(file)) {
        if (fscanf(file, "%lf %lf %lf", &record->mass, &record->specific_heat_capacity, &record->temperature_change) == 3) {
            if (current_index == index) {
                close_file(file);
                return record;
            }
            current_index++;
        } else {
            perror("Error reading from file");
            destroy_record(record);
            close_file(file);

            return NULL;
        }
    }

    destroy_record(record);
    close_file(file);

    return record;
}

int count_records(char *filename) {
    FILE *file = open_file(filename, "r");

    int records_count = 0;
    double mass, specific_heat_capacity, temperature_change;

    while (fscanf(file, "%lf %lf %lf", &mass, &specific_heat_capacity, &temperature_change) == 3) {
        records_count++;
    }

    fclose(file);
    return records_count;
}

double calculate_sensible_heat(record_t record) {
    double result;

    result = record.mass * record.specific_heat_capacity * record.temperature_change;

    return result;
}
