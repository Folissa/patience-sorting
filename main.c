#include "main.h"

// TODO: Tapes should be implemented using files
// TODO: Write and read one record to and from file [DONE]

// TODO: In the end the number of sorting phases, the amount of writes and reads of pages should be printed out
// TODO: File contents should be printed in the beginning and in the end
// TODO: File contents should be printed after each sorting phase

// TODO: Records should be generated randomly and as an input from the keyboard
// TODO: Test numbers should be available to load from a file [IN PROGRESS]


void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error creating the file");
    }
}


FILE *open_file(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    return file;
}


void close_file(FILE *file) {
    fclose(file);
}


void append_to_file(char *filename, sensible_heat heat) {
    FILE *file = open_file(filename, "ab");

    size_t result = fwrite(&heat, sizeof(struct sensible_heat), 1, file);
    if (result != 1) {
        perror("Error writing to file");
    }

    fclose(file);}


sensible_heat *read_from_file(char *filename, int offset) {
    sensible_heat *heat = (sensible_heat *)malloc(sizeof(sensible_heat));

    FILE *file = open_file(filename, "rb");

    int seek_result = fseek(file, offset, SEEK_SET);
    if (seek_result != 0) {
        perror("Error seeking to position");
        fclose(file);
        return NULL;
    }

    size_t result = fread(heat, sizeof(struct sensible_heat), 1, file);
    if (result != 1)
        perror("Error reading from file");

    fclose(file);    
    return heat;
}


void clear_file(char *filename) {
    FILE *file = open_file(filename, "w");
    fclose(file);
}


void delete_file(char *filename) {
    if (remove(filename) != 0)
        perror("Error deleting the file");
}


void serialize_page(FILE *file) {
    // TODO: Implement
}


void deserialize_page(FILE *file) {
    // TODO: Implement
}


int calculate_sensible_heat(sensible_heat *heat) {
    unsigned int result;

    result = heat->mass * heat->specific_heat_capacity * abs(heat->temperature_change);

    return result;
}


int main() {
    sensible_heat heat_1, heat_2;

    heat_1.mass = 1;
    heat_1.specific_heat_capacity = 2;
    heat_1.temperature_change = 5;

    heat_2.mass = 3;
    heat_2.specific_heat_capacity = 2;
    heat_2.temperature_change = -1;

    char *tape_1 = "tape-1.txt";
    char *tape_2 = "tape-2.txt";
    char *tape_3 = "tape-3.txt";

    delete_file(tape_1);
    create_file(tape_1);

    append_to_file(tape_1, heat_1);
    append_to_file(tape_1, heat_2);

    int records_number = 2;

    for (int i = 0; i < records_number; i++) {
        sensible_heat *heat = read_from_file(tape_1, sizeof(struct sensible_heat) * i);
        printf("DEBUG: Mass: %d\n", heat->mass);
        printf("DEBUG: Specific heat capacity: %d\n", heat->specific_heat_capacity);
        printf("DEBUG: Temperature change: %d\n", heat->temperature_change);
        printf("DEBUG: Calcualted sensible heat: %d\n", calculate_sensible_heat(heat));
        free(heat);
    }

    return 0;
}

