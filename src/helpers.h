#pragma once

#ifndef HELPERS_H
#define HELPERS_H

#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "record.h"
#include "tape.h"

// Generate a random record.
record_t *randomize_record();

// Save randomized records to the main tape.
void randomize_records(int records_count, int *series, tape_t tape);

#endif // HELPERS_H