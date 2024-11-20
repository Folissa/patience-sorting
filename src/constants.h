#pragma once

#define PARAMETERS_COUNT (sizeof(record_t) / sizeof(unsigned int))
#define RECORD_COUNT_PER_PAGE 4

#define NULL_CHARACTER_SIZE 1
#define INT_WIDTH 4

#define RECORD_SIZE sizeof(record_t)
#define PAGE_SIZE (RECORD_COUNT_PER_PAGE * RECORD_SIZE)
#define TAPE_SIZE sizeof(tape_t)

#define INPUT_FILENAME "input.txt"
#define TAPE_1_FILENAME "tape-1.txt"
#define TAPE_2_FILENAME "tape-2.txt"
#define TAPE_3_FILENAME "tape-3.txt"
