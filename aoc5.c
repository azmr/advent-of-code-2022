

// AoC day 5 starting shortly...

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
typedef uint32_t U4;
#define countof(a) (sizeof(a)/sizeof(*(a)))

enum { AoC5_stacks_max = 9 };

char const *aoc5_test[] = {
    "    [D]    ",
    "[N] [C]    ",
    "[Z] [M] [P]",
};
U4 aoc5_test_n = countof(aoc5_test);

char const *aoc5_test_ops[] = {
    "move 1 from 2 to 1",
    "move 3 from 1 to 3",
    "move 2 from 2 to 1",
    "move 1 from 1 to 2",
};
U4 aoc5_test_ops_n = countof(aoc5_test_ops);

char const *aoc5_data[] = {
    "                [V]     [C]     [M]",
    "[V]     [J]     [N]     [H]     [V]",
    "[R] [F] [N]     [W]     [Z]     [N]",
    "[H] [R] [D]     [Q] [M] [L]     [B]",
    "[B] [C] [H] [V] [R] [C] [G]     [R]",
    "[G] [G] [F] [S] [D] [H] [B] [R] [S]",
    "[D] [N] [S] [D] [H] [G] [J] [J] [G]",
    "[W] [J] [L] [J] [S] [P] [F] [S] [L]",
};

