#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <google/cmockery.h>

#define malloc test_malloc
#define calloc test_calloc
#define free test_free

int add(int, int);
int sub(int, int);
int div(int, int);
int test(int, char *);

// === assert test ===
void test_add(void **state) {
	assert_int_equal(add(3, 3), 6);
	assert_int_not_equal(add(3, 3), 5);
}

// === malloc test ===
void test_sub(void **state) {
	assert_int_equal(sub(3, 3), 0);
}

// === run before test ===
void before_test_div(void **state) {
	print_message("== before test div == \n");
}

// === mock test ===
void test_div(void **state) {
	assert_int_equal(div(3, 3), 1);
}

void test_for_mock(void **state) {
	expect_value(test, value, 1);
	expect_string(test, string, "test");
	will_return(test, 0x123456);
	assert_int_equal(test(1, "test"), 0x123456);
}

int main(int argc, char* argv[]) {
	const UnitTest tests[] = {
		unit_test(test_add),
		unit_test(test_sub),
		unit_test_setup_teardown(before_test_div, test_div, NULL),
		unit_test(test_for_mock),
	};
	return run_tests(tests);
}

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	int *res = (int*)malloc(sizeof(int));
	return *res = a - b;
}

int div(int a, int b)
{
	return a / b;
}

int test(int value, char *string)
{
	check_expected(value);
	check_expected(string);
	return (int)mock();
}

/*
	通過expect_value和check_expected可以判斷傳入函式的值是不是期望的值，
	而will_return和mock則是對應的關係，will_return會將值放入到queue中，
	而每次用mock都會取到queue前端的值。
*/