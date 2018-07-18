#include <stdlib.h>
#include <string.h>
#include "csplit.h"
static char *THE_REST_STR = NULL;
int strsplit (const char *str, char *ans[], const char *delimiter) {
	char *cut_str; //比較後字串
	int i = 0; //要回傳的筆數
	char tmp[256]; //結果
	char *copy_str = NULL; //複製一份原始的資料字串
	memset(tmp, '\0', sizeof(tmp));
	/*
	strdup函數原型：
	strdup()主要是複製s的一個副本，由函數回傳值返回，這個副本有自己的記憶體空間，和s不相關。
	strdup函數複製一個字串，使用完後要記得删除在函數中動態取得的記憶體，strdup函數的參數不能為NULL，一旦是NULL，就會有區段錯誤，
	因為該函數包括了strlen函數，而該函數參數不能是NULL。
	*/
	copy_str = strdup(str);
	if (THE_REST_STR != NULL) {
		strcat(copy_str,THE_REST_STR); //接起剩餘字串
	}
	cut_str = strstr(copy_str, delimiter);
	printf("copy_str = %s 大小 = %d\ncut_str = %s 大小 = %d\n",copy_str, strlen(copy_str), cut_str, strlen(cut_str));
	strncpy(tmp, copy_str, strlen(copy_str) - strlen(cut_str));
	printf("結果: tmp = %s index = %d\n", tmp, i);
	ans[i++] = strdup(tmp);

	while (cut_str != NULL) {
		memset(tmp, '\0', sizeof(tmp));
		cut_str[0]='\0'; //讓上一個找到的符號改成結束字元
		copy_str = cut_str + strlen(delimiter); //接起來,再繼續找
		printf("while loop copy_str = %s\n",copy_str);
		cut_str = strstr(copy_str, delimiter);
		if (cut_str == NULL) { //代表是最後一個字串,一定是剩餘字串,不然早就切了
			if (THE_REST_STR != NULL) {
				strcpy(THE_REST_STR, ""); //清空上次的剩餘字串
			}
			ans[i++] = strdup(copy_str);
			THE_REST_STR = strdup(copy_str);
			break;
		} else {
			strncpy(tmp, copy_str, strlen(copy_str) - strlen(cut_str));
			printf("while cut_str = %s\n while tmp = <%s> %d\n", cut_str, tmp, i);
			ans[i++] = strdup(tmp);
		}
	}
	return i;
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