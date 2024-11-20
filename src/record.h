#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "file.h"
#include "record.h"

typedef struct sensible_heat {
    unsigned int mass;
    unsigned int specific_heat_capacity;
    unsigned int temperature_change;
} record_t;

// Create new record - allocate memory.
record_t *create_record();

// Destroy a record - free memory.
void destroy_record(record_t *record);

// Append record to a file.
void append_record(char *filename, record_t *record);

// Read record from a file.
record_t *read_record(char *filename, int index);

// Count records in the file.
int count_records(char *filename);

// Calculate sennsible heat.
double calculate_sensible_heat(record_t record);