char const *aoc5_ops[] = {
    "move 2 from 2 to 7",
    "move 8 from 5 to 6",
    "move 2 from 4 to 5",
    "move 1 from 4 to 5",
    "move 1 from 5 to 8",
    "move 5 from 9 to 2",
    "move 7 from 1 to 6",
    "move 7 from 3 to 8",
    "move 1 from 4 to 6",
    "move 2 from 5 to 6",
    "move 6 from 7 to 5",
    "move 2 from 2 to 4",
    "move 4 from 5 to 2",
    "move 10 from 8 to 1",
    "move 2 from 7 to 4",
    "move 4 from 2 to 8",
    "move 2 from 9 to 8",
    "move 1 from 8 to 4",
    "move 2 from 4 to 9",
    "move 5 from 8 to 2",
    "move 1 from 4 to 6",
    "move 1 from 8 to 9",
    "move 1 from 7 to 2",
    "move 2 from 4 to 2",
    "move 1 from 7 to 3",
    "move 13 from 2 to 1",
    "move 1 from 2 to 4",
    "move 1 from 2 to 3",
    "move 2 from 5 to 4",
    "move 17 from 6 to 4",
    "move 3 from 4 to 9",
    "move 14 from 1 to 4",
    "move 4 from 6 to 8",
    "move 1 from 9 to 8",
    "move 23 from 4 to 8",
    "move 6 from 1 to 7",
    "move 3 from 1 to 5",
    "move 1 from 3 to 8",
    "move 5 from 7 to 8",
    "move 1 from 3 to 4",
    "move 1 from 5 to 3",
    "move 1 from 5 to 1",
    "move 1 from 3 to 2",
    "move 1 from 9 to 4",
    "move 9 from 4 to 9",
    "move 1 from 1 to 2",
    "move 11 from 8 to 2",
    "move 1 from 4 to 5",
    "move 13 from 2 to 3",
    "move 7 from 9 to 6",
    "move 1 from 5 to 6",
    "move 1 from 5 to 2",
    "move 1 from 9 to 4",
    "move 1 from 4 to 9",
    "move 2 from 8 to 9",
    "move 1 from 7 to 8",
    "move 8 from 9 to 1",
    "move 8 from 1 to 4",
    "move 4 from 6 to 7",
    "move 1 from 9 to 4",
    "move 2 from 3 to 9",
    "move 1 from 9 to 1",
    "move 6 from 4 to 1",
    "move 2 from 1 to 3",
    "move 22 from 8 to 6",
    "move 1 from 2 to 5",
    "move 3 from 7 to 8",
    "move 15 from 6 to 4",
    "move 7 from 3 to 7",
    "move 4 from 6 to 9",
    "move 2 from 9 to 2",
    "move 6 from 3 to 5",
    "move 3 from 9 to 5",
    "move 5 from 5 to 8",
    "move 1 from 2 to 1",
    "move 6 from 8 to 2",
    "move 1 from 1 to 2",
    "move 3 from 5 to 3",
    "move 1 from 7 to 2",
    "move 4 from 7 to 8",
    "move 4 from 6 to 1",
    "move 1 from 5 to 1",
    "move 4 from 8 to 7",
    "move 2 from 3 to 2",
    "move 1 from 1 to 3",
    "move 15 from 4 to 2",
    "move 3 from 7 to 3",
    "move 4 from 7 to 2",
    "move 1 from 4 to 9",
    "move 5 from 3 to 8",
    "move 29 from 2 to 1",
    "move 1 from 9 to 5",
    "move 1 from 2 to 1",
    "move 11 from 1 to 5",
    "move 1 from 4 to 5",
    "move 2 from 6 to 3",
    "move 1 from 3 to 4",
    "move 16 from 1 to 9",
    "move 4 from 8 to 4",
    "move 3 from 6 to 9",
    "move 1 from 3 to 7",
    "move 1 from 7 to 3",
    "move 6 from 1 to 6",
    "move 3 from 4 to 3",
    "move 3 from 8 to 5",
    "move 3 from 1 to 8",
    "move 3 from 1 to 4",
    "move 2 from 4 to 9",
    "move 3 from 6 to 3",
    "move 15 from 5 to 2",
    "move 3 from 2 to 3",
    "move 4 from 2 to 7",
    "move 2 from 5 to 9",
    "move 10 from 3 to 6",
    "move 11 from 9 to 5",
    "move 2 from 4 to 9",
    "move 8 from 9 to 4",
    "move 1 from 9 to 6",
    "move 7 from 4 to 6",
    "move 3 from 5 to 8",
    "move 22 from 6 to 9",
    "move 4 from 7 to 8",
    "move 8 from 5 to 8",
    "move 2 from 4 to 3",
    "move 1 from 8 to 1",
    "move 17 from 8 to 3",
    "move 3 from 3 to 4",
    "move 13 from 3 to 9",
    "move 20 from 9 to 7",
    "move 2 from 2 to 9",
    "move 19 from 9 to 5",
    "move 1 from 1 to 4",
    "move 3 from 2 to 7",
    "move 4 from 4 to 3",
    "move 1 from 9 to 8",
    "move 18 from 5 to 1",
    "move 1 from 9 to 4",
    "move 1 from 9 to 7",
    "move 2 from 4 to 8",
    "move 1 from 5 to 4",
    "move 3 from 2 to 7",
    "move 3 from 3 to 1",
    "move 2 from 1 to 3",
    "move 3 from 3 to 8",
    "move 1 from 4 to 8",
    "move 6 from 8 to 2",
    "move 1 from 3 to 9",
    "move 1 from 3 to 9",
    "move 10 from 1 to 9",
    "move 7 from 1 to 7",
    "move 4 from 7 to 4",
    "move 29 from 7 to 3",
    "move 6 from 2 to 9",
    "move 25 from 3 to 6",
    "move 5 from 3 to 9",
    "move 13 from 6 to 9",
    "move 12 from 6 to 2",
    "move 1 from 8 to 9",
    "move 10 from 2 to 6",
    "move 7 from 6 to 5",
    "move 20 from 9 to 3",
    "move 11 from 3 to 6",
    "move 1 from 7 to 9",
    "move 2 from 2 to 9",
    "move 19 from 9 to 2",
    "move 14 from 6 to 8",
    "move 4 from 5 to 2",
    "move 2 from 4 to 6",
    "move 3 from 5 to 1",
    "move 13 from 8 to 5",
    "move 1 from 6 to 1",
    "move 2 from 4 to 2",
    "move 8 from 2 to 4",
    "move 6 from 4 to 7",
    "move 1 from 9 to 8",
    "move 2 from 4 to 7",
    "move 5 from 2 to 4",
    "move 4 from 4 to 2",
    "move 10 from 5 to 6",
    "move 1 from 1 to 7",
    "move 1 from 5 to 4",
    "move 1 from 4 to 9",
    "move 4 from 7 to 8",
    "move 5 from 1 to 7",
    "move 1 from 9 to 7",
    "move 7 from 3 to 2",
    "move 2 from 5 to 2",
    "move 8 from 6 to 9",
    "move 1 from 4 to 6",
    "move 3 from 7 to 4",
    "move 5 from 9 to 7",
    "move 2 from 4 to 3",
    "move 20 from 2 to 4",
    "move 2 from 4 to 8",
    "move 14 from 4 to 2",
    "move 12 from 7 to 4",
    "move 8 from 2 to 1",
    "move 10 from 2 to 4",
    "move 6 from 8 to 5",
    "move 1 from 7 to 8",
    "move 4 from 4 to 3",
    "move 1 from 3 to 9",
    "move 1 from 2 to 7",
    "move 1 from 6 to 8",
    "move 5 from 3 to 5",
    "move 1 from 3 to 2",
    "move 7 from 4 to 5",
    "move 6 from 1 to 7",
    "move 5 from 7 to 6",
    "move 1 from 6 to 5",
    "move 2 from 7 to 8",
    "move 1 from 2 to 6",
    "move 2 from 8 to 2",
    "move 5 from 5 to 7",
    "move 6 from 6 to 8",
    "move 16 from 4 to 9",
    "move 16 from 9 to 4",
    "move 11 from 5 to 4",
    "move 5 from 8 to 3",
    "move 2 from 5 to 2",
    "move 14 from 4 to 2",
    "move 1 from 6 to 3",
    "move 1 from 6 to 9",
    "move 1 from 5 to 3",
    "move 3 from 8 to 2",
    "move 10 from 4 to 7",
    "move 5 from 9 to 2",
    "move 3 from 4 to 7",
    "move 1 from 1 to 4",
    "move 3 from 2 to 5",
    "move 2 from 3 to 7",
    "move 1 from 4 to 2",
    "move 18 from 2 to 8",
    "move 3 from 8 to 4",
    "move 5 from 3 to 1",
    "move 1 from 3 to 9",
    "move 1 from 9 to 3",
    "move 8 from 8 to 7",
    "move 2 from 5 to 4",
    "move 1 from 5 to 6",
    "move 1 from 2 to 5",
    "move 1 from 5 to 8",
    "move 1 from 6 to 9",
    "move 3 from 2 to 7",
    "move 27 from 7 to 4",
    "move 2 from 2 to 4",
    "move 4 from 8 to 4",
    "move 1 from 9 to 8",
    "move 3 from 1 to 6",
    "move 1 from 3 to 5",
    "move 3 from 8 to 3",
    "move 1 from 1 to 4",
    "move 1 from 8 to 1",
    "move 3 from 1 to 4",
    "move 2 from 8 to 2",
    "move 2 from 6 to 2",
    "move 8 from 4 to 9",
    "move 1 from 7 to 1",
    "move 1 from 5 to 4",
    "move 1 from 7 to 3",
    "move 4 from 2 to 7",
    "move 1 from 8 to 6",
    "move 8 from 9 to 7",
    "move 1 from 6 to 3",
    "move 3 from 3 to 4",
    "move 37 from 4 to 1",
    "move 1 from 4 to 5",
    "move 13 from 7 to 8",
    "move 6 from 8 to 4",
    "move 5 from 8 to 3",
    "move 1 from 7 to 6",
    "move 4 from 1 to 5",
    "move 1 from 6 to 5",
    "move 2 from 8 to 4",
    "move 32 from 1 to 5",
    "move 1 from 1 to 4",
    "move 5 from 3 to 5",
    "move 1 from 3 to 2",
    "move 1 from 2 to 9",
    "move 19 from 5 to 2",
    "move 1 from 9 to 1",
    "move 16 from 5 to 1",
    "move 7 from 5 to 6",
    "move 1 from 3 to 1",
    "move 11 from 1 to 2",
    "move 18 from 2 to 4",
    "move 1 from 5 to 9",
    "move 8 from 6 to 1",
    "move 10 from 2 to 6",
    "move 7 from 4 to 9",
    "move 2 from 2 to 1",
    "move 7 from 4 to 2",
    "move 5 from 4 to 5",
    "move 2 from 9 to 6",
    "move 9 from 6 to 3",
    "move 5 from 5 to 3",
    "move 8 from 4 to 9",
    "move 7 from 9 to 8",
    "move 4 from 2 to 9",
    "move 10 from 3 to 1",
    "move 6 from 8 to 1",
    "move 2 from 6 to 3",
    "move 5 from 3 to 8",
    "move 3 from 2 to 7",
    "move 1 from 9 to 5",
    "move 1 from 3 to 5",
    "move 2 from 7 to 8",
    "move 1 from 8 to 9",
    "move 1 from 6 to 1",
    "move 23 from 1 to 4",
    "move 2 from 5 to 3",
    "move 1 from 8 to 2",
    "move 2 from 8 to 5",
    "move 2 from 5 to 6",
    "move 1 from 2 to 7",
    "move 1 from 7 to 5",
    "move 4 from 9 to 7",
    "move 1 from 7 to 5",
    "move 1 from 3 to 6",
    "move 3 from 7 to 4",
    "move 1 from 3 to 8",
    "move 1 from 4 to 6",
    "move 6 from 1 to 8",
    "move 4 from 6 to 4",
    "move 2 from 9 to 1",
    "move 1 from 5 to 1",
    "move 19 from 4 to 2",
    "move 2 from 9 to 3",
    "move 1 from 9 to 3",
    "move 9 from 1 to 8",
    "move 1 from 5 to 8",
    "move 1 from 9 to 3",
    "move 2 from 3 to 9",
    "move 3 from 8 to 4",
    "move 1 from 4 to 9",
    "move 1 from 9 to 5",
    "move 2 from 3 to 4",
    "move 6 from 4 to 7",
    "move 3 from 9 to 5",
    "move 4 from 4 to 7",
    "move 1 from 5 to 6",
    "move 18 from 2 to 7",
    "move 13 from 7 to 9",
    "move 3 from 5 to 1",
    "move 1 from 2 to 1",
    "move 1 from 6 to 5",
    "move 3 from 1 to 7",
    "move 1 from 1 to 5",
    "move 7 from 9 to 6",
    "move 8 from 7 to 4",
    "move 11 from 7 to 6",
    "move 5 from 9 to 2",
    "move 17 from 6 to 1",
    "move 2 from 5 to 1",
    "move 11 from 8 to 1",
    "move 20 from 1 to 2",
    "move 3 from 8 to 1",
    "move 1 from 9 to 8",
    "move 1 from 6 to 1",
    "move 11 from 1 to 7",
    "move 18 from 2 to 3",
    "move 12 from 4 to 8",
    "move 11 from 7 to 3",
    "move 7 from 2 to 3",
    "move 2 from 1 to 5",
    "move 1 from 1 to 3",
    "move 1 from 8 to 1",
    "move 1 from 5 to 9",
    "move 1 from 9 to 6",
    "move 1 from 8 to 7",
    "move 1 from 5 to 3",
    "move 1 from 6 to 7",
    "move 2 from 8 to 1",
    "move 8 from 3 to 2",
    "move 7 from 2 to 9",
    "move 6 from 8 to 6",
    "move 1 from 9 to 3",
    "move 2 from 6 to 4",
    "move 5 from 9 to 6",
    "move 7 from 6 to 2",
    "move 8 from 2 to 9",
    "move 2 from 1 to 9",
    "move 2 from 7 to 2",
    "move 2 from 4 to 8",
    "move 1 from 2 to 7",
    "move 25 from 3 to 7",
    "move 7 from 9 to 7",
    "move 1 from 2 to 5",
    "move 1 from 1 to 4",
    "move 3 from 8 to 1",
    "move 3 from 1 to 8",
    "move 3 from 7 to 8",
    "move 15 from 7 to 3",
    "move 10 from 8 to 3",
    "move 1 from 5 to 7",
    "move 1 from 8 to 5",
    "move 3 from 9 to 2",
    "move 1 from 6 to 4",
    "move 2 from 2 to 7",
    "move 1 from 2 to 5",
    "move 14 from 7 to 9",
    "move 1 from 6 to 2",
    "move 1 from 7 to 1",
    "move 1 from 5 to 4",
    "move 3 from 4 to 3",
    "move 1 from 7 to 6",
    "move 1 from 2 to 7",
    "move 1 from 1 to 2",
    "move 3 from 9 to 1",
    "move 1 from 6 to 2",
    "move 2 from 2 to 6",
    "move 17 from 3 to 6",
    "move 1 from 8 to 3",
    "move 1 from 5 to 4",
    "move 2 from 7 to 2",
    "move 9 from 9 to 8",
    "move 1 from 9 to 3",
    "move 16 from 3 to 2",
    "move 1 from 7 to 5",
    "move 5 from 6 to 5",
    "move 1 from 1 to 6",
    "move 1 from 4 to 1",
    "move 1 from 9 to 3",
    "move 9 from 8 to 6",
    "move 3 from 1 to 5",
    "move 1 from 9 to 1",
    "move 16 from 2 to 1",
    "move 2 from 2 to 7",
    "move 2 from 3 to 9",
    "move 2 from 7 to 4",
    "move 2 from 9 to 3",
    "move 3 from 3 to 5",
    "move 1 from 4 to 5",
    "move 1 from 4 to 2",
    "move 1 from 1 to 7",
    "move 1 from 7 to 1",
    "move 1 from 3 to 6",
    "move 2 from 5 to 1",
    "move 3 from 6 to 2",
    "move 2 from 5 to 8",
    "move 8 from 5 to 4",
    "move 1 from 5 to 3",
    "move 1 from 3 to 2",
    "move 1 from 8 to 3",
    "move 1 from 3 to 8",
    "move 4 from 1 to 7",
    "move 9 from 1 to 7",
    "move 6 from 1 to 8",
    "move 3 from 7 to 4",
    "move 7 from 6 to 7",
    "move 11 from 4 to 3",
    "move 2 from 3 to 8",
    "move 8 from 3 to 8",
    "move 4 from 6 to 1",
    "move 1 from 7 to 4",
    "move 2 from 1 to 2",
    "move 8 from 7 to 2",
    "move 1 from 4 to 8",
    "move 10 from 8 to 2",
    "move 2 from 6 to 1",
    "move 1 from 1 to 4",
    "move 1 from 4 to 8",
    "move 2 from 1 to 4",
    "move 6 from 6 to 5",
    "move 1 from 1 to 9",
    "move 2 from 6 to 8",
    "move 1 from 4 to 5",
    "move 1 from 6 to 9",
    "move 4 from 8 to 9",
    "move 1 from 7 to 1",
    "move 6 from 8 to 6",
    "move 1 from 6 to 1",
    "move 1 from 4 to 9",
    "move 2 from 9 to 5",
    "move 5 from 5 to 9",
    "move 8 from 9 to 5",
    "move 2 from 8 to 5",
    "move 3 from 6 to 9",
    "move 8 from 5 to 7",
    "move 5 from 5 to 6",
    "move 1 from 9 to 2",
    "move 1 from 3 to 1",
    "move 1 from 6 to 7",
    "move 1 from 5 to 6",
    "move 24 from 2 to 4",
    "move 3 from 9 to 7",
    "move 16 from 4 to 5",
    "move 2 from 1 to 3",
    "move 12 from 5 to 6",
    "move 1 from 9 to 5",
    "move 4 from 5 to 9",
    "move 1 from 1 to 6",
    "move 1 from 5 to 2",
    "move 2 from 9 to 8",
    "move 1 from 8 to 1",
    "move 5 from 4 to 5",
    "move 2 from 3 to 5",
    "move 1 from 8 to 3",
    "move 1 from 1 to 6",
    "move 3 from 5 to 7",
    "move 1 from 9 to 1",
    "move 1 from 2 to 8",
};


