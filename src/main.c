#include <stdlib.h>
#include <time.h>

#include "tape.h"
#include "input.h"
#include "sorting.h"

// TODO: Sorting by heat, tapes should be implemented using files
// TODO: Write and read one record to and from file [DONE]

// TODO: In the end, the number of sorting phases, the amount of writes and reads of pages should be printed out [D0NE]
// TODO: File contents should be printed in the beginning and in the end
// TODO: File contents should be printed after each sorting phase

// TODO: Records should be generated randomly [DONE]
// TODO: Records should be able to be inputted from the keyboard [DONE]
// TODO: Test numbers should be available to load from a file [DONE]

#ifdef DEBUG
// Print debug information about the record.
void print_debug(record_t record) {
    printf("---\n");
    printf("DEBUG: Mass: %d\n", record.mass);
    printf("DEBUG: Specific heat capacity: %d\n", record.specific_heat_capacity);
    printf("DEBUG: Temperature change: %d\n", record.temperature_change);
    printf("DEBUG: Calculated sensible heat: %d\n", calculate_sensible_heat(record));
}
#endif

int main() {
    srand(time(NULL));
    
    int records_count = 0;
    int loads = 0;
    int saves = 0;

    init_file(TAPE_1_FILENAME);
    init_file(TAPE_2_FILENAME);
    init_file(TAPE_3_FILENAME);

    tape_t *tape_1 = create_tape(TAPE_1_FILENAME);
    tape_t *tape_2 = create_tape(TAPE_2_FILENAME);
    tape_t *tape_3 = create_tape(TAPE_3_FILENAME);

    load_records(&records_count, *tape_1);

    // sort(tape_1);

    distribute(tape_1, tape_2, tape_3);

    // read_page(tape_1);
    // record_t *record = tape_1->page->records[0];
    // while (!is_at_end(tape_1)) {
    //     add_record_to_page(tape_2, record);
    //     record = get_next_record_from_page(tape_1);
    // }
    // write_page(tape_2);

    destroy_tape(tape_3);
    destroy_tape(tape_2);
    destroy_tape(tape_1);
    return 0;
}
