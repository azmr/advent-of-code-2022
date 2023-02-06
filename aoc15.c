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


#if 0
char const *in[] = {
    "Sensor at x=2, y=18: closest beacon is at x=-2, y=15",
    "Sensor at x=9, y=16: closest beacon is at x=10, y=16",
    "Sensor at x=13, y=2: closest beacon is at x=15, y=3",
    "Sensor at x=12, y=14: closest beacon is at x=10, y=16",
    "Sensor at x=10, y=20: closest beacon is at x=10, y=16",
    "Sensor at x=14, y=17: closest beacon is at x=10, y=16",
    "Sensor at x=8, y=7: closest beacon is at x=2, y=10",
    "Sensor at x=2, y=0: closest beacon is at x=2, y=10",
    "Sensor at x=0, y=11: closest beacon is at x=2, y=10",
    "Sensor at x=20, y=14: closest beacon is at x=25, y=17",
    "Sensor at x=17, y=20: closest beacon is at x=21, y=22",
    "Sensor at x=16, y=7: closest beacon is at x=15, y=3",
    "Sensor at x=14, y=3: closest beacon is at x=15, y=3",
    "Sensor at x=20, y=1: closest beacon is at x=15, y=3",
};

#else
char const *in[] = {
    "Sensor at x=2765643, y=3042538: closest beacon is at x=2474133, y=3521072",
    "Sensor at x=2745662, y=2324735: closest beacon is at x=2491341, y=1883354",
    "Sensor at x=2015742, y=2904055: closest beacon is at x=2474133, y=3521072",
    "Sensor at x=3375262, y=3203288: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=3276468, y=3892409: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=952573, y=3147055: closest beacon is at x=-41010, y=2905006",
    "Sensor at x=1823659, y=1779343: closest beacon is at x=1592718, y=2000000",
    "Sensor at x=1156328, y=865741: closest beacon is at x=1592718, y=2000000",
    "Sensor at x=3938443, y=271482: closest beacon is at x=4081274, y=1177185",
    "Sensor at x=2815232, y=1641178: closest beacon is at x=2491341, y=1883354",
    "Sensor at x=3984799, y=3424711: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=1658825, y=3999931: closest beacon is at x=2474133, y=3521072",
    "Sensor at x=3199859, y=1285962: closest beacon is at x=4081274, y=1177185",
    "Sensor at x=3538649, y=2788193: closest beacon is at x=3725736, y=2414539",
    "Sensor at x=3522208, y=3336284: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=3093758, y=3492396: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=2464979, y=562119: closest beacon is at x=2491341, y=1883354",
    "Sensor at x=3665010, y=1556840: closest beacon is at x=3735739, y=2128164",
    "Sensor at x=207525, y=3893957: closest beacon is at x=-41010, y=2905006",
    "Sensor at x=3894678, y=1974599: closest beacon is at x=3735739, y=2128164",
    "Sensor at x=2185146, y=3822275: closest beacon is at x=2474133, y=3521072",
    "Sensor at x=31166, y=1467978: closest beacon is at x=-41010, y=2905006",
    "Sensor at x=3242364, y=3335961: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=3773718, y=3999789: closest beacon is at x=3321219, y=3415236",
    "Sensor at x=423046, y=2227938: closest beacon is at x=-41010, y=2905006",
    "Sensor at x=1600225, y=2529059: closest beacon is at x=1592718, y=2000000",
    "Sensor at x=3291752, y=2241389: closest beacon is at x=3735739, y=2128164",
    "Sensor at x=2741333, y=3984346: closest beacon is at x=2474133, y=3521072",
    "Sensor at x=3935288, y=2292902: closest beacon is at x=3725736, y=2414539",
    "Sensor at x=291635, y=140996: closest beacon is at x=212146, y=-1154950",
    "Sensor at x=3966296, y=2600346: closest beacon is at x=3725736, y=2414539",
    "Sensor at x=2228916, y=1461096: closest beacon is at x=2491341, y=1883354",
};
#endif

#ifdef assert
#undef assert
#endif
#define assert(x, ...) ((x) ? 1 : \
                   (fprintf(stderr, "break at line %d, %s, failed:\n    "#x"\n", __LINE__, __func__), \
                    fprintf(stderr, "" __VA_ARGS__),\
                    fflush(stderr), __debugbreak(), 0))


typedef struct Pt { S8 x, y; } Pt;


bool pt_eq(Pt a, Pt b) { return a.x == b.x && a.y == b.y; }

typedef struct Sensor {
    Pt pt;
    U4 beacon_dist; // manhattan distance
} Sensor;

typedef struct Map {
    Pt max_pt, min_pt;

    Sensor sensors[countof(in)];
    Pt     beacons[countof(in)]; // parallel
} Map;

inline S8 abs_diff(S8 a, S8 b)
{
    S8 result = a - b;
    if (result < 0)
    {   result *= -1;   }
    return result;
}

inline U8
manhattan_dist(Pt a, Pt b)
{   return abs_diff(a.x, b.x) + abs_diff(a.y, b.y);   }

int is_pt_beacon(Map *map, Pt pt) {
    bool is_beacon = false;
    for (U4 beacon_i = 0; beacon_i < countof(map->beacons); ++beacon_i)
    {
        if (pt_eq(map->beacons[beacon_i], pt))
        {   is_beacon = true; break;   }
    }
    return is_beacon;
}