typedef struct {
    char crates[4096];
    U4   crates_n;
} Stack;

char const *
aoc5(char const **rows, U4 rows_n, U4 stacks_n, char const **ops, U4 ops_n)
{
    static char result[AoC5_stacks_max+1]; // JRVNHHCSJ
    static Stack stacks[AoC5_stacks_max] = {0};

    for (U4 row_i = 0; row_i < rows_n; ++row_i)
    {
        for (U4 stack_i = 0; stack_i < stacks_n; ++stack_i)
        {
            U4   o       = stack_i * 4 + 1; // account for noisy characters
            char crate   = rows[row_i][o];
            U4   crate_i = rows_n - (row_i+1); // we're looking top-down, but we'll later access bottom-up

            Stack *stack = &stacks[stack_i];

            // transition from no crates to crates in this stack
            if (crate != ' ' &&
                (row_i == 0 ||
                 rows[row_i-1][o] == ' '))
            {   stack->crates_n = crate_i + 1;   }

            stack->crates[crate_i] = crate;
        }
    }


    for (U4 op_i = 0; op_i < ops_n; ++op_i)
    {
        U4 move_n = 0, src_stack = 0, dst_stack = 0;
        sscanf(ops[op_i], "move %u from %u to %u", &move_n, &src_stack, &dst_stack);

        Stack *src = &stacks[src_stack-1];
        Stack *dst = &stacks[dst_stack-1];

        for (U4 move_i = 0; move_i < move_n; ++move_i)
        {
            if (src->crates_n > 0)
            {
                U4 dst_crate_i = dst->crates_n++;
                U4 src_crate_i = --src->crates_n;
                dst->crates[dst_crate_i] = src->crates[src_crate_i];
            }
        }
    }


    for (U4 i = 0; i < stacks_n; ++i)
    {
        result[i] = stacks[i].crates[stacks[i].crates_n - 1];
    }


    return result;
}

