#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#undef max

bool dbg = 0;

#define printf(...) if (dbg) printf(__VA_ARGS__)

#if 0
char const *in[] = {
    "Monkey 0:",
        "  Starting items: 79, 98",
        "  Operation: new = old * 19",
        "  Test: divisible by 23",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 3",
        "",
        "Monkey 1:",
        "  Starting items: 54, 65, 75, 74",
        "  Operation: new = old + 6",
        "  Test: divisible by 19",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 0",
        "",
        "Monkey 2:",
        "  Starting items: 79, 60, 97",
        "  Operation: new = old * old",
        "  Test: divisible by 13",
        "    If true: throw to monkey 1",
        "    If false: throw to monkey 3",
        "",
        "Monkey 3:",
        "  Starting items: 74",
        "  Operation: new = old + 3",
        "  Test: divisible by 17",
        "    If true: throw to monkey 0",
        "    If false: throw to monkey 1",
};

#else

char const *in[] = {
    "Monkey 0:",
    "  Starting items: 54, 61, 97, 63, 74",
    "  Operation: new = old * 7",
    "  Test: divisible by 17",
    "    If true: throw to monkey 5",
    "    If false: throw to monkey 3",
    "",
    "Monkey 1:",
    "  Starting items: 61, 70, 97, 64, 99, 83, 52, 87",
    "  Operation: new = old + 8",
    "  Test: divisible by 2",
    "    If true: throw to monkey 7",
    "    If false: throw to monkey 6",
    "",
    "Monkey 2:",
    "  Starting items: 60, 67, 80, 65",
    "  Operation: new = old * 13",
    "  Test: divisible by 5",
    "    If true: throw to monkey 1",
    "    If false: throw to monkey 6",
    "",
    "Monkey 3:",
    "  Starting items: 61, 70, 76, 69, 82, 56",
    "  Operation: new = old + 7",
    "  Test: divisible by 3",
    "    If true: throw to monkey 5",
    "    If false: throw to monkey 2",
    "",
    "Monkey 4:",
    "  Starting items: 79, 98",
    "  Operation: new = old + 2",
    "  Test: divisible by 7",
    "    If true: throw to monkey 0",
    "    If false: throw to monkey 3",
    "",
    "Monkey 5:",
    "  Starting items: 72, 79, 55",
    "  Operation: new = old + 1",
    "  Test: divisible by 13",
    "    If true: throw to monkey 2",
    "    If false: throw to monkey 1",
    "",
    "Monkey 6:",
    "  Starting items: 63",
    "  Operation: new = old + 4",
    "  Test: divisible by 19",
    "    If true: throw to monkey 7",
    "    If false: throw to monkey 4",
    "",
    "Monkey 7:",
    "  Starting items: 72, 51, 93, 63, 80, 86, 81",
    "  Operation: new = old * old",
    "  Test: divisible by 11",
    "    If true: throw to monkey 0",
    "    If false: throw to monkey 4",
    "",
};

#endif

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

typedef struct Item {
    U8           worry;
    struct Item *next_item;
} Item;

typedef struct Monkey {
    Item *first_item, *last_item;
    U8 items_n;
    U8 inspect_c;
    char op[3];
    U8 test_div;
    U8 tgts[2];
} Monkey;

Item *remove_item(Monkey *monkey, Item *pre_item)
{
    Item *item = NULL;

    if (! pre_item)
    {
        item = monkey->first_item;
        if (item)
        {   monkey->first_item = item->next_item;   }
    }

    else
    {
        item = pre_item->next_item;
        if (item)
        {   pre_item->next_item = item->next_item;   }
    }

    if (item == monkey->last_item)
    {   monkey->last_item = pre_item;   }

    if (!item) __debugbreak();
    monkey->items_n -= !!item;
    return item;
}

Item *add_item(Monkey *monkey, Item *item)
{
    if (item)
    {
        ++monkey->items_n;
        item->next_item = NULL;

        if (! monkey->first_item)
        {   monkey->first_item = item;   }

        if (monkey->last_item)
        {   monkey->last_item->next_item = item;   }

        monkey->last_item = item;
    }

    return item;
}

