[![Build Status](https://travis-ci.org/mikeqoo1/C_lib_Test.svg?branch=master)](https://travis-ci.org/mikeqoo1/C_lib_Test)

# C_Lib_Test
測試C的小功能,小東西

# 說明

make時,帶的參數可以決定要示範哪些例子,
make mocha=1 gitmap=1 cmap=1 csplit=1 Coo=1
如果要直接看全部,直接make all

# Clib

csplit ---> C的通用切包,使用strstr實作 內部包含2個方法 切包 和 判斷是不是有剩餘字串

cmap ---> 用Linux提供的search.h實作的map

map ---> github https://github.com/rxi/map 提供

mocha ---> 彩色的單元測試框架

增加類似用結構的方法,實作C++的OO設計

# 注意事項

cmap的key,一定不能指向一個空的pointer,會出錯

csplit,本來是使用strtok來作的,但是,strtok會把要切的符號個別判斷,例如 \r\n只要是 \r或\n 就切掉了
新增加判斷,假設第一包就是斷包的情況,也可以處理

# Zlog

這邊直接附上中文手冊 https://hardysimpson.github.io/zlog/UsersGuide-CN.html#htoc11

# 尚缺項目

各部份的單元測試,需要補上
