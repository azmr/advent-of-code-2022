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
typedef int64_t  S8;
typedef uint64_t U8;
#define countof(a) (sizeof(a)/sizeof(*(a)))


#if 1
char *type = "test";

char const *in[] = {
    "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB",
    "Valve BB has flow rate=13; tunnels lead to valves CC, AA",
    "Valve CC has flow rate=2; tunnels lead to valves DD, BB",
    "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE",
    "Valve EE has flow rate=3; tunnels lead to valves FF, DD",
    "Valve FF has flow rate=0; tunnels lead to valves EE, GG",
    "Valve GG has flow rate=0; tunnels lead to valves FF, HH",
    "Valve HH has flow rate=22; tunnel leads to valve GG",
    "Valve II has flow rate=0; tunnels lead to valves AA, JJ",
    "Valve JJ has flow rate=21; tunnel leads to valve II",
};

#else
char *type = "real";
char const *in[] = {
    "Valve ED has flow rate=0; tunnels lead to valves PS, AW",
    "Valve SI has flow rate=0; tunnels lead to valves AA, HX",
    "Valve LX has flow rate=22; tunnels lead to valves DY, YH",
    "Valve CR has flow rate=0; tunnels lead to valves BE, HX",
    "Valve BI has flow rate=0; tunnels lead to valves GC, AY",
    "Valve PB has flow rate=4; tunnels lead to valves IX, YG, RI, KR, BV",
    "Valve YY has flow rate=0; tunnels lead to valves PH, GJ",
    "Valve PH has flow rate=11; tunnels lead to valves YY, VE, ZG, MM",
    "Valve DY has flow rate=0; tunnels lead to valves LX, AW",
    "Valve SD has flow rate=0; tunnels lead to valves AY, EC",
    "Valve SV has flow rate=24; tunnels lead to valves CC, GF",
    "Valve RL has flow rate=0; tunnels lead to valves OW, IN",
    "Valve GF has flow rate=0; tunnels lead to valves RQ, SV",
    "Valve BE has flow rate=5; tunnels lead to valves CR, JC, MF, IT",
    "Valve PR has flow rate=0; tunnels lead to valves BV, GJ",
    "Valve AW has flow rate=21; tunnels lead to valves VE, DY, TR, ED",
    "Valve FY has flow rate=17; tunnels lead to valves GG, KJ",
    "Valve GC has flow rate=0; tunnels lead to valves BI, GJ",
    "Valve RI has flow rate=0; tunnels lead to valves PB, AY",
    "Valve RQ has flow rate=0; tunnels lead to valves HH, GF",
    "Valve IT has flow rate=0; tunnels lead to valves MZ, BE",
    "Valve XG has flow rate=0; tunnels lead to valves BL, AA",
    "Valve MK has flow rate=0; tunnels lead to valves HX, DV",
    "Valve IX has flow rate=0; tunnels lead to valves PB, JC",
    "Valve BV has flow rate=0; tunnels lead to valves PR, PB",
    "Valve TR has flow rate=0; tunnels lead to valves CD, AW",
    "Valve PS has flow rate=0; tunnels lead to valves ED, AY",
    "Valve HH has flow rate=12; tunnels lead to valves RQ, NL, ZQ",
    "Valve AA has flow rate=0; tunnels lead to valves KR, SI, XG, EC, ZG",
    "Valve FT has flow rate=0; tunnels lead to valves IN, YH",
    "Valve YG has flow rate=0; tunnels lead to valves PB, HX",
    "Valve HX has flow rate=14; tunnels lead to valves MK, ZQ, YG, SI, CR",
    "Valve DV has flow rate=0; tunnels lead to valves MK, QR",
    "Valve GJ has flow rate=3; tunnels lead to valves PR, CD, YY, GC, BL",
    "Valve BL has flow rate=0; tunnels lead to valves GJ, XG",
    "Valve CD has flow rate=0; tunnels lead to valves TR, GJ",
    "Valve GG has flow rate=0; tunnels lead to valves FY, NL",
    "Valve JC has flow rate=0; tunnels lead to valves IX, BE",
    "Valve JN has flow rate=0; tunnels lead to valves OW, QR",
    "Valve RM has flow rate=18; tunnel leads to valve KJ",
    "Valve NL has flow rate=0; tunnels lead to valves GG, HH",
    "Valve QR has flow rate=20; tunnels lead to valves CC, DV, PN, JN",
    "Valve ZG has flow rate=0; tunnels lead to valves AA, PH",
    "Valve AY has flow rate=6; tunnels lead to valves RI, PS, SD, BI, MM",
    "Valve VE has flow rate=0; tunnels lead to valves PH, AW",
    "Valve OW has flow rate=25; tunnels lead to valves MZ, RL, JN",
    "Valve MM has flow rate=0; tunnels lead to valves AY, PH",
    "Valve KJ has flow rate=0; tunnels lead to valves RM, FY",
    "Valve MF has flow rate=0; tunnels lead to valves BE, PN",
    "Valve YH has flow rate=0; tunnels lead to valves LX, FT",
    "Valve ZQ has flow rate=0; tunnels lead to valves HX, HH",
    "Valve KR has flow rate=0; tunnels lead to valves AA, PB",
    "Valve PN has flow rate=0; tunnels lead to valves MF, QR",
    "Valve CC has flow rate=0; tunnels lead to valves SV, QR",
    "Valve MZ has flow rate=0; tunnels lead to valves OW, IT",
    "Valve EC has flow rate=0; tunnels lead to valves SD, AA",
    "Valve IN has flow rate=16; tunnels lead to valves RL, FT",
};
#endif

