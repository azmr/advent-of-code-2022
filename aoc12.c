
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#undef max
typedef uint8_t  U1;
typedef uint32_t U4;
typedef int32_t  S4;
typedef uint64_t U8;
#define countof(a) (sizeof(a)/sizeof(*(a)))

#ifdef assert
#undef assert
#endif
#define assert(x, ...) ((x) ? 1 : \
                   (fprintf(stderr, "break at line %d, %s, failed:\n    "#x"\n", __LINE__, __func__), \
                    fprintf(stderr, "" __VA_ARGS__),\
                    fflush(stderr), __debugbreak(), 0))

/* bool dbg = 1; */

/* #define printf(...) if (dbg) printf(__VA_ARGS__) */
#define printf(...)

#if 0
char data[][8] = {
    { "Sabqponm" },
    { "abcryxxl" },
    { "accszExk" },
    { "acctuvwj" },
    { "abdefghi" },
};

#else

char data[][66] = {
    "abcccccccaaaaaccccaaaaaaaccccccccccccccccccccccccccccccccccccaaaaa",
    "abaacccaaaaaaccccccaaaaaaaaaaaaaccccccccccccccccccccccccccccaaaaaa",
    "abaacccaaaaaaaccccaaaaaaaaaaaaaacccccccccccccaacccccccccccccaaaaaa",
    "abaacccccaaaaaacaaaaaaaaaaaaaaaacccccccccccccaacccccccccccccacacaa",
    "abaccccccaaccaacaaaaaaaaaacccaacccccccccccccaaacccccccccccccccccaa",
    "abcccccccaaaacccaaaaaaaaacccccccccccccaaacccaaacccccccccccccccccaa",
    "abccccccccaaaccccccccaaaacccccccccccccaaaaacaaaccacacccccccccccccc",
    "abccccccccaaacaaacccccaaacccccccccccccaaaaaaajjjjjkkkcccccaacccccc",
    "abcccccaaaaaaaaaacccccaaccccccccccciiiiiijjjjjjjjjkkkcaaaaaacccccc",
    "abcccccaaaaaaaaacccccccccccccccccciiiiiiijjjjjjjrrkkkkaaaaaaaacccc",
    "abcccccccaaaaaccccccccccccccccccciiiiiiiijjjjrrrrrppkkkaaaaaaacccc",
    "abcccaaccaaaaaacccccccccccaacaaciiiiqqqqqrrrrrrrrpppkkkaaaaaaacccc",
    "abccaaaaaaaaaaaaccccacccccaaaaaciiiqqqqqqrrrrrruuppppkkaaaaacccccc",
    "abcccaaaaaaacaaaacaaacccccaaaaaahiiqqqqtttrrruuuuupppkkaaaaacccccc",
    "abcaaaaaaaccccaaaaaaacccccaaaaaahhqqqtttttuuuuuuuuuppkkkccaacccccc",
    "abcaaaaaaaaccccaaaaaacccccaaaaaahhqqqtttttuuuuxxuuuppkklcccccccccc",
    "abcaaaaaaaacaaaaaaaaaaacccccaaachhhqqtttxxxuuxxyyuuppllllccccccccc",
    "abcccaaacaccaaaaaaaaaaaccccccccchhhqqtttxxxxxxxyuupppplllccccccccc",
    "abaacaacccccaaaaaaaaaaaccccccccchhhqqtttxxxxxxyyvvvpppplllcccccccc",
    "abaacccccccccaaaaaaacccccccccccchhhpppttxxxxxyyyvvvvpqqqlllccccccc",
    "SbaaccccccaaaaaaaaaaccccccccccchhhppptttxxxEzzyyyyvvvqqqlllccccccc",
    "abaaaaccccaaaaaaaaacccccccccccchhhpppsssxxxyyyyyyyyvvvqqqlllcccccc",
    "abaaaacccccaaaaaaaacccccccccccgggpppsssxxyyyyyyyyyvvvvqqqlllcccccc",
    "abaaacccaaaacaaaaaaaccccccccccgggpppsswwwwwwyyyvvvvvvqqqllllcccccc",
    "abaaccccaaaacaaccaaaacccccccccgggppssswwwwwwyyywvvvvqqqqmmmccccccc",
    "abaaccccaaaacaaccaaaaccaaaccccggpppssssswwswwyywvqqqqqqmmmmccccccc",
    "abcccccccaaacccccaaacccaaacaccgggpppssssssswwwwwwrqqmmmmmccccccccc",
    "abcccccccccccccccccccaacaaaaacgggppooosssssrwwwwrrrmmmmmcccccccccc",
    "abcccccccccccccccccccaaaaaaaacggggoooooooorrrwwwrrnmmmdddccaaccccc",
    "abaccccccccccccaacccccaaaaaccccggggoooooooorrrrrrrnmmddddcaaaccccc",
    "abaccccccccaaaaaaccccccaaaaaccccggfffffooooorrrrrnnndddddaaaaccccc",
    "abaacccccccaaaaaacccccaaaaaacccccffffffffoonrrrrrnnndddaaaaaaacccc",
    "abaaccccccccaaaaaaaccacaaaacccccccccffffffonnnnnnnndddaaaaaaaacccc",
    "abccccccccccaaaaaaaaaaaaaaaccccccccccccfffennnnnnnddddccaaaccccccc",
    "abcccccccccaaaaaaacaaaaaaaaaacccccccccccffeennnnnedddccccaaccccccc",
    "abcccccccccaaaaaaccaaaaaaaaaaaccccccccccaeeeeeeeeeedcccccccccccccc",
    "abccccccccccccaaaccaaaaaaaaaaaccccccccccaaaeeeeeeeecccccccccccccaa",
    "abcccccccaaccccccccaaaaaaaacccccccccccccaaaceeeeecccccccccccccccaa",
    "abaaccaaaaaaccccccccaaaaaaaacccccccccccccaccccaaacccccccccccaaacaa",
    "abaaccaaaaacccccaaaaaaaaaaacccccccccccccccccccccacccccccccccaaaaaa",
    "abaccaaaaaaaaccaaaaaaaaaaaaaacccccccccccccccccccccccccccccccaaaaaa",
};
#endif


