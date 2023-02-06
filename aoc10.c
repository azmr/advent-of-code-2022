#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#undef max

bool streq(char const *a, char const *b)
{   return a && b && (strcmp(a, b) == 0);   }

bool streq_n(char const *a, char const *b, size_t n)
{   return a && b && (strncmp(a, b, n) == 0);   }

// byte-based types (are you shocked and appalled?)
typedef uint8_t  U1;
typedef uint32_t U4;
typedef int32_t  S4;
typedef uint64_t U8;
#define countof(a) (sizeof(a)/sizeof(*(a)))


#if 0
char const *in[] = {
    "noop",
    "addx 3",
    "addx -5",
};

#elif 0
char const *in[] = {
    "addx 15",
    "addx -11",
    "addx 6",
    "addx -3",
    "addx 5",
    "addx -1",
    "addx -8",
    "addx 13",
    "addx 4",
    "noop",
    "addx -1",
    "addx 5",
    "addx -1",
    "addx 5",
    "addx -1",
    "addx 5",
    "addx -1",
    "addx 5",
    "addx -1",
    "addx -35",
    "addx 1",
    "addx 24",
    "addx -19",
    "addx 1",
    "addx 16",
    "addx -11",
    "noop",
    "noop",
    "addx 21",
    "addx -15",
    "noop",
    "noop",
    "addx -3",
    "addx 9",
    "addx 1",
    "addx -3",
    "addx 8",
    "addx 1",
    "addx 5",
    "noop",
    "noop",
    "noop",
    "noop",
    "noop",
    "addx -36",
    "noop",
    "addx 1",
    "addx 7",
    "noop",
    "noop",
    "noop",
    "addx 2",
    "addx 6",
    "noop",
    "noop",
    "noop",
    "noop",
    "noop",
    "addx 1",
    "noop",
    "noop",
    "addx 7",
    "addx 1",
    "noop",
    "addx -13",
    "addx 13",
    "addx 7",
    "noop",
    "addx 1",
    "addx -33",
    "noop",
    "noop",
    "noop",
    "addx 2",
    "noop",
    "noop",
    "noop",
    "addx 8",
    "noop",
    "addx -1",
    "addx 2",
    "addx 1",
    "noop",
    "addx 17",
    "addx -9",
    "addx 1",
    "addx 1",
    "addx -3",
    "addx 11",
    "noop",
    "noop",
    "addx 1",
    "noop",
    "addx 1",
    "noop",
    "noop",
    "addx -13",
    "addx -19",
    "addx 1",
    "addx 3",
    "addx 26",
    "addx -30",
    "addx 12",
    "addx -1",
    "addx 3",
    "addx 1",
    "noop",
    "noop",
    "noop",
    "addx -9",
    "addx 18",
    "addx 1",
    "addx 2",
    "noop",
    "noop",
    "addx 9",
    "noop",
    "noop",
    "noop",
    "addx -1",
    "addx 2",
    "addx -37",
    "addx 1",
    "addx 3",
    "noop",
    "addx 15",
    "addx -21",
    "addx 22",
    "addx -6",
    "addx 1",
    "noop",
    "addx 2",
    "addx 1",
    "noop",
    "addx -10",
    "noop",
    "noop",
    "addx 20",
    "addx 1",
    "addx 2",
    "addx 2",
    "addx -6",
    "addx -11",
    "noop",
    "noop",
    "noop",
};
#else

