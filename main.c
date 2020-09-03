#include "cmap.h"
#include "csplit.h"
#include "map.h"
#include "mocha.h"
#include "switchs.h"
#include "timesub.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

void SWITCH(char **argv);
void printIntArr(int *arr, int arrSize);
int cmpfunc(const void *a, const void *b);

#ifdef mocha
int test1()
{
    int i = 4;
    int j = 4;
    // void assert(expression);
    assert(i == j);
    // return 0 to tell mocha this test pass
    return 0;
}
int test2()
{
    int l = 12;
    assert(l == 12) return 0;
}
#endif

#ifdef Coo
struct PokeMon {
    size_t size;
    void (*create)(size_t size);
    int (*delete)(const char *key);
    int (*fetch)(const char *key, intptr_t *value);
    void (*store)(const char *key, void *value);
};

void PokeMonNew(struct PokeMon *obj, size_t size)
{
    obj->create = createmap;
    obj->delete = delete;
    obj->fetch = fetch;
    obj->store = store;
    obj->size = size;
}
#endif
int main(int argc, char **argv)
{
    int ok;
    ok = log_init();
    if (ok == 0) {
        logger = getLogger(1);
    } else {
        printf("取得log指標失敗\n");
        return 0;
    }
    printf("Hello, World!\n");
//----mocha
#ifdef mocha
    printf("----mocha的範例----\n");
    describe("Test Example", test1, test2);
    printf("----mocha的範例----\n");
#endif

//----git map
#ifdef gitmap
    printf("----git上別人的map分隔----\n");
    map_int_t m;
    map_init(&m);
    map_set(&m, "testkey", 4546464);
    map_set(&m, "ABC", 558);
    int *val = map_get(&m, "testkey");
    if (val) {
        printf("value: %d\n", *val);
    } else {
        printf("value not found\n");
        LOG_DEBUG(logger, "value not found\033[0m");
    }
    int *val2 = map_get(&m, "AAA");
    if (val2) {
        printf("value: %d\n", *val);
    } else {
        printf("value not found\n");
        LOG_DEBUG(logger, "value not found\033[0m");
    }
    printf("----git上別人的map分隔----\n");
#endif

//----cmap
#ifdef cmap
    printf("----我自己寫的map分隔----\n");
    static const char *const keys[] = {"red",  "orange", "yellow", "green",
                                       "blue", "white",  "black"};
    intptr_t value;
    int i;
    if (hcreate(50) == 0) fail("hcreate");
    printf("開始插入\n");
    store("red", "紅色");
    store("orange", "AAA");
    store("green", "綠色");
    store("blue", "藍色");
    store("white", "白色");
    store("black", "黑色");
    store("orange", "橘色"); //會覆蓋前面的value
    store("123456", (void *)555777888999);
    if (fetch("123456", &value)) {
        printf("123456 has value %d\n", (int)value);
        LOG_FATAL(logger, "123456 has value %d\033[0m", (int)value);
        LOG_ERROR(logger, "123456 has value %d\033[0m", (int)value);
        LOG_WARN(logger, "123456 has value %d\033[0m", (int)value);
        LOG_INFO(logger, "123456 has value %d\033[0m", (int)value);
        LOG_DEBUG(logger, "123456 has value %d\033[0m", (int)value);
    } else {
        printf("123456 is not in table\n");
    }
    printf("印出結果\n");
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        if (fetch(keys[i], &value))
            printf("%s has value %s\n", keys[i], (char *)value);
        else
            printf("%s is not in table\n", keys[i]);
    }
    printf("刪除 orange\n");
    delete ("orange");
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        if (fetch(keys[i], &value))
            printf("%s has value %s\n", keys[i], (char *)value);
        else
            printf("%s is not in table\n", keys[i]);
    }
    delete ("123456");
    if (fetch("123456", &value))
        printf("123456 has value %d\n", (int)value);
    else
        printf("123456 is not in table\n");
    printf("----我自己寫的map分隔----\n");
#endif