char const *
aoc5b(char const **rows, U4 rows_n, U4 stacks_n, char const **ops, U4 ops_n)
{
    static char result[AoC5_stacks_max+1]; // GNFBSBJLH
    static Stack stacks[AoC5_stacks_max] = {0};

    for (U4 row_i = 0; row_i < rows_n; ++row_i)
    { // initialize stacks
        for (U4 stack_i = 0; stack_i < stacks_n; ++stack_i)
        {
            U4   o       = stack_i * 4 + 1; // account for noisy characters
            char crate   = rows[row_i][o];
            U4   crate_i = rows_n - (row_i+1); // we're looking top-down, but we'll later access bottom-up

            Stack *stack = &stacks[stack_i];

            // transition from no crates to crates in this stack
            if (crate != ' ' &&
                (row_i == 0 ||
                 rows[row_i-1][o] == ' '))
            {   stack->crates_n = crate_i + 1;   }

            stack->crates[crate_i] = crate;
        }
    }


    for (U4 op_i = 0; op_i < ops_n; ++op_i)
    { // do the move operations
        U4 move_n = 0, src_stack = 0, dst_stack = 0;
        sscanf(ops[op_i], "move %u from %u to %u", &move_n, &src_stack, &dst_stack);

        Stack *src = &stacks[src_stack-1];
        Stack *dst = &stacks[dst_stack-1];

        if (move_n > src->crates_n) // don't move more than exist
        {   move_n = src->crates_n;   }

        { // move multiple crates at once
            U4 dst_crate_i = dst->crates_n;
            dst->crates_n += move_n;
            src->crates_n -= move_n;
            U4 src_crate_i = src->crates_n;
            memcpy(&dst->crates[dst_crate_i], &src->crates[src_crate_i],
                   move_n * sizeof(src->crates[src_crate_i]));
        }
    }


    // find the top of each stack
    for (U4 i = 0; i < stacks_n; ++i)
    {
        result[i] = stacks[i].crates[stacks[i].crates_n - 1];
    }


    return result;
}

