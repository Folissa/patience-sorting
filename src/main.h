#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "constants.h"

//  Create new file.
void create_file(const char *filename);

// Open a file in the chosen mode.
FILE *open_file(char *filename, char *mode);

//  Close a file.
void close_file(FILE *file); 

// Check if file exists.
int check_file_existence(char *filename);

// Clear a file.
void clear_file(char *filename);

// Create a file if it doesn't exist or clear it if it does.
void init_file(char *filename);

// Delete a file.
void delete_file(char *filename);

// Copy contents of source file to the destination file.
void copy_file(char *source_filename, char *destination_filename);

// Create new record. 
record_t *create_record();

// Destroy a record.
void destroy_record(record_t *record);

// Append record to a file.
void append_record(char *filename, record_t *record);

// Read record from a file.
record_t *read_record(char *filename, int index);

// Count records in the file.
int count_records(char *filename);

// Calculate sennsible heat.
double calculate_sensible_heat(record_t record);

// Print debug information about the record.
void print_debug(record_t record);

// Print prompt string.
void print_prompt();

// Input records from the user.
void input_records(int records_count);

// Generate a random record.
record_t *randomize_record();

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