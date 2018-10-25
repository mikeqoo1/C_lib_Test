#include "cmap.h"
#include "csplit.h"
#include "zlog.h"
#include "timesub.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <google/cmockery.h>
#include <stdio.h>

int rc;
zlog_category_t *logger;
void test_cmap(void **state)
{
    logger = zlog_get_category("my_test");
    intptr_t value;
    zlog_debug(logger, "開始測試cmap");
    if (hcreate(50) == 0) store("black", "黑色");
    if (fetch("black", &value)) assert_string_equal((char *)value, "黑色");
    delete ("black");
    assert_string_equal((char *)value, "");
    zlog_debug(logger, "結束測試cmap");
}

void test_csplit(void **state)
{
    logger = zlog_get_category("my_test");
    zlog_debug(logger, "開始測試csplit");
    int i_csp = 0;
    //尾端剩餘
    char str[] = "A\r\nB\r\nC\r\nD\r\nE\r\nF\r\nG "
                 "AND ";
    //正常
    char str2[] = "g\r\nI\r\nJ\r\nK\r\nL\r\nM\r\nN\r\n";
    //單一剩餘的情況
    char str3[] = "Kobe";
    char str4[] = " Bryant\r\n";
    //增加複雜的case
    char str5[] =
        "告五人 Accusefive.《 披星戴月的想你 》\r\n突如其來的美夢\r\n是你離去時卷起的泡沫";
    char str6[] = "A\r\n踢著石頭 默默的走\r\n公車從旁擦身而過\r\n突如其來的念頭\r\n";
    char str7[] = "幻想化成流星的你我 ";
    char str8[] = "明亮的夜 漆黑的宇宙";
    char str9[] = "通通來自夜空\r\n 我會披星戴月的想你 我會奮不顧身的前進";
    char str10[] = "遠方煙火越來越唏噓 凝視前方身後的距離\r\n";
    char *ans[16], *ans2[16], *ans3[16], *ans4[16], *ans5[16];
    for (i_csp = 0; i_csp < 16; i_csp++) {
        ans[i_csp] = (char *)malloc(128);
        ans2[i_csp] = (char *)malloc(128);
        ans3[i_csp] = (char *)malloc(128);
        ans4[i_csp] = (char *)malloc(128);
        ans5[i_csp] = (char *)malloc(1024);
    }
    strsplit(str, ans, "\r\n");
    strsplit(str2, ans2, "\r\n");
    strsplit(str3, ans3, "\r\n");
    strsplit(str4, ans4, "\r\n");
    assert_string_equal(ans[0], "A");
    assert_string_equal(ans2[0], "G AND g");
    assert_string_equal(ans3[0], "Kobe");
    assert_string_equal(ans4[0], "Kobe Bryant");
    zlog_debug(logger, "結束測試csplit");
    int q = 0;
    int sss = 0;
    sss = strsplit(str5, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("1.<%s>>\n", ans5[q]);
    }
    sss = strsplit(str6, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("2.<%s>>\n", ans5[q]);
    }
    sss = strsplit(str7, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("3.<%s>>\n", ans5[q]);
    }
    sss = strsplit(str8, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("4.<%s>>\n", ans5[q]);
    }
    sss = strsplit(str9, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("5.<%s>>\n", ans5[q]);
    }
    sss = strsplit(str10, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("6.<%s>>\n", ans5[q]);
    }
}

void test_time(void **state)
{
    logger = zlog_get_category("my_test");
    zlog_debug(logger, "開始測試miketime");
    char *now = "095604";
    char *qwe = "095550";
    long A = 0L;
    A = miketime(now, qwe);
    assert_int_equal(A, 14);
    zlog_debug(logger, "結束測試miketime");

    zlog_debug(logger, "開始測試timeSubtract");
    A = timeSubtract(atol(now), atol(qwe));
    assert_int_equal(A, 14);
    zlog_debug(logger, "結束測試timeSubtract");

    zlog_debug(logger, "開始測試miketime2");
    A = miketime2(now, qwe);
    assert_int_equal(A, 14);
    zlog_debug(logger, "結束測試miketime2");
}

int main(int argc, char *argv[])
{
    rc = zlog_init("zlogconfig.conf");
    logger = zlog_get_category("my_test");
    const UnitTest tests[] = {
        unit_test(test_cmap),
        unit_test(test_csplit),
        unit_test(test_time),
    };
    return run_tests(tests);
}

/*
        通過expect_value和check_expected可以判斷傳入函式的值是不是期望的值，
        而will_return和mock則是對應的關係，will_return會將值放入到queue中，
        而每次用mock都會取到queue前端的值。
*/