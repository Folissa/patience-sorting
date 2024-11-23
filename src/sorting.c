#include "sorting.h"

int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    //
}

void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    record_t *last_record;
    int toggle_tape = 1;
    while (!is_at_end(tape_1)) {
        record_t *current_record = get_next_record_from_page(tape_1);
        if (calculate_sensible_heat(*last_record) > calculate_sensible_heat(*current_record)) {
            toggle_tape = !toggle_tape;
        }
        if (toggle_tape) {
            add_record_to_page(tape_2, current_record);
        } else {
            add_record_to_page(tape_3, current_record);
        }
        last_record = current_record;
    }
}

void sort(tape_t *tape_1) {
    int sorted = 0;
    int phases = 0;
    tape_t *tape_2 = create_tape(TAPE_2_FILENAME);
    tape_t *tape_3 = create_tape(TAPE_3_FILENAME);
    while (!sorted) {
        phases++;
        distribute(tape_1, tape_2, tape_3);
        sorted = merge(tape_1, tape_2, tape_3);
    }
    // TODO: Change prints to function
    printf("Number of phases: %d\n", phases);
    printf("Number of writes: %d\n", tape_1->writes + tape_2->writes + tape_3->writes);
    printf("Number of reads: %d\n", tape_1->reads + tape_2->reads + tape_3->reads);
    destroy_tape(tape_2);
    destroy_tape(tape_3);
}
