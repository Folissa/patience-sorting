#pragma once

#include <stdio.h>

#include "constants.h"
#include "file.h"
#include "helpers.h"
#include "record.h"
#include "tape.h"

// Print prompt string.
void print_prompt();

// Clear input buffer.
void clear_input_buffer();

// Input records from the user.
void input_records(int records_count, tape_t tape);

//  Load records from an input file to the main tape.
void load_records_from_file(char *filename, int *record_count, tape_t tape);

//  Load records from the user to the main tape.
void load_records_from_keyboard(int *records_count, tape_t tape);

//  Load records generated randomly to the main tape.
record_t *load_records_generated_randomly(int *records_count, tape_t tape);

// Prints a menu with input options to choose from.
void print_menu();

// Prompt user for the input method of the test records, and load them into tape.
void load_records(int *records_count, tape_t tape);
