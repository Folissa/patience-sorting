typedef struct sensible_heat {
    unsigned int mass;
    unsigned int specific_heat_capacity;
    int temperature_change;
} sensible_heat;

#define RECORD_SIZE sizeof(sensible_heat)
#define RECORD_COUNT 4
#define PAGE_SIZE RECORD_COUNT * RECORD_SIZE