char const *in[] = {
    "addx 2",
    "addx 4",
    "noop",
    "noop",
    "addx 17",
    "noop",
    "addx -11",
    "addx -1",
    "addx 4",
    "noop",
    "noop",
    "addx 6",
    "noop",
    "noop",
    "addx -14",
    "addx 19",
    "noop",
    "addx 4",
    "noop",
    "noop",
    "addx 1",
    "addx 4",
    "addx -20",
    "addx 21",
    "addx -38",
    "noop",
    "addx 7",
    "noop",
    "addx 3",
    "noop",
    "addx 22",
    "noop",
    "addx -17",
    "addx 2",
    "addx 3",
    "noop",
    "addx 2",
    "addx 3",
    "noop",
    "addx 2",
    "addx -8",
    "addx 9",
    "addx 2",
    "noop",
    "noop",
    "addx 7",
    "addx 2",
    "addx -27",
    "addx -10",
    "noop",
    "addx 37",
    "addx -34",
    "addx 30",
    "addx -29",
    "addx 9",
    "noop",
    "addx 2",
    "noop",
    "noop",
    "noop",
    "addx 5",
    "addx -4",
    "addx 9",
    "addx -2",
    "addx 7",
    "noop",
    "noop",
    "addx 1",
    "addx 4",
    "addx -1",
    "noop",
    "addx -19",
    "addx -17",
    "noop",
    "addx 1",
    "addx 4",
    "addx 3",
    "addx 11",
    "addx 17",
    "addx -23",
    "addx 2",
    "noop",
    "addx 3",
    "addx 2",
    "addx 3",
    "addx 4",
    "addx -22",
    "noop",
    "addx 27",
    "addx -32",
    "addx 14",
    "addx 21",
    "addx 2",
    "noop",
    "addx -37",
    "noop",
    "addx 31",
    "addx -26",
    "addx 5",
    "addx 2",
    "addx 3",
    "addx -2",
    "addx 2",
    "addx 5",
    "addx 2",
    "addx 3",
    "noop",
    "addx 2",
    "addx 9",
    "addx -8",
    "addx 2",
    "addx 11",
    "addx -4",
    "addx 2",
    "addx -15",
    "addx -22",
    "addx 1",
    "addx 5",
    "noop",
    "noop",
    "noop",
    "noop",
    "noop",
    "addx 4",
    "addx 19",
    "addx -15",
    "addx 1",
    "noop",
    "noop",
    "addx 6",
    "noop",
    "noop",
    "addx 5",
    "addx -1",
    "addx 5",
    "addx -14",
    "addx -13",
    "addx 30",
    "noop",
    "addx 3",
    "noop",
    "noop",
};
#endif

#define STR__N(str) str, (sizeof(str)-1)

S4 cycle(U4 *cycle_c, S4 reg_X)
{
    S4 result = 0;
    *cycle_c += 1;
    if (*cycle_c >= 20 &&
        (*cycle_c - 20) % 40 == 0)
    {   result = *cycle_c * reg_X;   }
    return result;
}

U4 aoc10(char const **ops, U4 ops_n)
{
    S4 result  = 0;
    S4 reg_X   = 1;
    U4 cycle_c = 0;

    for (U4 op_i = 0; op_i < ops_n; ++op_i)
    {
        char const *op = ops[op_i];
        S4 addend = 0;

        if (streq(op, "noop"))
        {   addend = cycle(&cycle_c, reg_X); result += addend;   }

        else if (streq_n(op, STR__N("addx")))
        {
            S4 val = 0;
            if (sscanf(op+5, "%d", &val) != 1)
            {   __debugbreak();   }

            addend = cycle(&cycle_c, reg_X); result += addend;
            addend = cycle(&cycle_c, reg_X); result += addend;
            reg_X += val;
        }

        else
        {   __debugbreak();   }
    }

    return result;
}


S4 cycle_b(U4 *cycle_c, S4 reg_x)
{
    S4 draw_x  = *cycle_c % 40;
    if (draw_x == 0)
    {   printf("\n");   }

    *cycle_c += 1;
    S4 sprite_l = reg_x-1;
    S4 sprite_r = reg_x+1;
    bool should_draw = sprite_l <= draw_x && draw_x <= sprite_r;

    printf("%c", should_draw ? '#' : '.');
}


U4 aoc10_b(char const **ops, U4 ops_n)
{
    S4 result  = 0; // EGJBGCFK
    S4 reg_X   = 1;
    U4 cycle_c = 0;

    for (U4 op_i = 0; op_i < ops_n; ++op_i)
    {
        char const *op = ops[op_i];
        S4 addend = 0;

        if (streq(op, "noop"))
        {   addend = cycle_b(&cycle_c, reg_X);   }

        else if (streq_n(op, STR__N("addx")))
        {
            S4 val = 0;
            if (sscanf(op+5, "%d", &val) != 1)
            {   __debugbreak();   }

            addend = cycle_b(&cycle_c, reg_X);
            addend = cycle_b(&cycle_c, reg_X);
            reg_X += val;
        }

        else
        {   __debugbreak();   }
    }

    return result;
}

int main()
{
    aoc10_b(in, countof(in));
}
