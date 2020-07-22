#include "log.h"

int log_init()
{
    int rc;
    rc = zlog_init("/home/Projects/C_lib_Test/zlogconfig.conf");
    if (rc) {
        printf("初始化log設定檔,失敗\n");
        return -1;
    }
    init_zlog_category();
    return 0;
}

int init_zlog_category()
{
    if (!(logger = zlog_get_category("my_log"))) {
        printf("找不到my_log的規則\n");
        zlog_fini();
        return -1;
    }
    if (!(logger = zlog_get_category("my_dog"))) {
        printf("找不到my_dog的規則\n");
        zlog_fini();
        return -1;
    }
    if (!(logger = zlog_get_category("my_test"))) {
        printf("找不到my_test的規則\n");
        zlog_fini();
        return -1;
    }
    return 0;
}

zlog_category_t *getLogger(int rule)
{
    switch (rule) {
    case 1:
        printf("my_log\n");
        logger = zlog_get_category("my_log");
        return logger;
        break;
    case 2:
        printf("my_dog\n");
        logger = zlog_get_category("my_dog");
        return logger;
        break;
    case 3:
        printf("my_test\n");
        logger = zlog_get_category("my_test");
        return logger;
        break;
    default:
        printf("沒東西\n");
    }
    return NULL;
}