void
print_round_results(Monkey *monkeys, U8 monkey_c, U8 round_num)
{
    (printf)("\nEnd of round %zu\n", round_num);
    for (Monkey *monkey = monkeys, *end = monkeys + monkey_c;
         monkey < end;
         ++monkey)
    {
        (printf)("Monkey %llu: ", monkey - monkeys);

        for (Item *item = monkey->first_item; item; item = item->next_item)
        {
            (printf)("%s%llu(0x%zx)",
                     (item == monkey->first_item ? "" : ", "),
                     item->worry, ((U8)item) & 0xffff);
        }
        (printf)("\n");
    }

}

void
print_inspections(Monkey *monkeys, U8 monkey_c, U8 round_num)
{
    (printf)("\nEnd of round %zu\n", round_num);
    for (Monkey *monkey = monkeys, *end = monkeys + monkey_c;
         monkey < end;
         ++monkey)
    {
        (printf)("Monkey %llu: %zu inspections\n", monkey - monkeys, monkey->inspect_c);
    }
}

void
do_rounds(Monkey *monkeys, U8 monkey_c, U8 lcm, U8 rounds_n)
{
    printf("\n\n---------------------------\n");
    for (U8 round_i = 0; round_i < rounds_n; ++round_i)
    { // do rounds (moving items)
#define U "\e[91m%llu\e[m"

        for (U8 monkey_i = 0; monkey_i < monkey_c; ++monkey_i)
        {
            printf("\nMonkey %zu:\n", monkey_i);
            Monkey *monkey = &monkeys[monkey_i];
            for (Item *item = monkey->first_item, *next_item = NULL, *pre_item = NULL;
                 item;
                 item = next_item)
            {
                next_item = item->next_item;
                ++monkey->inspect_c;

                printf("  Monkey inspects an item with a worry level of " U ".\n", item->worry);
                { // op
                    U8 val = item->worry;

                    if (monkey->op[1] != 'o')
                    { // handle digits
                        val = monkey->op[1]-'0';
                        if (monkey->op[2])
                        {
                            val *= 10;
                            val += monkey->op[2]-'0';
                        }
                    }

                    U8 new_worry = 0;
                    switch (monkey->op[0])
                    {
                        case '*': new_worry = item->worry * val; break;
                        case '+': new_worry = item->worry + val; break;
                        default: __debugbreak();
                    }
                    item->worry = lcm ? new_worry % lcm : new_worry;
                    printf("    Worry level is multiplied by " U " to " U ", mod to " U ".\n", val, new_worry, item->worry);
                }

                bool test_result = item->worry % monkey->test_div == 0;
                printf("    Current worry level is %sdivisible by " U ".\n",
                       (test_result ? "" : "not "), monkey->test_div);

                U8      tgt_i = monkey->tgts[test_result];
                Monkey *tgt   = &monkeys[tgt_i];
                printf("    Item with worry level " U " is thrown to monkey " U ".\n", item->worry, tgt_i);

                if (pre_item && ! pre_item->next_item)
                {   __debugbreak();   }

                Item *removed = remove_item(monkey, pre_item);
                if (! removed) __debugbreak();
                if (pre_item && removed->next_item != pre_item->next_item) __debugbreak();
                add_item(tgt, removed);
            }
        }

        if (dbg) print_round_results(monkeys, monkey_c, round_i+1);
    }
}


U8 aoc11(char const **in, U8 in_n)
{
    // add monkeys to list
    //   > items
    //   > op
    //   > test + dests
    Monkey monkeys[8] = {0};

    U8 monkey_c = 0;
    for (U8 in_i = 0; in_i < in_n;)
    {
        Monkey *monkey = &monkeys[monkey_c++];
        ++in_i; // monkey
        char const *items_str  = in[in_i++];
        char const *op_str     = in[in_i++];
        char const *test_str   = in[in_i++];
        char const *true_str   = in[in_i++];
        char const *false_str  = in[in_i++];
        ++in_i; // gap


        { // items
            U8  items[8] = {0};
            int items_n = sscanf(items_str,
                                 "  Starting items: %zu, %zu, %zu, %zu, %zu, %zu, %zu, %zu",
                                 &items[0], &items[1], &items[2], &items[3],
                                 &items[4], &items[5], &items[6], &items[7]);

            for (int item_i = 0; item_i < items_n; ++item_i)
            {
                Item *item = malloc(sizeof(Item));
                *item      = (Item){ items[item_i] };

                add_item(monkey, item);
            }

            if (items_n != monkey->items_n) __debugbreak();
            U8 item_c = 0;
            for (Item *item = monkey->first_item; item; item = item->next_item)
            {   ++item_c;   }

            if (items_n != item_c) __debugbreak();
        }

        { // operation
            sscanf(op_str, "  Operation: new = old %c %c%c",
                   &monkey->op[0], &monkey->op[1], &monkey->op[2]);
        }

        { // test
            sscanf(test_str, "  Test: divisible by %zu", &monkey->test_div);
            sscanf(true_str,  "    If true: throw to monkey %zu", &monkey->tgts[true]);
            sscanf(false_str, "    If false: throw to monkey %zu", &monkey->tgts[false]);
        }
    }

    do_rounds(monkeys, monkey_c, 0, 20);

    U8 max_cs[2] = {0};

    for (U8 i = 0; i < monkey_c; ++i)
    { // calculate monkey business
        U8 c = monkeys[i].inspect_c;
        if (c > max_cs[1])
        {
            max_cs[0] = max_cs[1];
            max_cs[1] = c;
        }
        else if (c > max_cs[0])
        {   max_cs[0] = c;   }
    }

    U8 result = max_cs[0] * max_cs[1];
    return result;
}

