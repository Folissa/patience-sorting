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

int record_exists(record_t *record);

// Create new record. Allocate memory, and initialize values.
record_t *create_record();

// Initialize all fields of the record.
void initialize_record(record_t *record);

// Destroy a record.
void destroy_record(record_t *record);

// Append record to a file.
void append_record(FILE *file, record_t *record);

// Write record to a file at specific index.
void write_record(FILE *file, record_t *record, int record_index);

// Read record from a file at specific index.
void read_record(FILE *file, record_t *record, int record_index);

// Count records in the file.
int count_records(char *filename);

// Calculate sennsible heat.
int calculate_sensible_heat(record_t record);
