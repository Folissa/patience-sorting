#pragma once

#include <stdio.h>

#include "constants.h"
#include "file.h"
#include "helpers.h"
#include "records.h"

// Print prompt string.
void print_prompt();

// Input records from the user.
void input_records(int records_count);

// Save randomized records to the main tape.
void randomize_records(int records_count);

//  Load records from an input file to the main tape.
void load_records_from_file(char *filename, int *record_count);

//  Load records from the user to the main tape.
void load_records_from_keyboard(int *records_count);

//  Load records generated randoml to the main tape.
record_t *load_records_generated_randomly(int *records_count);

// Prints a menu with options to choose from.
void print_menu();

// Prompt user for the input method of the test records.
void prompt_for_records(int *records_count);