#ifdef assert
#undef assert
#endif
#define assert(x, ...) ((x) ? 1 : \
                   (fprintf(stderr, "break at line %d, %s, failed:\n    "#x"\n", __LINE__, __func__), \
                    fprintf(stderr, "    " __VA_ARGS__),\
                    fflush(stderr), __debugbreak(), 0))

struct Valve_;

typedef struct Tunnel_ {
    U4             travel_time;
    struct Valve_  *to;
    struct Tunnel_ *next,
                   *twin; // bidirectional in other direction
} Tunnel;

typedef struct Valve_ {
    U4      flow, open_time; // NOTE: open_time is AFTER open, which takes 1 min
    char    id[3];
    bool    is_open;
    Tunnel *first_tunnel, *last_tunnel;
} Valve;

typedef struct Map {
    Valve *valves;
    U4     valves_n;
} Map;

void
append_valve_tunnel(Valve *v, Tunnel *t)
{ // singly-linked list append
    if (v->last_tunnel)
    {   v->last_tunnel->next = t;   }
    else
    {   v->first_tunnel = t;   }
    v->last_tunnel = t;
}

Tunnel *
create_valve_tunnel(Valve *from, Valve *to, U4 travel_time)
{
    Tunnel *tunnel = malloc(sizeof(Tunnel));
    *tunnel = (Tunnel){ travel_time, to };
    append_valve_tunnel(from, tunnel);

    for (Tunnel *t = to->first_tunnel; t; t = t->next)
    {
        if (t->to == from &&
            (! t->twin || t->twin->to == from))
        {
            assert(! t->twin,
                   "tunnel %p from %s to %s already has twin to %s!\n", t, to->id, from->id, t->twin->to->id);
            assert(! tunnel->twin);
            t->twin      = tunnel;
            tunnel->twin = t;
        }
    }

    return tunnel;
}

void
graph_rooms(Map *map)
{
    static U4 dot_id = 0;
    FILE *dot = fopen("aoc16.dot", "wb"); assert(dot);

    fprintf(dot, "digraph valves {\n");
    for (U4 i = 0; i < map->valves_n; ++i)
    {
        Valve *v = &map->valves[i];
        fprintf(dot, (v->open_time
                      ? "  \"%s (%u * %u = %u)\"\n"
                      : "  \"%s (%u)\"\n"),
                v->id, v->flow, v->open_time, v->flow * v->open_time);

        for (Tunnel *t = v->first_tunnel; t; t = t->next)
        {
            if ((U8)t > (U8)t->twin)
            {
                fprintf(dot, "  \"%s (%u)\" %s-> \"%s (%u)\" [label=\"%u\"]\n",
                        v->id, v->flow,
                        t->twin ? "<" : "",
                        t->to->id, t->to->flow,
                        t->travel_time);
            }
        }
    }

    fprintf(dot, "}");
    fclose(dot);

    char call[256] = {0};
    snprintf(call, sizeof(call), "dot -Tsvg -oaoc16-%s-%u.svg aoc16.dot", type, dot_id);
    system(call);
    ++dot_id;
}

void
move_room(Valve **v, Valve *to, U4 *time_remaining)
{
    bool can_move = false;
    for (Tunnel *t = v[0]->first_tunnel; t; t = t->next)
    {
        if (t->to == to)
        {   can_move = true; break;   }
    }
    assert(can_move);

    *v = to;
    if (to)
    {
        --time_remaining;
    }
}

