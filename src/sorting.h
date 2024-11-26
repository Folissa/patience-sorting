#pragma once

#ifndef SORTING_H
#define SORTING_H

#include "constants.h"
#include "record.h"
#include "tape.h"

// Merge from tape_2, and tape_3 into tape_1.
int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3);

// Distribute from tape_1 to tape_2, and tape_3.
void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3);

// Sort tape.
void sort(tape_t *tape_1);

// Handle when end of run.
void handle_end_of_run(tape_t *source, tape_t *destination);

// Dump all of the record left in the source tape to the destination tape.
int dump_rest(tape_t *source, tape_t *desitnation, record_t *last_record);

#endif // SORTING_H