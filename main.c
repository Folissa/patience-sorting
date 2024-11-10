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


void append_record(char *filename, sensible_heat heat) {
    FILE *file = open_file(filename, "ab");

    size_t result = fwrite(&heat, sizeof(struct sensible_heat), 1, file);
    if (result != 1) {
        perror("Error writing to file");
    }

    close_file(file);
}


sensible_heat *read_record(char *filename, int offset) {
    sensible_heat *heat = (sensible_heat *)malloc(sizeof(sensible_heat));

    FILE *file = open_file(filename, "rb");

    int seek_result = fseek(file, offset, SEEK_SET);
    if (seek_result != 0) {
        perror("Error seeking to position");
        close_file(file);
        return NULL;
    }

    size_t result = fread(heat, sizeof(struct sensible_heat), 1, file);
    if (result != 1)
        perror("Error reading from file");

    close_file(file);    
    return heat;
}


void clear_file(char *filename) {
    FILE *file = open_file(filename, "w");
    close_file(file);
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


double calculate_sensible_heat(sensible_heat heat) {
    double result;

    result = heat.mass * heat.specific_heat_capacity * heat.temperature_change;

    return result;
}


void print_debug(sensible_heat record) {
    printf("---\n");
    printf("DEBUG: Mass: %.2lf\n", record.mass);
    printf("DEBUG: Specific heat capacity: %.2lf\n", record.specific_heat_capacity);
    printf("DEBUG: Temperature change: %.2lf\n", record.temperature_change);
    printf("DEBUG: Calculated sensible heat: %.4lf\n", calculate_sensible_heat(record));
}


void load_test_from_file(char *filename, sensible_heat *records, int *record_count) {
    FILE *file = open_file(filename, "r");

    *record_count = 0;
    while (*record_count < MAX_RECORD_COUNT && fscanf(file, "%lf %lf %lf",
                                        &records[*record_count].mass,
                                        &records[*record_count].specific_heat_capacity,
                                        &records[*record_count].temperature_change) == 3) {
        (*record_count)++;
    }

    close_file(file);
}


void load_test_from_keyboard() {
    // TODO: Implement
}


void print_menu() {
    printf("1. Load test input from file\n");
    printf("2. Load test input from keyboard\n");
    printf("3. Exit\n");
}

void prompt_for_test_type(sensible_heat *records, int *record_count) {
    int exit = 0;
    int choice;

    while (!exit) {
        print_menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                load_test_from_file(TEST_FILE, records, record_count);
                exit = 1;
                break;
            case 2:
                load_test_from_keyboard();
                exit = 1;
                break;
            case 3:
                exit = 1;
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    };
} 

sensible_heat *create_records() {
    sensible_heat *records = (sensible_heat *)malloc(sizeof(sensible_heat) * MAX_RECORD_COUNT);
    if (records == NULL) {
        perror("Failed to allocate memory for records");
        return NULL;
    }
    return records;
}

void destroy_records(sensible_heat *records) {
    free(records);
}

int main() {
    // sensible_heat heat_1, heat_2;

    // heat_1.mass = 1.20;
    // heat_1.specific_heat_capacity = 2;
    // heat_1.temperature_change = 5;

    // heat_2.mass = 3;
    // heat_2.specific_heat_capacity = 2;
    // heat_2.temperature_change = -1;

    // char *tape_1 = "tape-1.txt";
    // char *tape_2 = "tape-2.txt";
    // char *tape_3 = "tape-3.txt";

    // delete_file(tape_1);
    // create_file(tape_1);

    // append_record(tape_1, heat_1);
    // append_record(tape_1, heat_2);

    // int records_number = 2;

    // for (int i = 0; i < records_number; i++) {
    //     sensible_heat *heat = read_record(tape_1, sizeof(struct sensible_heat) * i);
    //     printf("DEBUG: Mass: %.2f\n", heat->mass);
    //     printf("DEBUG: Specific heat capacity: %.2f\n", heat->specific_heat_capacity);
    //     printf("DEBUG: Temperature change: %.2f\n", heat->temperature_change);
    //     printf("DEBUG: Calcualted sensible heat: %.2f\n", calculate_sensible_heat(heat));
    //     free(heat);
    // }
    int record_count = 0;
    sensible_heat *records;
    
    records = create_records();

    prompt_for_test_type(records, &record_count);

    destroy_records(records);
    return 0;
}