void
remove_tunnel(Tunnel **pre, Valve *v, Tunnel *removee)
{
    *pre = removee->next;

    if (v->last_tunnel == removee->next)
    {   v->last_tunnel = removee;   }

    removee->next = NULL;
}

void
consolidate_path(Valve *v, bool keep_out_tunnel)
{
    // A <2> B <1> D
    // ^
    // 1
    // v
    // C
    //
    // consolidating A
    //
    // B  3> C
    // B <3> C

    U4 i = 0;
    for (Tunnel *t1 = v->first_tunnel; t1; t1 = t1->next)
    {
        Valve *v1 = t1->to;

        for (Tunnel *t2 = v->first_tunnel; t2; t2 = t2->next)
        { // add combined tunnels skipping v if there isn't a shorter 1
            if (t1 == t2) continue;

            Valve *v2 = t2->to;
            U4 travel_time = t1->travel_time + t2->travel_time;

            bool add_tunnel = true;
            for (Tunnel  *t3  = v1->first_tunnel,
                        **pre = &v1->first_tunnel;
                          t3;
                          pre = &t3->next,
                          t3  = t3->next)
            { // check if there's no better path
                if (t3->to == v2)                      // B already has tunnel to C
                {                                      // is new route better?
                    if (travel_time < t3->travel_time) // better => replace
                    {
                        assert(! "faster tunnel");
                        /* remove_tunnel(pre, v1, t2); */
                        break;
                    }
                    else                               // worse => keep
                    {   add_tunnel = false; break;   }
                }
            }

            if (add_tunnel)
            {   create_valve_tunnel(v1, v2, travel_time);   }
        }

        bool removed = false;
        for (Tunnel  *t2  = v1->first_tunnel,
                    **pre = &v1->first_tunnel;
                      t2;
                      pre = &t2->next,
                      t2  = t2->next)

        { // remove tunnel to v
            if (t2->to == v)
            {   remove_tunnel(pre, v1, t2);   }
        }

    }

    /* if (! keep_out_tunnel) */
    {   v->first_tunnel = NULL;   } // Leak
}

void
open_valve(Valve *v, U4 *time_remaining)
{
    assert(! v->is_open);
    v->is_open = true;
    consolidate_path(v, 0);
    v->open_time = --(time_remaining[0]);
}


void
init(char const **valve_strs, Map *map)
{
    for (U4 i = 0; i < map->valves_n; ++i)
    { // init valves
        int matches_n = sscanf(valve_strs[i], "Valve %s has flow rate=%u;",
                               map->valves[i].id, &map->valves[i].flow);
        assert(matches_n == 2);
    }

    for (U4 i = 0; i < map->valves_n; ++i)
    { // init tunnels
        char  tunnel_ids[8][3] = {0};
        int matches_n = sscanf(valve_strs[i], "Valve %s has flow rate=%u; tunn%*s lea%*s to valv%*s %[A-Z], %[A-Z], %[A-Z], %[A-Z], %[A-Z], %[A-Z], %[A-Z], %[A-Z]",
                               map->valves[i].id, &map->valves[i].flow,
                               tunnel_ids[0], tunnel_ids[1], tunnel_ids[2], tunnel_ids[3],
                               tunnel_ids[4], tunnel_ids[5], tunnel_ids[6], tunnel_ids[7]);
        assert(matches_n >= 3);
        int tunnels_n = matches_n - 2;
        Valve *valve_from = &map->valves[i];


        for (int tunnel_i = 0; tunnel_i < tunnels_n; ++tunnel_i)
        {
            Tunnel *tunnel = NULL;
            for (U4 valve_i = 0; valve_i < map->valves_n; ++valve_i)
            {
                Valve *valve_to = &map->valves[valve_i];
                if (valve_to->id[0] == tunnel_ids[tunnel_i][0] &&
                    valve_to->id[1] == tunnel_ids[tunnel_i][1])
                {
                    tunnel = create_valve_tunnel(valve_from, valve_to, 1);
                    break; // found
                }
            }
            assert(tunnel);
        }
    }

    graph_rooms(map);

    // NOTE: don't remove our start position
    for (U4 i = 0; i < map->valves_n; ++i)
    { // elide 0-flow valves
        if (map->valves[i].flow == 0)
        {   consolidate_path(&map->valves[i], i == 0);   }
    }
}

U4
aoc16()
{
    Valve valves[countof(in)] = {0};
    Map map[1] = { valves, countof(valves) };

    init(in, map);
    graph_rooms(map);

    U4 time_remaining = 30;
    open_valve(&valves[1], &time_remaining);

    graph_rooms(map);

    return 0;
}
