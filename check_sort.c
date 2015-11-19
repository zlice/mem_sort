/*
GPLv2 :  http://fsf.org/
Author:  zlice

Checks a list to see if it is in order from lowest to highest

*/

#include <stdio.h>

#define SORT_SZ sizeof(sort) / sizeof(long long)

int main(){

    long long sort[] = {

    -38585, -31956, -31865, -27508, -26193, -23905, -15051, -14572, -12986, -12967, -10875, -9095, -6959, -3741, -1085, 247, 800, 1256, 3753, 4644, 7011, 8678, 9712, 10570, 11664, 12102, 12446, 13317, 14883, 15806, 16885, 18354, 18513, 20375, 20764, 21514, 21517, 21571, 21607, 22100, 22295, 23662, 25458, 25641, 26573, 28143, 29594, 30559, 30932, 32069, 32185, 32807, 34827, 34949, 35129, 35383, 36221, 41068, 41565, 53893,

    };

    long long cnt = 0;

    while(cnt < (SORT_SZ -1) && sort[cnt] <= sort[cnt+1])
        cnt++;

    printf("made it to %d of %d - value = %d\n", cnt, SORT_SZ - 1, sort[cnt]);

}

