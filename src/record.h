#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "file.h"
#include "record.h"

typedef struct sensible_heat {
    int mass;
    int specific_heat_capacity;
    int temperature_change;
} record_t;

// Create new record - allocate memory.
record_t *create_record();

// Destroy a record - free memory.
void destroy_record(record_t *record);

// Append record to a file.
void append_record(FILE *file, record_t *record);

// Write record to a file at specific index.
void write_record(FILE *file, record_t *record, int record_index);

// Read record from a file at specific index.
record_t *read_record(FILE *file, int record_index);

// Count records in the file.
int count_records(char *filename);

// Calculate sennsible heat.
double calculate_sensible_heat(record_t record);