//----csplit
#ifdef csplit
    printf("----csplit分隔----\n");
    int z;
    int x;
    char str[] = "hello world\r\nNike\r\nPokeMon!\r\nMike\r\nLBJ\r\nNBA\r\nCrrry "
                 "AND ";                                             //尾端剩餘
    char str2[] = "KD\r\nRay\r\nRuby\r\nEZ\r\nJack\r\nMJ\r\nPG\r\n"; //正常
    char str3[] = "Kobe";                                            //單一剩餘的情況
    char str4[] = " Bryant\r\n";
    char *ans[16];
    char *ans2[16];
    char *ans3[16];
    char *ans4[16];
    int i_csp = 0;
    for (; i_csp < 16; i_csp++) {
        ans[i_csp] = (char *)malloc(128);
        ans2[i_csp] = (char *)malloc(128);
        ans3[i_csp] = (char *)malloc(128);
        ans4[i_csp] = (char *)malloc(128);
    }
    size_t size;
    size = strsplit(str, ans, "\r\n");
    printf("尾端剩餘\n");
    for (z = 0; z < size; ++z) {
        printf("分割後:第%d個:%s\n", z, ans[z]);
    }
    size_t size2 = strsplit(str2, ans2, "\r\n");
    printf("尾端剩餘+正常\n");
    for (x = 0; x < size2; ++x) {
        printf("分割後:第%d個:%s\n", x, ans2[x]);
    }
    size_t size3 = strsplit(str3, ans3, "\r\n");
    printf("單一剩餘\n");
    for (x = 0; x < size3; ++x) {
        printf("分割後:第%d個:%s\n", x, ans3[x]);
    }
    size_t size4 = strsplit(str4, ans4, "\r\n");
    printf("單一剩餘+正常\n");
    for (x = 0; x < size4; ++x) {
        printf("分割後:第%d個:%s\n", x, ans4[x]);
    }
    // if(find_the_rest(str,"\r\n")) {
    // 	printf("代表有剩餘\n");
    // } else{
    // 	printf("代表沒有剩餘\n");
    // }
    printf("----csplit分隔----\n");
#endif

//----C Object Oriented
#ifdef Coo
    intptr_t pokemon;
    struct PokeMon Charizard;
    PokeMonNew(&Charizard, 50);
    Charizard.create(Charizard.size);
    printf("Charizard.size = %ld\n", Charizard.size);
    Charizard.store("噴火龍", "名稱:噴火龍 等級:100 主人:Mike 招式:噴射火焰 超進化:可以");

    struct PokeMon Cyndaquil;
    PokeMonNew(&Cyndaquil, 100);
    // Cyndaquil.create(Cyndaquil.size);
    printf("Cyndaquil.size = %ld\n", Cyndaquil.size);
    Cyndaquil.store("火球鼠", "名稱:火球鼠 等級:100 主人:Ann 招式:火焰漩渦 超進化:不可以");

    if (Charizard.fetch("噴火龍", &pokemon))
        printf("資料是%s\n", (char *)pokemon);
    else
        printf("找不到噴火龍\n");

    if (Cyndaquil.fetch("火球鼠", &pokemon))
        printf("資料是%s\n", (char *)pokemon);
    else
        printf("找不到火球鼠\n");

    if (Cyndaquil.fetch("未知圖騰", &pokemon))
        printf("資料是%s\n", (char *)pokemon);
    else
        printf("找不到未知圖騰\n");
#endif

    SWITCH(argv);

    int arr[] = {56, 45, 48, 12, 4, 3, 4568, 45, 48, 213, 54, 32, 4, 8, 9, 6, 4, 23, 0, -2, 56};
    printIntArr(arr, (sizeof(arr) / sizeof(int)));
    qsort(arr, sizeof(arr) / sizeof(int), sizeof(int), cmpfunc); //Quick sort
    printIntArr(arr, (sizeof(arr) / sizeof(int)));

    return 0;
}

void SWITCH(char **argv)
{
    char *argvtemp = "TEST";
    if (argv[1] != NULL) {
        argvtemp = argv[1];
    }
    switchs(argvtemp)
    {
        cases("bar") printf("foo or bar (區分大小寫)\n");
        break;
        icases("pi") printf("pi or Pi or pI or PI (不分大小寫)\n");
        break;
        cases_re("^D.*", 0) printf("Something that start with D (有大寫的D開頭都算)\n");
        break;
        cases_re("^E.*", REG_ICASE) printf("Something that start with E (大小寫的E,e開頭都算)\n");
        break;
        cases("1") printf("1\n");
        cases("2") printf("2\n");
        break;
        defaults printf("TEST\n");
        break;
    }
    switchs_end;
}

void printIntArr(int *arr, int arrSize)
{
    int i = 0;
    for (i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int cmpfunc(const void *a, const void *b) { return *(int *)a - *(int *)b; }