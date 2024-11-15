typedef struct sensible_heat {
    double mass;
    double specific_heat_capacity;
    double temperature_change;
} record_t;

#define RECORD_SIZE sizeof(sensible_heat)
#define RECORD_COUNT 4
#define PAGE_SIZE RECORD_COUNT * RECORD_SIZE

#define MAX_RECORD_COUNT 1000
#define INPUT_FILE "input.txt"
#define TAPE_1 "tape-1.txt"
#define TAPE_2 "tape-2.txt"
#define TAPE_3 "tape-3.txt"