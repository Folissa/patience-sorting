#pragma once

#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "records.h"

// Generate a random record.
record_t *randomize_record();

// Save randomized records to the main tape.
void randomize_records(int records_count);