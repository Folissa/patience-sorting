#pragma once

typedef struct sensible_heat {
    unsigned int mass;
    unsigned int specific_heat_capacity;
    unsigned int temperature_change;
} record_t;

#define RECORD_SIZE sizeof(record_t)
#define PARAMETERS_COUNT sizeof(record_t) / sizeof(unsigned int)
#define NULL_CHARACTER_SIZE 1
#define RECORD_COUNT 4
#define INT_WIDTH 4
#define PAGE_SIZE RECORD_COUNT *RECORD_SIZE
#define MAX_RECORD_COUNT 1000
#define INPUT_FILENAME "input.txt"
#define TAPE_1_FILENAME "tape-1.txt"
#define TAPE_2_FILENAME "tape-2.txt"
#define TAPE_3_FILENAME "tape-3.txt"