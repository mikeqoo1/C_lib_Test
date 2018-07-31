#pragma once

#include <inttypes.h>	/* intptr_t, PRIxPTR */
#include <search.h>	/* hcreate(), hsearch() */
#include <stdio.h>	/* perror(), printf() */
#include <stdlib.h>	/* exit() */

void fail(char *message);

//新增
void createmap(size_t size);

//刪除
int delete(const char *key);

//搜尋
int fetch(const char *key, intptr_t *value);

//設定key,value
void store(const char *key, void *value);