#include <stdlib.h>
#include <time.h>

#include "tape.h"
#include "input.h"

// TODO: Sorting by heat, tapes should be implemented using files
// TODO: Write and read one record to and from file [DONE]

// TODO: In the end, the number of sorting phases, the amount of writes and reads of pages should be printed out
// TODO: File contents should be printed in the beginning and in the end
// TODO: File contents should be printed after each sorting phase

// TODO: Records should be generated randomly [DONE]
// TODO: Records should be able to be inputted from the keyboard [DONE]
// TODO: Test numbers should be available to load from a file [DONE]

#ifdef DEBUG
// Print debug information about the record.
void print_debug(record_t record) {
    printf("---\n");
    printf("DEBUG: Mass: %u\n", record.mass);
    printf("DEBUG: Specific heat capacity: %u\n", record.specific_heat_capacity);
    printf("DEBUG: Temperature change: %u\n", record.temperature_change);
    printf("DEBUG: Calculated sensible heat: %u\n", calculate_sensible_heat(record));
}
#endif

int main() {
    srand(time(NULL));
    int records_count = 0;
    tape_t *tape_1 = create_tape();
    tape_1 = initialize_tape(tape_1, TAPE_1_FILENAME);
    load_records(&records_count, *tape_1);
    destroy_tape(tape_1);
    return 0;
}
