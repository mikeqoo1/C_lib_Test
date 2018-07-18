#include <stdio.h>
#include "mocha.h"
#include "map.h"
#include "cmap.h"
#include "csplit.h"

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

	assert(l == 12)

	return 0;
}

int main()
{
//----mocha
	printf("----mocha的範例----\n");
	describe(
		"Test Example",
		test1,
		test2
		);
	printf("----mocha的範例----\n");
//----mocha

//----git map
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
	}
	int *val2 = map_get(&m,"AAA");
		if (val2) {
		printf("value: %d\n", *val);
	} else {
		printf("value not found\n");
	}
	printf("----git上別人的map分隔----\n");
//----git map

//----cmap
	printf("----我自己寫的map分隔----\n");
	static const char *const keys[] =
		{"red", "orange", "yellow", "green", "blue", "white", "black"};
	intptr_t value;
	int i;
	if (hcreate(50) == 0)
		fail("hcreate");
	printf("開始插入\n");
	store("red", "紅色");
	store("orange", "AAA");
	store("green", "綠色");
	store("blue", "藍色");
	store("white", "白色");
	store("black", "黑色");
	store("orange", "橘色"); //會覆蓋前面的value
	store("123456", (void *)555777888999);
	if (fetch("123456", &value))
			printf("123456 has value %d\n", (int *)value);
		else
			printf("123456 is not in table\n");

	printf("印出結果\n");
	for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
		if (fetch(keys[i], &value))
			printf("%s has value %s\n",keys[i], (char *)value);
		else
			printf("%s is not in table\n", keys[i]);
	}
	printf("刪除 orange\n");
	delete("orange");
	for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
		if (fetch(keys[i], &value))
			printf("%s has value %s\n",keys[i], (char *)value);
		else
			printf("%s is not in table\n", keys[i]);
	}
	delete("123456");
	if (fetch("123456", &value))
			printf("123456 has value %d\n", (int *)value);
		else
			printf("123456 is not in table\n");
	printf("----我自己寫的map分隔----\n");
//----cmap

//----csplit
	printf("----csplit分隔----\n");
	int z;
	char str[] = "hello****world****Nike****Kobe****Mike****LBJ****NBA****Crrry****";
	//判斷剩下的
	char *ans[100]; //這邊未來可以動態設定,再做優化
	size_t size = strsplit(str, ans, "****");
	printf("原本的str===>%s\n",str);
	for (z = 0; z < size; ++z) {
		printf("分割後:第%d個:%s\n", z, ans[z]);
	}
	// if(find_the_rest(str,"****")) {
	// 	printf("代表有剩餘\n");
	// } else{
	// 	printf("代表沒有剩餘\n");
	// }
	printf("----csplit分隔----\n");
//----csplit
	return 0;
}