Sensor *
find_sensor_for_pt(Map *map, Pt pt, U8 *dist_out)
{
    Sensor *result = NULL;
    for (U4 sensor_i = 0; sensor_i < countof(map->sensors); ++sensor_i)
    {
        Sensor *sensor = &map->sensors[sensor_i];
        U8      dist   = manhattan_dist(sensor->pt, pt);

        if (dist <= sensor->beacon_dist) // point is covered by sensor
        {
            *dist_out = dist;
            result    = sensor;
            break;
        }
    }
    return result;
}

int is_sensed(Map *map, Pt pt)
{
    U8 dist_dummy;
    return !!find_sensor_for_pt(map, pt, &dist_dummy);
}

U8
aoc15(S8 check_y)
{
    Map map[1] = {0};

    for (U4 i = 0; i < countof(in); ++i)
    {
        char const *str    = in[i];
        Sensor     *sensor = &map->sensors[i];
        Pt         *beacon = &map->beacons[i];

        // get sensor & beacon locations
        int nums_found = sscanf(
            str,
            "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld",
            &sensor->pt.x, &sensor->pt.y, &beacon->x, &beacon->y);
        assert(nums_found == 4);

        // get manhattan distance from sensor to beacon
        sensor->beacon_dist = manhattan_dist(sensor->pt, *beacon);

        // expand maximum extent
        Pt min_extent = { sensor->pt.x - sensor->beacon_dist, sensor->pt.y - sensor->beacon_dist,  };
        Pt max_extent = { sensor->pt.x + sensor->beacon_dist, sensor->pt.y + sensor->beacon_dist,  };

        if (i == 0 || min_extent.x < map->min_pt.x)
        {   map->min_pt.x = min_extent.x;   }
        if (i == 0 || min_extent.y < map->min_pt.y)
        {   map->min_pt.y = min_extent.y;   }
        if (i == 0 || max_extent.x > map->max_pt.x)
        {   map->max_pt.x = max_extent.x;   }
        if (i == 0 || max_extent.y > map->max_pt.y)
        {   map->max_pt.y = max_extent.y;   }
    }

    U8 result = 0;
    for (Pt pt = { map->min_pt.x, check_y };
         pt.x <= map->max_pt.x;
         ++pt.x)
    {
        if (is_pt_beacon(map, pt))
        {   continue;   } // doesn't matter if covered by sensor

        result += is_sensed(map, pt);
    }


    return result;
}

U8
aoc15b(S4 search_size)
{
    Map map[1] = {0};

    for (U4 i = 0; i < countof(in); ++i)
    {
        char const *str    = in[i];
        Sensor     *sensor = &map->sensors[i];
        Pt         *beacon = &map->beacons[i];

        // get sensor & beacon locations
        int nums_found = sscanf(
            str,
            "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld",
            &sensor->pt.x, &sensor->pt.y, &beacon->x, &beacon->y);
        assert(nums_found == 4);

        // get manhattan distance from sensor to beacon
        sensor->beacon_dist = manhattan_dist(sensor->pt, *beacon);

        // expand maximum extent
        Pt min_extent = { sensor->pt.x - sensor->beacon_dist, sensor->pt.y - sensor->beacon_dist,  };
        Pt max_extent = { sensor->pt.x + sensor->beacon_dist, sensor->pt.y + sensor->beacon_dist,  };

        if (i == 0 || min_extent.x < map->min_pt.x)
        {   map->min_pt.x = min_extent.x;   }
        if (i == 0 || min_extent.y < map->min_pt.y)
        {   map->min_pt.y = min_extent.y;   }
        if (i == 0 || max_extent.x > map->max_pt.x)
        {   map->max_pt.x = max_extent.x;   }
        if (i == 0 || max_extent.y > map->max_pt.y)
        {   map->max_pt.y = max_extent.y;   }
    }

    bool space_found = false;
    Pt pt = {0};
    for (; pt.y <= search_size; ++pt.y)
    {
        for (pt.x = 0; pt.x <= search_size;)
        {
            U8      dist   = 0;
            Sensor *sensor = find_sensor_for_pt(map, pt, &dist);

            if (! sensor)
            {   space_found = true; goto hard_break;   }

            // skip the rest of x seen at this y by this sensor (accounting for diagonal)
            S8 max_sensor_x = (sensor->pt.x + sensor->beacon_dist -
                               abs_diff(pt.y, sensor->pt.y));
            pt.x = max_sensor_x + 1;
        }
    }


    assert(space_found);
hard_break:
    ;
    // calculate "frequency" from position
    U8 result = pt.x * 4000000 + pt.y;



    return result;
}

//    1                   1    1    2    2
//    0    5    0    5    0    5    0    5
// -2 ..................#.................
// -1 .................###................
//  0 ............S...#####...............
//  1 ...............#######........S.....
//  2 ..............#########S............
//  3 .............###########SB..........
//  4 ............#############...........
//  5 ...........###############..........
//  6 ..........#################.........
//  7 .........#########S#######S#........
//  8 ..........#################.........
//  9 ...........###############..........
// 10 ..V.....####B#########X##...........
// 11 ..........S..########XXXR...........
// 12 ..............######XXXXX...........
// 13 ...............####XXXXXXX..........
// 14 ................##XXXXSXXXX...S.....
// 15 ........B........##XXXXXXX..........
// 16 ..................#SBXXXX...........
// 17 .....................XXXS..........B
// 18 ............S.........X.............
// 19 ....................................
// 20 ....................S......S........
// 21 ....................................
// 22 ...............................B....
