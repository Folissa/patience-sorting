#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

void create_file(const char *filename);

FILE *open_file(char *filename, char *mode);

void close_file(FILE *file);

void append_to_file(char *filename, sensible_heat heat);

void read_from_file(char *filename, int offset);

void clear_file(char *filename);

void delete_file(char *filename);

void serialize(FILE *file);

void deserialize(FILE *file);

int calculate_sensible_heat(sensible_heat heat);