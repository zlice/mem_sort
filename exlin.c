/*

GPLv2 :  http://fsf.org/
Author:  zlice

Compile: gcc -Os -o exlin exlin.c -ffunction-sectoins -fdata-sections
         gcc -m32 -Os -o exlin exlin.c -ffunction-sectoins -fdata-sections

Use:     ./exlin > file   (dumps output into a file, easier for large sorts)

What:    Number sorter

Main limitation is memory
Uses lo-hi for "expanding"

This is easy to segfault, but will sort numbers in seconds
A large difference in numbers has a big impact

e.g.
A million 1's will use less memory than 1 and 1 billion
e.g.
Giving a list with 0 and 9trillion (high range 64bit number)
will cause it to try to use more memory than possible

Code overview:
1. Allocate memory for sort[] (input)
2. Create input (RNG, list, count 0-size)
3. Find high and low values in sort[]
4. Size and allocate goal[] (range to sort output - also dupes[] for duplicate numbers)
5. Place sort[cnt] to goal[ sort[cnt] - lo], increase dupes[]
6. Loop through dupes[] and place goal[] to sort[]
7. Print output and free() memory

*/

#include <stdio.h>  //printf
#include <stdlib.h> //malloc
#include <string.h> //memset
#include <time.h>   //timing

//#define SORT_SZ sizeof(sort) / sizeof(long long)
#define SORT_SZ 1000000

clock_t t;
double time_taken;

void set_timer(){
    t = clock();
}

void timer(){
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("took %f seconds to ", time_taken);
    t = clock() - t;
}

int main(){
    unsigned long long GOAL_SZ, cntDupe = 0, cntGoal = 0, cnt = 0;
    long long lo = 0, hi = 0, *goal, *sort;

    sort = malloc(SORT_SZ * sizeof(long long) );

    srand( time(NULL) );
    long long r = rand();

    for(cnt = 0; cnt < SORT_SZ; cnt++){
        srand(r);
        r = rand();          //does't gen negatives
        sort[cnt] = r / 100; //memory constraints
        //sort[cnt] = cnt;   //straight 0---
    }//fake gen - 2mil bombs out on stack

    set_timer();

    for(cnt = 0; cnt < SORT_SZ; cnt++) {
        if( sort[cnt] > hi )
            hi = sort[cnt];
        else if( sort[cnt] < lo )
            lo = sort[cnt];
    }

    GOAL_SZ = hi - lo + 1; //can allocate way more than needed, [2] with 0 and 9tril ... x-x

    goal = malloc(GOAL_SZ * sizeof(long long) );
    memset(goal, 0x0, GOAL_SZ * sizeof(long long) );
    short *dupes = malloc(GOAL_SZ * sizeof(short) );
    //^ times_duped - could make int/short? 4bil dupes unlikely
    memset(dupes, 0x0, GOAL_SZ * sizeof(short) );
    //^ takes more time to malloc than 'sort', especially with 2x size
    //  not as much as printing though

    printf("SORT_SZ = %lld\nGOAL_SZ = %llu\n\thi = %lld\n\tlo = %lld\n", SORT_SZ, GOAL_SZ, hi, lo);
    printf("%llu total bytes for goal\n", GOAL_SZ * sizeof(long long) );

    timer();
    printf("malloc\n\"expanding\" numbers into goal\n");

    for(cnt = 0; cnt < SORT_SZ; cnt++) {
        dupes[ sort[cnt] - lo ] += 1;       //tells later loop to use this value x times
        goal[ sort[cnt] - lo ] = sort[cnt];
    }

    printf("\"compressing\" into sort\n");

    cnt = 0; //reset, place in sort[cnt]
    for(cntGoal = 0; cntGoal < GOAL_SZ; cntGoal++)
        for(cntDupe = 0; cntDupe < dupes[cntGoal]; cntDupe++)
            sort[cnt++] = goal[cntGoal];

    timer(); printf("sort\nprinting sort\n");

    //this prints over info, best to dump to file
    //7.6MB for 1mil straight sort
    for(cnt = 0; cnt < SORT_SZ; cnt++)
        printf("%lld, ", sort[cnt] );

    timer(); printf("display\n");

    free(goal);
    free(dupes);
    free(sort);

    return 0;

}

