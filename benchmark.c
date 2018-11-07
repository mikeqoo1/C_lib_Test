#include "csplit.h"
#include "timesub.h"
#include "zlog.h"
#include <stdio.h>
#include <uv.h>

#ifndef RUN_CNT
#define RUN_CNT (uint64_t)1000000
#endif
uint64_t start, end, diff, per;
int rc;
zlog_category_t *logger;

int main(int argc, char **argv)
{
    rc = zlog_init("zlogconfig.conf");
    logger = zlog_get_category("my_dog");
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
    zlog_debug(logger, "strsplit => %llu run: %llu[ns] (%llu ns/op)", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        timeSubtract(atol(now), asd);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    zlog_debug(logger, "timeSubtract => %llu run: %llu[ns] (%llu ns/op)", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        miketime(now, qwe);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    zlog_debug(logger, "miketime => %llu run: %llu[ns] (%llu ns/op)", RUN_CNT, diff, per);

    start = uv_hrtime();
    for (iii = 0; iii < 1000000; iii++)
        miketime2(now, qwe);
    end = uv_hrtime();
    diff = end - start;
    per = diff / RUN_CNT;
    zlog_debug(logger, "miketime2 => %llu run: %llu[ns] (%llu ns/op)", RUN_CNT, diff, per);
    return 0;
}