enum { fringe_max = sizeof(data) * sizeof(data) };


typedef enum Dir {
    Dir_none = 0,
    Dir_left  = 1 << 0,
    Dir_right = 1 << 1,
    Dir_up    = 1 << 2,
    Dir_down  = 1 << 3,
} Dir;

typedef struct Pt { U4 x, y; } Pt;


typedef struct Square {
    Pt             pt;
    Dir            move_dirs;
    struct Square *min_route_prev;
    U4             min_path_len;
    bool           is_hit;
    bool           in_fringe;
} Square;

typedef struct Map {
    char const *grid;
    Pt          size;
    Square    **fringe; // array stack
    U4          fringe_c;
} Map;

U4 idx2(U4 w, U4 x, U4 y)
{   return w*y + x;   }

U4 pt2i(U4 w, Pt pt)
{   return w*pt.y + pt.x;   }

Pt i2pt(U4 w, U4 i)
{   return (Pt){ i % w, i / w };   }

char grid_ch(Map const *map, U4 x, U4 y)
{   return map->grid[map->size.x*y + x];   }

char grid_h(Map const *map, U4 x, U4 y)
{
    char ch = map->grid[map->size.x*y + x];
    return (ch == 'S' ? 'a' :
            ch == 'E' ? 'z' :
            ch);
}

bool can_traverse_up(U4 to, U4 from) { return to <= from + 1; }
bool can_traverse_down(U4 to, U4 from) { return to >= from - 1; }


Dir  available_move_dirs(Map *map, Pt pt, bool (*cmp)(U4, U4))
{
    Dir result = Dir_none;

    char pt_h       = grid_h(map, pt.x, pt.y);
    bool is_limit_u = pt.y == 0;
    bool is_limit_d = pt.y == map->size.y-1;
    bool is_limit_l = pt.x == 0;
    bool is_limit_r = pt.x == map->size.x-1;

    if (! is_limit_l)
    {
        char l = grid_h(map, pt.x-1, pt.y);
        result |= cmp(l, pt_h) * Dir_left;
    }

    if (! is_limit_r)
    {
        char r = grid_h(map, pt.x+1, pt.y);
        result |= cmp(r, pt_h) * Dir_right;
    }

    if (! is_limit_u)
    {
        char u = grid_h(map, pt.x, pt.y-1);
        result |= cmp(u, pt_h) * Dir_up;
    }

    if (! is_limit_d)
    {
        char d = grid_h(map, pt.x, pt.y+1);
        result |= cmp(d, pt_h) * Dir_down;
    }


    return result;
}

