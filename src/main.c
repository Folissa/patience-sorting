#include <stdlib.h>
#include <time.h>

#include "tape.h"
#include "input.h"
#include "sorting.h"

// TODO: Sorting by heat, tapes should be implemented using files [DONE]
// TODO: Write and read one record to and from file [DONE]

// TODO: In the end, the number of sorting phases, the amount of writes and reads of pages should be printed out [D0NE]
// TODO: File contents should be printed in the beginning and in the end [DONE]
// TODO: File contents should be printed after each sorting phase [DONE]

// TODO: Records should be generated randomly [DONE]
// TODO: Records should be able to be inputted from the keyboard [DONE]
// TODO: Test numbers should be available to load from a file [DONE]

int main() {
    srand(time(NULL));
    
    int records_count = 0;

    init_file(TAPE_1_FILENAME);
    init_file(TAPE_2_FILENAME);
    init_file(TAPE_3_FILENAME);

    tape_t *tape_1 = create_tape(TAPE_1_FILENAME);
    load_records(&records_count, *tape_1);
    #ifdef DEBUG
    printf("___________TAPE1_BEFORE_SORTING___________\n");
    print_tape(tape_1);
    #endif // DEBUG
    sort(tape_1);
    #ifdef DEBUG
    printf("___________TAPE1_AFTER__SORTING___________\n");
    print_tape(tape_1);
    #endif // DEBUG
    destroy_tape(tape_1);
    return 0;
}