U8 get_monkeys(char const **in, U8 in_n, Monkey *monkeys, U8 *monkey_c, Item *item_pool, U8 *item_pool_n)
{
    U8 lcm = 1;

    for (U8 in_i = 0; in_i < in_n;)
    { // get monkey info
        Monkey *monkey = &monkeys[monkey_c[0]++];
        ++in_i; // monkey
        char const *items_str  = in[in_i++];
        char const *op_str     = in[in_i++];
        char const *test_str   = in[in_i++];
        char const *true_str   = in[in_i++];
        char const *false_str  = in[in_i++];
        ++in_i; // gap


        { // items
            U8  items[8] = {0};
            int items_n = sscanf(items_str,
                                 "  Starting items: %zu, %zu, %zu, %zu, %zu, %zu, %zu, %zu",
                                 &items[0], &items[1], &items[2], &items[3],
                                 &items[4], &items[5], &items[6], &items[7]);

            for (int item_i = 0; item_i < items_n; ++item_i)
            {
                Item *item = &item_pool[item_pool_n[0]++];
                *item      = (Item){ items[item_i] };

                add_item(monkey, item);
            }

            if (items_n != monkey->items_n) __debugbreak();
            U8 item_c = 0;
            for (Item *item = monkey->first_item; item; item = item->next_item)
            {   ++item_c;   }


            if (items_n != item_c) __debugbreak();
        }

        { // operation
            sscanf(op_str, "  Operation: new = old %c %c%c",
                   &monkey->op[0], &monkey->op[1], &monkey->op[2]);
        }

        { // test
            sscanf(test_str, "  Test: divisible by %zu", &monkey->test_div);
            sscanf(true_str,  "    If true: throw to monkey %zu", &monkey->tgts[true]);
            sscanf(false_str, "    If false: throw to monkey %zu", &monkey->tgts[false]);
            lcm *= monkey->test_div;
        }
    }

    return lcm;
}

U8 aoc11b(char const **in, U8 in_n)
{
    // add monkeys to list
    //   > items
    //   > op
    //   > test + dests
    Monkey      monkeys[8]    = {0};
    U8          monkey_c      = 0;
    static Item item_pool[40] = {0};
    U8          item_pool_n   = 0;
    U8          lcm  = get_monkeys(in, in_n, monkeys, &monkey_c, item_pool, &item_pool_n);

    for (U8 i = 1; i <= 1000; ++i)
    {
        do_rounds(monkeys, monkey_c, lcm, 10);
        if (i == 20 || (i % 1000 == 0))
        {
            print_inspections(monkeys, monkey_c, (i));
            print_round_results(monkeys, monkey_c, (i));
        }
    }

    U8 max_cs[2] = {0};

    for (U8 i = 0; i < monkey_c; ++i)
    { // calculate monkey business
        U8 c = monkeys[i].inspect_c;
        if (c > max_cs[1])
        {
            max_cs[0] = max_cs[1];
            max_cs[1] = c;
        }
        else if (c > max_cs[0])
        {   max_cs[0] = c;   }
    }

    U8 result = max_cs[0] * max_cs[1];
    return result;
}

int main()
{
    aoc11b(in, countof(in));
}
