#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int status, i;
    int cflags = REG_EXTENDED;
    regmatch_t pmatch;
    const size_t nmatch = 1;
    
    regex_t reg;

    //權證風險
    const char *pattern1 = "^[0][3-8]{1}[0-9]{3}[Q,F]";
    const char *pattern2 = "^[0][3-8]{1}[0-9]{3}[C,B]";
    const char *pattern3 = "^[0][3-8]{1}[0-9]{3}[X,Y]";
    //公司債風險

    //ETN槓桿反向風險
    const char *pattern4 = "^[0][2-9]{1}[0-9]{3}[L,R]";

    char *buf = "03001F";

    int a = regcomp(&reg, pattern1, cflags);           //編譯正則模式
    printf("a = %d\n", a);
    status = regexec(&reg, buf, nmatch, &pmatch, 0); //執行正規表示式和快取的比較
    if (status == REG_NOMATCH) {
        printf("No match\n");
    } else if (0 == status) {
        printf("比較成功 :\n");
        for (i = pmatch.rm_so; i < pmatch.rm_eo; i++) {
            putchar(buf[i]);
        }
        printf("\n");
    }
    regfree(&reg);
    return 0;
}