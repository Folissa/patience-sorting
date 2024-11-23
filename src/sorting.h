#pragma once

#include "constants.h"
#include "record.h"
#include "tape.h"

// Merge from tape_2, and tape_3 into tape_1.
int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3);

// Distribute from tape_1 to tape_2, and tape_3.
void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3);

// Sort tape.
void sort(tape_t *tape_1);
