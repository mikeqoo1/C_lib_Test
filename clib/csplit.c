#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csplit.h"
static char THE_REST_STR[1024] = {0}; //剩餘字串
int strsplit (const char *str, char *ans[], const char *delimiter) {
	char *All_Str = malloc(2048); //剩餘加上現有的str
	char *ptr = All_Str; //存一個指標指到All_Str的地址,方便free掉
	sprintf(All_Str, "%s%s", THE_REST_STR, str);
	memset(THE_REST_STR, '\0', strlen(THE_REST_STR)); //清空剩餘字串
	char *cut_str;

	int index = 0;
	cut_str = strstr(All_Str, delimiter);

	strncpy(ans[index++], All_Str, strlen(All_Str) - strlen(cut_str));

	while (cut_str != NULL) {
		cut_str[0]='\0'; //讓上一個找到的符號改成結束字元
		All_Str = cut_str + strlen(delimiter); //接起來,再繼續找
		//printf("while loop All_Str = %s\n",All_Str);
		cut_str = strstr(All_Str, delimiter);
		if (cut_str == NULL) { //代表是最後一個字串,一定是剩餘字串,不然早就切了
			strcpy(ans[index++], All_Str);
			strcpy(THE_REST_STR, All_Str);
		} else {
			strncpy(ans[index++], All_Str, strlen(All_Str) - strlen(cut_str));
			//printf("while cut_str = %s\n while ans[i++] = <%s> %d\n", cut_str, ans[index-1], index);
		}
	}
	free(ptr);
	return index;
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