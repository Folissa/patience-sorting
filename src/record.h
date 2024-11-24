#pragma once

#ifndef RECORD_H
#define RECORD_H

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

// Count records in the file.
int count_records(char *filename);

// Calculate sennsible heat.
int calculate_sensible_heat(record_t record);

void copy_record(record_t *source, record_t *destination);

#endif // RECORD_H