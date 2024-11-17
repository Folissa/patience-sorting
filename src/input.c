#include "input.h"

void print_prompt() {
    printf("> ");
}


void input_records(int records_count) {
    init_file(TAPE_1);

    for (int i = 0; i < records_count; i++) {
        record_t *record = create_record();
        double mass, specific_heat_capacity, temperature_change;

        print_prompt();
        if (scanf("%lf %lf %lf", &mass, &specific_heat_capacity, &temperature_change) == 3) {
            record->mass = mass;
            record->specific_heat_capacity = specific_heat_capacity;
            record->temperature_change = temperature_change;
        } else {
            printf("Invalid input. Please enter three floating point numbers separated by spaces.\n");
            continue;
        }

        append_record(TAPE_1, record);
        destroy_record(record);
    }
}


void randomize_records(int records_count) {
    init_file(TAPE_1);

    for (int i = 0; i < records_count; i++) {
        record_t *record = randomize_record();
        append_record(TAPE_1, record);
        destroy_record(record);
    }
}


void load_records_from_file(char *filename, int *record_count) {
    init_file(TAPE_1);

    *record_count = count_records(filename);

    copy_file(filename, TAPE_1);
}


void load_records_from_keyboard(int *records_count) {
    printf("Input number of records you will be inputting:\n");
    print_prompt();
    scanf("%d", records_count);
    printf("Input records, one per line, and the values in the following order: mass specific_heat_capacity temperature_change\n");
    input_records(*records_count);
}


record_t *load_records_generated_randomly(int *records_count) {
    printf("Input number of records to generate:\n");
    print_prompt();
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
        print_prompt();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                load_records_from_file(INPUT_FILE, records_count);
                exit = 1;
                break;
            case 2:
                load_records_from_keyboard(records_count);
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