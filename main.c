#include <stdio.h>
#include <stdlib.h>

#include "constants.h"


void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error creating the file");
    }
}


FILE *open_file(const char *filename) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening the file");
        return NULL;
    }
    return file;
}


void close_file(FILE *file) {
    fclose(file);
}


void write_ints_to_file(FILE *file, int number) {
    // TODO: Implement
}


void read_ints_from_file(FILE *file) {
    // TODO: Implement
}


void clear_file() {
    // TODO: Implement
}


void delete_file(char *filename) {
    if (remove(filename) != 0)
        perror("Error deleting the file");
}


void serialize(FILE *file) {
    // TODO: Implement
}


void deserialize(FILE *file) {
    // TODO: Implement
}


int calculate_sensible_heat(sensible_heat heat) {
    unsigned int result;

    result = heat.mass * heat.specific_heat_capacity * abs(heat.temperature_change);

    return result;
}


int main() {
    sensible_heat heat;

    char *my_filename = "file.txt";
    char *tape_1 = "tape-1.txt";
    char *tape_2 = "tape-2.txt";
    char *tape_3 = "tape-3.txt";

    create_file(my_filename);
    FILE *file = open_file(my_filename);
    close_file(file);

    return 0;
}

