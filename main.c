#include <stdio.h>
#include "mocha.h"
#include "map.h"
#include "cmap.h"
#include "csplit.h"

int test1() {
	int i = 4;
	int j = 4;
	// void assert(expression);
	assert(i == j);

	// return 0 to tell mocha this test pass
	return 0;
}

int test2() {
	int l = 12;

	assert(l == 12)

	return 0;
}

struct PokeMon {
	size_t size;
	void (*gomap)(size_t size);
	int (*delete)(const char *key);
	int (*fetch)(const char *key, intptr_t *value);
	void (*store)(const char *key, void *value);
};

void Oo_gomap(size_t size){
	hcreate(size);
}

int Oo_delete(const char *key) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, FIND);
	if (p) {
		p->key="NULL"; //key不能指向空指標
		p->data=NULL;
		return 1;
	} else
		return 0;
}

int Oo_fetch(const char *key, intptr_t *value) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, FIND);
	if (p) {
		*value = (intptr_t)p->data;
		return 1;
	} else
		return 0;
}

void Oo_store(const char *key, void *value) {
	ENTRY e = {key: (char *)key}, *p;
	p = hsearch(e, ENTER);
	if (p == NULL)
		fail("hsearch");
	p->data = (void *)value;
}

void PokeMonNew(struct PokeMon *obj,size_t size) {
	obj-> gomap = Oo_gomap;
	obj-> delete = Oo_delete;
	obj-> fetch = Oo_fetch;
	obj-> store = Oo_store;
	obj-> size = size;
}

int main() {

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
			printf("123456 has value %d\n", (int)value);
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
			printf("123456 has value %d\n", (int)value);
		else
			printf("123456 is not in table\n");
	printf("----我自己寫的map分隔----\n");
//----cmap

//----csplit
	printf("----csplit分隔----\n");
	int z;
	int x;
	char str[] = "hello world\r\nNike\r\nPokeMon!\r\nMike\r\nLBJ\r\nNBA\r\nCrrry AND "; //尾端剩餘
	char str2[] = "KD\r\nRay\r\nRuby\r\nEZ\r\nJack\r\nMJ\r\nPG\r\n"; //正常
	char str3[] = "Kobe"; //單一剩餘的情況
	char str4[] = " Bryant\r\n";
	char *ans[16];
	char *ans2[16];
	char *ans3[16];
	char *ans4[16];
	int i_csp = 0;
	for (; i_csp < 16 ; i_csp++){
		ans[i_csp] = (char *)malloc(128);
		ans2[i_csp] = (char *)malloc(128);
		ans3[i_csp] = (char *)malloc(128);
		ans4[i_csp] = (char *)malloc(128);
	}
	size_t size = strsplit(str, ans, "\r\n");
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
//----csplit

//----OO
	struct PokeMon Charizard;
	PokeMonNew(&Charizard,10);
	Charizard.gomap(Charizard.size);
	Charizard.store("red", "紅色");
	if (fetch("red", &value))
		printf("has value %s\n", (char *)value);
	else
		printf("is not in table\n");
//----OO
	return 0;
}