void print_fringe(Map *map, Square *sqs)
{
    for (U4 i = 0; i < map->fringe_c; ++i)
    {
        Pt pt = map->fringe[i]->pt;
        printf("{%u,%u}, ", pt.x, pt.y);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}

void print_grid(Square *sqs, Map *map, Square *fringe)
{
    for (U4 y = 0; y < map->size.y; ++y)
    {
        for (U4 x = 0; x < map->size.x; ++x)
        {
            Pt pt = {x,y};
            U4 i = pt2i(map->size.x, pt);
            Square *sq = &sqs[i];
            printf(sq->in_fringe ? "%c%02u# " :
                   sq->is_hit    ? "%c%02u* " :
                   "%c... ", map->grid[i], sq->min_path_len);
        }
        printf("\n");
    }
}

// TODO: could binary search

Square **
find_sq(Map *map, Square *sq)
{
    Square **result = NULL;
    for (U4 i = 0; i < map->fringe_c; ++i)
    {
        if (map->fringe[i] == sq)
        {   result = &map->fringe[i]; break;   }
    }
    return result;
}

Square **
find_pos(Map *map, U4 len)
{
    Square **pos = map->fringe + map->fringe_c; // if set, everything after and including should be moved
    for (U4 i = 0; i < map->fringe_c; ++i)
    {
        if (len < map->fringe[i]->min_path_len)
        {   pos = &map->fringe[i]; break;   }
    }
    return pos;
}

Square *
pri_q_remove(Map *map, Square **sq)
{
    Square *result = *sq;

    U4 i         = sq - map->fringe;
    U4 move_size = sizeof(Square) * (--map->fringe_c - i);
    memmove(sq, sq+1, move_size);
    result->in_fringe = false;

    return result;
}

void
pri_q_add(Map *map, Square *to, Square *from)
{
    U4 path_len = from->min_path_len+1;
    if (path_len < to->min_path_len)
    {
        Square **existing = find_sq(map, to);
        if (existing)
        {   pri_q_remove(map, existing);   }

        Square **pos = find_pos(map, path_len);


        U4 i         = pos - map->fringe;
        U4 move_size = sizeof(Square) * (map->fringe_c++ - i);
        memmove(pos+1, pos, move_size);
        *pos = to;
        to->min_path_len   = path_len;
        to->min_route_prev = from;
        to->in_fringe      = true;
    }
}



/// from must be on fringe
void check_square(Map *map, Square *from, Square *to, Square *sqs)
{
    pri_q_add(map, to, from);

    /* if (! to->is_hit) */
    /* { */
    /*     /1* if (! to->in_fringe) *1/ */
    /*     { */
    /*         Square square = {0}; */
    /*         Square *top   = map->fringe_c ? map->fringe[map->fringe_c-1]: &square; */
    /*         printf("about to push {%u,%u} onto {%u,%u}\n", */
    /*                to->pt.x, to->pt.y, top->pt.x, top->pt.y); */
    /*         fflush(stdout); */
    /*         /1* map->fringe[map->fringe_c++] = to; *1/ */
    /*     } */
    /* } */

    /* if (from->min_path_len+1 < to->min_path_len) */
    /* { // update shortest path */
    /*     to->min_path_len  = from->min_path_len+1; */
    /*     to->min_route_prev = from; */
    /* } */
}

void init_map(Map *map, Square *sqs, char start_ch, Square **start, char end_ch, Square **end, bool (*cmp)(U4,U4))
{
    Square *sq = sqs;
    for (U4 y = 0; y < map->size.y; ++y)
    { // init move_dirs, start & end
        for (U4 x = 0; x < map->size.x; ++x)
        {
            Pt pt = {x,y};
            Square *sq = &sqs[pt2i(map->size.x, pt)];
            *sq = (Square){
                .pt            = {x, y},
                .move_dirs     = available_move_dirs(map, pt, cmp),
                .min_path_len = ~(U4)0,
            };
            if      (grid_ch(map, x, y)        == start_ch) { *start = sq; }
            else if (end && grid_ch(map, x, y) == end_ch)   { *end   = sq; }
        }
    }
}

U4 visit_pts(Map *map, Square *sqs)
{
    for (U4 c = 0; map->fringe_c; ++c)
    {
        Square *sq = map->fringe[0]; // highest priority
        Pt pt = i2pt(map->size.x, sq - sqs);
        printf("\nremoving {%u,%u}\n", pt.x,pt.y); fflush(stdout);
        sq->is_hit = true;
        /* print_fringe(map, sqs); */

        // add potential move dirs to fringe
        if (sq->move_dirs & Dir_left)
        {   Square *l_sq = sq-1;           check_square(map, sq, l_sq,sqs);   }
        if (sq->move_dirs & Dir_right)
        {   Square *r_sq = sq+1;           check_square(map, sq, r_sq,sqs);   }
        if (sq->move_dirs & Dir_up)
        {   Square *u_sq = sq-map->size.x; check_square(map, sq, u_sq,sqs);   }
        if (sq->move_dirs & Dir_down)
        {   Square *d_sq = sq+map->size.x; check_square(map, sq, d_sq,sqs);   }

        print_fringe(map, sqs);
        print_grid(sqs, map, sq);
        printf("\n");
        pri_q_remove(map, map->fringe);
    }
    printf("done\n");
    return 0;
}

void draw_path(Map *map, Square *end_sq)
{
    printf("%d\n", __LINE__); fflush(stdout);
    char *graph = calloc(1, map->size.x*map->size.y);
    printf("%d\n", __LINE__); fflush(stdout);
    for (Square const *sq = end_sq->min_route_prev, *sq_p = end_sq;
         sq; sq_p = sq, sq = sq->min_route_prev)
    { // generate final path
        char dir = '.';
        if (sq_p->pt.x < sq->pt.x)
        {   dir = '<';   }
        else if (sq_p->pt.x > sq->pt.x)
        {   dir = '>';   }
        else if (sq_p->pt.y > sq->pt.y)
        {   dir = 'v';   }
        else if (sq_p->pt.y < sq->pt.y)
        {   dir = '^';   }

        U4 i = pt2i(map->size.x, sq->pt);
        graph[i] = dir;
    }


    printf("%d\n", __LINE__); fflush(stdout);
    for (U4 y = 0; y < map->size.y; ++y)
    { // draw final path
        for (U4 x = 0; x < map->size.x; ++x)
        {
            U4 i = pt2i(map->size.x, (Pt){ x,y });
            (printf)("%c%s%c%s ", data[y][x],
                     graph[i] ? "\e[91m\e[1m" : "",
                     graph[i] ?: '.',
                     graph[i] ? "\e[0m" : ""
                     );
        }
        putc('\n', stdout);
    }
}

U4 aoc12(Map *map)
{
    U4 result = 0;

    map->grid   = data[0];
    map->fringe = malloc(sizeof(*map->fringe) * fringe_max);
    Square *sqs = malloc(sizeof(*sqs) * map->size.x * map->size.y);

    Square *sq     = NULL;
    Square *end_sq = NULL;
    init_map(map, sqs, 'S', &sq, 'E', &end_sq, can_traverse_up);

    // init fringe at start point
    sq->is_hit       = true;
    sq->min_path_len = 0;
    map->fringe[map->fringe_c++] = sq;

    printf("before\n"); fflush(stdout);
    visit_pts(map, sqs);
    printf("after\n"); fflush(stdout);

    draw_path(map, end_sq);



    printf("%d\n", __LINE__); fflush(stdout);
    (printf)("%u", end_sq->min_path_len);
    return end_sq->min_path_len;
}

int infinite_loop(int *a)
{
    int result = 0;
    for (;;)
    {
        ++*a;
    }
    return result;
}

U4 aoc12b(Map *map)
{
    U4 result = 0;

    /* map->grid   = data[0]; */
    map->fringe = malloc(sizeof(*map->fringe) * fringe_max);
    Square *sqs = malloc(sizeof(*sqs) * map->size.x * map->size.y);

    Square *sq = NULL;
    init_map(map, sqs, 'E', &sq, 0, NULL, can_traverse_down);

    // init fringe at start point
    sq->is_hit       = true;
    sq->min_path_len = 0;
    map->fringe[map->fringe_c++] = sq;

    printf("before\n"); fflush(stdout);
    visit_pts(map, sqs);
    printf("after\n"); fflush(stdout);

    printf("%d\n", __LINE__); fflush(stdout);
    char *graph = calloc(1, map->size.x*map->size.y);
    printf("%d\n", __LINE__); fflush(stdout);


    Square *end_sq = NULL;
    printf("%d\n", __LINE__); fflush(stdout);
    for (U4 y = 0; y < map->size.y; ++y)
    { // draw final path
        for (U4 x = 0; x < map->size.x; ++x)
        {
            U4 i = pt2i(map->size.x, (Pt){ x,y });
            if (map->grid[i] == 'a' &&
                (! end_sq ||
                 sqs[i].min_path_len < end_sq->min_path_len))
            {   end_sq = &sqs[i];   }
        }
    }

    /* int a = data[0][0]; */

    draw_path(map, end_sq);

    printf("%d\n", __LINE__); fflush(stdout);
    (printf)("%u", end_sq->min_path_len);
    return end_sq->min_path_len;
}

int main()
{
    Map map[] = {&data[0][0], { countof(data[0]), countof(data) } };
    puts("\n-----");
    aoc12b(map);
}
