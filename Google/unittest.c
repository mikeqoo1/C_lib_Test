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
    char str5[] = "Passenger | Let Her Go\r\nWell you only need the light when it's burning "
                  "low\r\nOnly miss the ";
    char str6[] = "sun when it starts to snow\r\nOnly know you ";
    char str7[] = "love her when ";
    char str8[] = "you let her go\r\n";
    char str9[] = "Only know you've been high when you're feeling low\r\nOnly hate the road when you're missing home\r\n";
    char str10[] = "Only know you love her when you let her go\r\nAnd you let her go\r\n";
    char *ans[16], *ans2[16], *ans3[16], *ans4[16], *ans5[16];
    for (i_csp = 0; i_csp < 16; i_csp++) {
        ans[i_csp] = (char *)malloc(128);
        ans2[i_csp] = (char *)malloc(128);
        ans3[i_csp] = (char *)malloc(128);
        ans4[i_csp] = (char *)malloc(128);
        ans5[i_csp] = (char *)malloc(256);
    }
    strsplit(str, ans, "\r\n");
    strsplit(str2, ans2, "\r\n");
    strsplit(str3, ans3, "\r\n");
    strsplit(str4, ans4, "\r\n");
    assert_string_equal(ans[0], "A");
    assert_string_equal(ans2[0], "G AND g");
    assert_string_equal(ans4[0], "Kobe Bryant");
    zlog_debug(logger, "結束測試csplit");
    int q = 0;
    int sss = 0;
    sss = strsplit(str5, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        assert_string_equal(ans5[0], "Passenger | Let Her Go");
        assert_string_equal(ans5[1], "Well you only need the light when it's burning low");
    }
    sss = strsplit(str6, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        assert_string_equal(ans5[0], "Only miss the sun when it starts to snow");
    }
    sss = strsplit(str7, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        printf("3.<%s>>%d\n", ans5[q],sss);
    }
    sss = strsplit(str8, ans5, "\r\n");
    for (q = 0; q < sss; q++) {
        assert_string_equal(ans5[0], "Only know you love her when you let her go");
    }
    sss = strsplit(str9, ans4, "\r\n");
    for (q = 0; q < sss; q++) {
        assert_string_equal(ans4[1], "Only hate the road when you're missing home");
    }
    sss = strsplit(str10, ans, "\r\n");
    for (q = 0; q < sss; q++) {
        assert_string_equal(ans[1], "And you let her go");
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