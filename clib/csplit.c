#include <stdlib.h>
#include <string.h>
#include "csplit.h"

int strsplit (const char *str, char *ans[], const char *delimiter) {
	char *cut_str; //切割後字串
	int i = 0;
	char *copy = NULL;
	char *tmp = NULL;
	/*
	strdup函數原型：
	strdup()主要是複製s的一個副本，由函數回傳值返回，這個副本有自己的記憶體空間，和s不相關。
	strdup函數複製一個字串，使用完後要記得删除在函數中動態取得的記憶體，strdup函數的參數不能為NULL，一旦是NULL，就會有區段錯誤，
	因為該函數包括了strlen函數，而該函數參數不能是NULL。
	*/
	copy = strdup(str); //如果分配空間失敗,則回傳NULL值
	if (!copy)
		goto fail;

	cut_str = strtok(copy, delimiter);

	tmp = strdup(cut_str);
	if (!tmp)
		goto fail;

	ans[i++] = tmp;

	while (cut_str) {
		cut_str = strtok(NULL, delimiter);
		if (NULL == cut_str)
			break;
		tmp = strdup(cut_str);
		if (!tmp)
			goto fail;
		ans[i++] = tmp;
	}

	free(copy); //這個一定要用free(),釋放記憶體空間
	return i;

	fail:
	free(copy); //這個一定要用free(),釋放記憶體空間
	int j;
	for (j = 0; j < i; j++)
		free(ans[j]);
	return -1;
}

int find_the_rest(const char *str, const char *delimiter)
{
	int TorF;
	int i;
	size_t len = strlen(str);
	size_t dellen = strlen(delimiter);
	int x = dellen - 1;
	char temp[x];
	for (i = 0; i < len; i++) {
		if (i+1 == len) { //代表最後一個字,開始判斷
		int start = i - dellen;
		int tempx = 0;
			while(dellen != 0){
				temp[tempx++] = str[++start];
				printf("while ==>%c\n", temp[x]);
				dellen--;
			}
		}
	}
	printf("while EnD==>%s\n", temp);
	if(strcmp(temp,delimiter) == 0) { //代表相等
		return 0;
	}
	return 1;
}