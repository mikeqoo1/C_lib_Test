#include "sheet.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    newsheet concord0;
    concord0 = SetNumero(concord0, 0, 100);
    concord0 = SetTerm(concord0);
    printf("櫃號:%c 起始:%d 結束:%d 序號:%d 索引:%d\n", concord0.term[concord0.index],
           concord0.start, concord0.end, concord0.numero, concord0.index);
    printf("櫃號:%s 序號:%d\n", concord0.term, concord0.numero);
    int i = 0;
    for (i = 0; i < 101; i++) {
        concord0 = Next(concord0);
        printf("櫃號:%c 序號:%d\n", concord0.term[concord0.index], concord0.numero);
    }
    return 0;
}
