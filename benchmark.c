#include "csplit.h"
#include "timesub.h"
#include "log.h"
#include <stdio.h>
#include <uv.h>

#ifndef RUN_CNT
#define RUN_CNT (uint64_t)1000000
#endif
uint64_t start, end, diff, per;

int main(int argc, char **argv)
{
    int ok;
    ok = log_init();
    if (ok == 0) {
        logger = getLogger(2);
    } else {
        printf("取得log指標失敗\n");
        return 0;
    }
    char testdata[] = "恭喜\r\n發財！！";
    char *now = "095604";
    long asd = 95550L;
    char *qwe = "095550";

    int iii = 0;
    char *anstesttt[16];
    for (iii = 0; iii < 16; iii++) {
        anstesttt[iii] = (char *)malloc(128);
    }

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        strsplit(testdata, anstesttt, "\r\n");
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    LOG_DEBUG(logger, "strsplit => %llu run: %llu[ns] (%llu ns/op)\033[0m", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        timeSubtract(atol(now), asd);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    LOG_DEBUG(logger, "timeSubtract => %llu run: %llu[ns] (%llu ns/op)\033[0m", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        miketime(now, qwe);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    LOG_DEBUG(logger, "miketime => %llu run: %llu[ns] (%llu ns/op)\033[0m", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        miketime2(now, qwe);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    LOG_DEBUG(logger, "miketime2 => %llu run: %llu[ns] (%llu ns/op)\033[0m", RUN_CNT, diff, per);
    return 0;
}