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


record_t *create_record() {
    record_t *record = (record_t *)malloc(sizeof(record_t));
    if (record == NULL) {
        perror("Error allocating memory");
        return NULL;
    }
    return record;
}


void destroy_record(record_t *record) {
    free(record);
}


void append_record(char *filename, record_t *record) {
    FILE *file = open_file(filename, "a");

    fprintf(file, "%.2f %.2f %.2f ", record->mass, record->specific_heat_capacity, record->temperature_change);

    close_file(file);
}


record_t *read_record(char *filename, int index) {
    FILE *file = open_file(filename, "r");

    record_t *heat = create_record();

    int current_index = 0;
    while (current_index <= index && !feof(file)) {
        if (fscanf(file, "%lf %lf %lf", &heat->mass, &heat->specific_heat_capacity, &heat->temperature_change) == 3) {
            if (current_index == index) {
                close_file(file);
                return heat;
            }
            current_index++;
        } else {
            perror("Error reading from file");
            destroy_record(heat);
            close_file(file);
            return NULL;
        }
    }

    destroy_record(heat);
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


int count_records(char *filename) {
    FILE *file = open_file(filename, "r");

    int records_count = 0;
    double record_value_1, record_value_2, record_value_3; 
    
    while (fscanf(file, "%lf %lf %lf", &record_value_1, &record_value_2, &record_value_3) == 3) {
        records_count++;
    }

    fclose(file);
    return records_count; 
}


void copy_file(char *source_filename, char *destination_filename) {
    FILE *source_file = open_file(source_filename, "r");
    FILE *destination_file = open_file(destination_filename, "w");
    
    char character;

    while ((character = fgetc(source_file)) != EOF) {
        fputc(character, destination_file);
    }

    close_file(source_file);
    close_file(destination_file);
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
    printf("DEBUG: Mass: %.2lf\n", record.mass);
    printf("DEBUG: Specific heat capacity: %.2lf\n", record.specific_heat_capacity);
    printf("DEBUG: Temperature change: %.2lf\n", record.temperature_change);
    printf("DEBUG: Calculated sensible heat: %.6lf\n", calculate_sensible_heat(record));
}


void load_records_from_file(char *filename, int *record_count) {
    *record_count = count_records(filename);
    copy_file(filename, TAPE_1);
}


void load_records_from_keyboard() {
    // TODO: Implement
}


record_t *randomize_record() {    
    record_t *record = create_record();
    
    // Mass between 0 and 1000 with precision
    record->mass = (rand() % 1001) + ((rand() % 1000) / 1000.0);

    // Specific heat capacity between 1000 and 10000 with precision
    record->specific_heat_capacity = (rand() % 9001 + 1000) + ((rand() % 1000) / 1000.0); 
    
    // Temperature change between -50 and 50 with precision
    record->temperature_change = (rand() % 101) - 50 + ((rand() % 1000) / 1000.0);

    return record;
}


void randomize_records(int records_count) {
    clear_file(TAPE_1);

    for (int i = 0; i < records_count; i++) {
        record_t *record = randomize_record();
        append_record(TAPE_1, record);
        destroy_record(record);
    }
}


record_t *load_records_generated_randomly(int *records_count) {
    printf("Input number of records to generate:\n");
    printf("> ");
    scanf("%d", records_count);
    randomize_records(*records_count);
}


void print_menu() {
    printf("1. Load test input from file\n");
    printf("2. Load test input from keyboard\n");
    printf("3. Load test input generated randomly\n");
    printf("4. Exit\n");
}


void prompt_for_records(int *records_count) {
    int exit = 0;
    int choice;

    while (!exit) {
        print_menu();
        printf("> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                load_records_from_file(INPUT_FILE, records_count);
                exit = 1;
                break;
            case 2:
                load_records_from_keyboard();
                exit = 1;
                break;
            case 3:
                load_records_generated_randomly(records_count);
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


int main() {
    srand(time(NULL));

    int records_count = 0;

    prompt_for_records(&records_count);

    return 0;
}
