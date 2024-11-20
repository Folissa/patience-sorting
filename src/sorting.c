#include "sorting.h"

int merge(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    // 
}

void distribute(tape_t *tape_1, tape_t *tape_2, tape_t *tape_3) {
    //
}

void sort(tape_t *tape_1) {
    int sorted = 0;
    int phases = 0;

    tape_t *tape_2 = create_tape();
    tape_2 = initialize_tape(tape_2, TAPE_2_FILENAME);
 
    tape_t *tape_3 = create_tape();
    tape_3 = initialize_tape(tape_3, TAPE_3_FILENAME);

    while (!sorted) {
        phases++;
        distribute(tape_1, tape_2, tape_3);
        sorted = merge(tape_1, tape_2, tape_3);
    }

    printf("Number of phases: %d\n", phases);

    destroy_tape(tape_2);
    destroy_tape(tape_3);
}