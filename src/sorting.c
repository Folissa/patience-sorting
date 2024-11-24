#include "sorting.h"

int dump_rest(tape_t *source, tape_t *destination, record_t *last_record) {
    int sorted = 1;
    record_t *record = create_record();
    while (!is_at_end(source)) {
        copy_record(get_current(source), record);
        if (record_exists(last_record) && calculate_sensible_heat(*record) < calculate_sensible_heat(*last_record))
            sorted = 0;
        copy_record(record, last_record);
        add_record(destination, record);
        get_next(source);
    }
    destroy_record(record);
    return sorted;
}

void handle_end_of_run(tape_t *source, tape_t *destination) {
    if (is_at_end(source))
        return;
    record_t *last_record = create_record();
    record_t *record = create_record();
    copy_record(get_current(source), last_record);
    copy_record(get_current(source), record);
    while (!is_at_end(source) && calculate_sensible_heat(*record) >= calculate_sensible_heat(*last_record)) {
        copy_record(get_current(source), last_record);
        add_record(destination, record);
        copy_record(get_next(source), record);
    }
    destroy_record(last_record);
    destroy_record(record);
}

int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    int sorted = 1;
    int tape_2_finished = 0;
    int tape_3_finished = 0;
    reset_tape(tape_1);
    move_to_start(tape_2);
    move_to_start(tape_3);
    record_t *last_record_1 = create_record();
    record_t *record_2 = create_record();
    record_t *last_record_2 = create_record();
    record_t *record_3 = create_record();
    record_t *last_record_3 = create_record();
    while (!is_at_end(tape_2) && !is_at_end(tape_3)) {
        copy_record(get_current(tape_2), record_2);
        copy_record(get_current(tape_3), record_3);
        if (!record_exists(record_2)) {
            // No more records in tape_2
            tape_2_finished = 1;
            break;
        }
        if (!record_exists(record_3)) {
            // No more records in tape_3
            tape_3_finished = 1;
            break;
        }
        if (record_exists(last_record_2) && calculate_sensible_heat(*record_2) < calculate_sensible_heat(*last_record_2)) {
            // Handle when the the numbers in the tape_2 are no longer in the rising order.
            sorted = 0;
            handle_end_of_run(tape_3, tape_1);
            initialize_record(last_record_2);
            initialize_record(last_record_3);
            continue;
        } else if (record_exists(last_record_3) && calculate_sensible_heat(*record_3) < calculate_sensible_heat(*last_record_3)) {
            // Handle when the numbers in the tape_3 are no longer in the rising order.
            sorted = 0;
            handle_end_of_run(tape_2, tape_1);
            initialize_record(last_record_2);
            initialize_record(last_record_3);
            continue;
        }
        if (calculate_sensible_heat(*record_2) > calculate_sensible_heat(*record_3)) {
            // We are adding the record from tape_3 to tape_1 as it is smaller
            add_record(tape_1, record_3);
            if (calculate_sensible_heat(*last_record_3) > calculate_sensible_heat(*record_3)) {
                sorted = 0;
            }
            copy_record(record_3, last_record_3);
            copy_record(record_3, last_record_1);
            get_next(tape_3);
        } else {
            // We are adding the record from tape_2 to tape_1 as it is smaller
            add_record(tape_1, record_2);
            if (calculate_sensible_heat(*last_record_2) > calculate_sensible_heat(*record_2)) {
                sorted = 0;
            }
            copy_record(record_2, last_record_2);
            copy_record(record_2, last_record_1);
            get_next(tape_2);
        }
    }
    if (!tape_2_finished) {
        sorted = dump_rest(tape_2, tape_1, last_record_1) && sorted;
    }
    if (!tape_3_finished) {
        sorted = dump_rest(tape_3, tape_1, last_record_1) && sorted;
    }
    destroy_record(last_record_1);
    destroy_record(record_2);
    destroy_record(last_record_2);
    destroy_record(record_3);
    destroy_record(last_record_3);
    write_page(tape_1);
    reset_tape(tape_2);
    reset_tape(tape_3);
    return sorted;
}

void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    move_to_start(tape_1);
    // Reset the tapes
    reset_tape(tape_2);
    reset_tape(tape_3);
    // Clear the tape files
    clear_file(tape_2->filename);
    clear_file(tape_3->filename);
    record_t *last_record = create_record();
    record_t *current_record = get_current(tape_1);
    int toggle_tape = 1;
    while (!is_at_end(tape_1)) {
        if (!record_exists(current_record))
            break;
        if (record_exists(last_record) && calculate_sensible_heat(*last_record) > calculate_sensible_heat(*current_record)) {
            toggle_tape = !toggle_tape;
        }
        if (toggle_tape) {
            add_record(tape_2, current_record);
        } else {
            add_record(tape_3, current_record);
        }
        copy_record(current_record, last_record);
        current_record = get_next(tape_1);
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
        #ifdef DEBUG
        if (!sorted) {
            printf("______________TAPE1_PHASE_%02d______________\n", phases);
            print_tape(tape_1);
        }
        #endif // DEBUG
    }
    #ifdef DEBUG
    printf("------------------STATUS------------------\n");
    printf("Number of phases: %24d\n", phases);
    printf("Number of writes: %24d\n", tape_1->writes + tape_2->writes + tape_3->writes);
    printf("Number of reads: %25d\n", tape_1->reads + tape_2->reads + tape_3->reads);
    #endif // DEBUG
    destroy_tape(tape_2);
    destroy_tape(tape_3);
}