char const *
aoc5c(char const **rows, U4 rows_n, U4 stacks_n, char const **ops, U4 ops_n)
{
    static char result[AoC5_stacks_max+1]; // GNFBSBJLH
    static char stacks[AoC5_stacks_max][4096] = {0};
    static U4   crates_counts[countof(stacks)] = {0};

    for (U4 row_i = 0; row_i < rows_n; ++row_i)
    { // initialize stacks
        for (U4 stack_i = 0; stack_i < stacks_n; ++stack_i)
        {
            U4   o       = stack_i * 4 + 1; // account for noisy characters
            char crate   = rows[row_i][o];
            U4   crate_i = rows_n - (row_i+1); // we're looking top-down, but we'll later access bottom-up

            // transition from no crates to crates in this stack
            if (crate != ' ' &&
                (row_i == 0 ||
                 rows[row_i-1][o] == ' '))
            {   crates_counts[stack_i] = crate_i + 1;   }

            stacks[stack_i][crate_i] = crate;
        }
    }


    /* for (U4 op_i = 0; op_i < ops_n; ++op_i) */
    /* { // do the move operations */
    /*     U4 move_n = 0, src_stack = 0, dst_stack = 0; */
    /*     sscanf(ops[op_i], "move %u from %u to %u", &move_n, &src_stack, &dst_stack); */

    /*     Stack *src = &stacks[src_stack-1]; */
    /*     Stack *dst = &stacks[dst_stack-1]; */

    /*     if (move_n > src->crates_n) // don't move more than exist */
    /*     {   move_n = src->crates_n;   } */

    /*     { // move multiple crates at once */
    /*         U4 dst_crate_i = dst->crates_n; */
    /*         dst->crates_n += move_n; */
    /*         src->crates_n -= move_n; */
    /*         U4 src_crate_i = src->crates_n; */
    /*         memcpy(&dst->crates[dst_crate_i], &src->crates[src_crate_i], */
    /*                move_n * sizeof(src->crates[src_crate_i])); */
    /*     } */
    /* } */


    /* // find the top of each stack */
    /* for (U4 i = 0; i < stacks_n; ++i) */
    /* { */
    /*     result[i] = stacks[i].crates[stacks[i].crates_n - 1]; */
    /* } */


    return result;
}

void test()
{
    /* aoc5(aoc5_data, countof(aoc5_data), 9, aoc5_ops, countof(aoc5_ops)); */
    /* aoc5b(aoc5_test, countof(aoc5_test), 3, aoc5_test_ops, countof(aoc5_test_ops)); */
    aoc5b(aoc5_data, countof(aoc5_data), 9, aoc5_ops, countof(aoc5_ops));
}
