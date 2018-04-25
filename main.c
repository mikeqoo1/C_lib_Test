#include <stdio.h>
#include "mocha.h"

int test1()
{
	int i = 3;
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

	return 0;
}
