#include "timesub.h"

long timeSubtract(long now, long beforetime)
{
    //系統時間
    long timeA[3];
    //中台時間
    long timeB[3];
    for (int i = 0; i < 3; i++) {
        timeA[i] = now % 100;
        timeB[i] = beforetime % 100;
        now = now / 100;
        beforetime = beforetime / 100;
    }
    long hour = (timeA[2] - timeB[2]) * 3600;
    long min = (timeA[1] - timeB[1]) * 60;
    long sec = (timeA[0] - timeB[0]);
    // printf("hour%ld , min%ld,sec%ld\n", hour, min, sec);
    return (hour + min + sec);
}

long miketime(char *now, char *beforetime)
{
    //printf("%s - %s\n", now, beforetime);
    int i = 0;
    long hour;
    long min;
    long sec;
    for (int i = 0; i < 6; i += 2) {
        // printf("now 小時= %c%c i=%d\n", *(now + i), *(now + i + 1), i);
        // printf("beforetime 小時= %c%c i=%d\n", *(beforetime + i),
        //       *(beforetime + i + 1), i);
               if (i == 0) {
                   hour = (*(now + i) - *(beforetime + i)) * 10 +
                          *(now + i + 1) - *(beforetime + i + 1);
                   // printf("%ld\n", hour);
               } else if (i == 2) {
                   min = (*(now + i) - *(beforetime + i)) * 10 +
                         *(now + i + 1) - *(beforetime + i + 1);
                   // printf("%ld\n", min*60);
               } else {
                   sec = (*(now + i) - *(beforetime + i)) * 10 +
                         *(now + i + 1) - *(beforetime + i + 1);
                   // printf("%ld\n", sec);
               }
    }
    return (hour * 3600 + min * 60 + sec);
}