#include "helpers.h"

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
