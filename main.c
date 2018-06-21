#include <stdio.h>
#include "mocha.h"
#include "map.h"

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
	describe(
		"Test Example",
		test1,
		test2
		);
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

	return 0;
}
