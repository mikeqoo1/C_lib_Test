#include <check.h>
#include <stdio.h>

/*
 * 利用暴力法
 * 計算start, start + step, start + step * 2 ... end的總和
 */
int series_sum_ref(int start, int end, int step)
{
  int s = 0;
  for(; start <= end; start += step)
    {
      s += start;
    }
  return s;
}

/*
 * 利用公式
 * 計算start, start + step, start + step * 2 ... end的總和
 */
int series_sum_formula(int start, int end, int step)
{
  int n = (end - start) / step + 1;
  return n * (2 * start + (n - 1) * step) / 2;
}

/*
 * 所有的Unit test都要用START_TEST和END_TEST來包裹起來
 */
START_TEST(test_series_ref)
{
  fail_if(series_sum_ref(1, 10, 1) != 55);
  fail_if(series_sum_ref(1, 10, 2) != 25);
  fail_if(series_sum_ref(3, 5, 2) != 8);
}
END_TEST

START_TEST(test_series_formula)
{
  int a, b, s;
  for(a = -20; a <= -10; a++)
    {
      for(b = 0; b <= 10; b++)
        {
          for(s = 1; s <= 3; s++)
            {
              int r = series_sum_ref(a, b, s);
              int f = series_sum_formula(a, b, s);
              if(r != f)
                {
                  printf("\nFail at a = %d, b = %d, s = %d\nr = %d, f = %d\n", a, b, s, r, f);
                  fail("Test failed: the series sum from reference and formula are different.");
                }
            }
        }
    }
}
END_TEST

/*
 * check的架構：
 * 可以設定許多組Suite, 每組Suite都有許多的TCase, 
 * 每個Tcase又有許多test
 * 總之呢，這是一個階層式的架構。
 *
 * Suite1
 * __ TCase1
 * _____ Test1
 * _____ Test2
 * ...
 * __ TCase2
 * ...
 * __ TCase3
 * ...
 * Suite2
 * __ TCase2-1
 * ...
 */
int main()
{
  TCase* series_sum_case = tcase_create("Arith. Series");
  tcase_add_test(series_sum_case, test_series_ref);
  tcase_add_test(series_sum_case, test_series_formula);

  Suite* suite = suite_create("Main Suite");
  suite_add_tcase(suite, series_sum_case);
  
  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_VERBOSE);
  
  int fail_count = srunner_ntests_failed(runner);
  srunner_free(runner);
}