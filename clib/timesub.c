#include "timesub.h"

long timeSubtract(long now, long beforetime)
{
    int i = 0;
    //系統時間
    long timeA[3];
    //中台時間
    long timeB[3];
    for (i = 0; i < 3; i++) {
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
    // printf("%s - %s\n", now, beforetime);
    //int i = 0;
    long hour;
    long min;
    long sec;
    // printf("now 小時= %c%c i=%d\n", *(now + i), *(now + i + 1), i);
    // printf("beforetime 小時= %c%c i=%d\n", *(beforetime + i),
    //       *(beforetime + i + 1), i);
    hour = (*(now + 0) - *(beforetime + 0)) * 10 + *(now + 1) - *(beforetime + 1);
    // printf("%ld\n", hour);
    min = (*(now + 2) - *(beforetime + 2)) * 10 + *(now + 3) - *(beforetime + 3);
    // printf("%ld\n", min*60);
    sec = (*(now + 4) - *(beforetime + 4)) * 10 + *(now + 5) - *(beforetime + 5);
    // printf("%ld\n", sec);
    return (hour * 3600 + min * 60 + sec);
}

long miketime2(char *now, char *beforetime)
{
    long hh = (now[0] - beforetime[0]) * 10 + (now[1] - beforetime[1]);
    long mm = (now[2] - beforetime[2]) * 10 + (now[3] - beforetime[3]);
    long ss = (now[4] - beforetime[4]) * 10 + (now[5] - beforetime[5]);
    return hh * 3600L + mm * 60L + ss;
}