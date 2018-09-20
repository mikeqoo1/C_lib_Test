#pragma once
#include <stdlib.h>
#include <string.h>

int strsplit(const char *str, char *ans[], const char *delimiter);

//有剩餘字串會回傳1 回傳0代表沒有剩餘字串
int find_the_rest(const char *str, const char *delimiter);