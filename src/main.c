#include "main.h"

// TODO: Tapes should be implemented using files
// TODO: Write and read one record to and from file [DONE]

// TODO: In the end the number of sorting phases, the amount of writes and reads of pages should be printed out
// TODO: File contents should be printed in the beginning and in the end
// TODO: File contents should be printed after each sorting phase

// TODO: Records should be generated randomly [DONE]
// TODO: Records should be able to be inputted from the keyboard
// TODO: Test numbers should be available to load from a file [DONE]

// TODO: (Optional) Prevent user from giving negative numbers

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


void append_record(char *filename, record_t heat) {
    FILE *file = open_file(filename, "ab");

    size_t result = fwrite(&heat, sizeof(record_t), 1, file);
    if (result != 1) {
        perror("Error writing to file");
    }

    close_file(file);
}


record_t *read_record(char *filename, int offset) {
    record_t *heat = (record_t *)malloc(sizeof(record_t));

    FILE *file = open_file(filename, "rb");

    int seek_result = fseek(file, offset, SEEK_SET);
    if (seek_result != 0) {
        perror("Error seeking to position");
        close_file(file);
        return NULL;
    }

    size_t result = fread(heat, sizeof(record_t), 1, file);
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


double calculate_sensible_heat(record_t record) {
    double result;

    result = record.mass * record.specific_heat_capacity * record.temperature_change;

    return result;
}


void print_debug(record_t record) {
    printf("---\n");
    printf("DEBUG: Mass: %.4lf\n", record.mass);
    printf("DEBUG: Specific heat capacity: %.4lf\n", record.specific_heat_capacity);
    printf("DEBUG: Temperature change: %.4lf\n", record.temperature_change);
    printf("DEBUG: Calculated sensible heat: %.4lf\n", calculate_sensible_heat(record));
}


void load_records_from_file(char *filename, record_t *records, int *record_count) {
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


void load_records_from_keyboard() {
    // TODO: Implement
}

record_t *generate_records(record_t *records, int records_count) {
    srand(time(NULL));
    
    for (int i = 0; i < records_count; i++) {
        record_t record;
        // Mass between 0 and 1000 with precision
        record.mass = (rand() % 1001) + ((rand() % 1000) / 1000.0);
        // Specific heat capacity between 1000 and 10000 with precision
        record.specific_heat_capacity = (rand() % 9001 + 1000) + ((rand() % 1000) / 1000.0); 
         // Temperature change between -50 and 50 with precision
        record.temperature_change = (rand() % 101) - 50 + ((rand() % 1000) / 1000.0);
        print_debug(record);
        records[i] = record;
    }

    return records;
}

record_t *load_records_generated_randomly(record_t *records, int *records_count) {
    printf("Input number of records to generate:\n");
    printf("> ");
    scanf("%d", records_count);
    return generate_records(records, *records_count);
}


void print_menu() {
    printf("1. Load test input from file\n");
    printf("2. Load test input from keyboard\n");
    printf("3. Load test input generated randomly\n");
    printf("4. Exit\n");
}

void prompt_for_records(record_t *records, int *record_count) {
    int exit = 0;
    int choice;

    while (!exit) {
        print_menu();
        printf("> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                load_records_from_file(TEST_FILE, records, record_count);
                exit = 1;
                break;
            case 2:
                load_records_from_keyboard();
                exit = 1;
                break;
            case 3:
                load_records_generated_randomly(records, record_count);
                exit = 1;
                break;
            case 4:
                exit = 1;
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    };
} 

record_t *create_records() {
    record_t *records = (record_t *)malloc(sizeof(record_t) * MAX_RECORD_COUNT);
    if (records == NULL) {
        perror("Failed to allocate memory for records");
        return NULL;
    }
    return records;
}

void destroy_records(record_t *records) {
    free(records);
}

int main() {
    char *tape_1 = "tape-1.txt";
    char *tape_2 = "tape-2.txt";
    char *tape_3 = "tape-3.txt";

    int record_count = 0;
    record_t *records;
    
    create_file(tape_1);

    records = create_records();

    prompt_for_records(records, &record_count);

    record_t *record = read_record(tape_1, sizeof(record) * 0);

    print_debug(*record);

    destroy_records(records);
    free(record);
    return 0;
}
