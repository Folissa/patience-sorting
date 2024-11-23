#include "sorting.h"

int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    //
}

void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    move_to_start(tape_1);
    // Reset the tapes
    reset_tape(tape_2);
    reset_tape(tape_3);
    // Clear the tape files
    clear_file(tape_2->filename);
    clear_file(tape_3->filename);
    // TODO: Potential memory leak?
    record_t *last_record = create_record();
    int toggle_tape = 1;
    while (!is_at_end(tape_1)) {
        record_t *current_record = get_next_record_from_page(tape_1);
        if (!record_exists(current_record))
            break;
        if (record_exists(last_record) && 
            calculate_sensible_heat(*last_record) > calculate_sensible_heat(*current_record)) {
            toggle_tape = !toggle_tape;
        }
        if (toggle_tape) {
            add_record_to_page(tape_2, current_record);
        } else {
            add_record_to_page(tape_3, current_record);
        }
        copy_record(current_record, last_record);
    }
    // Dump all the records to files
    write_page(tape_2);
    write_page(tape_3);
    // Reset pages
    reset_page(tape_2);
    reset_page(tape_3);
    destroy_record(last_record);
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
