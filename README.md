# C_Lib_Test
測試C的小功能,小東西


# Clib

csplit ---> C的通用切包,使用strstr實作 內部包含2個方法 切包 和 判斷是不是有剩餘字串

cmap ---> 用Linux提供的search.h實作的map

map ---> github https://github.com/rxi/map 提供

mocha ---> 彩色的單元測試框架

# 注意事項

cmap的key,一定不能指向一個空的pointer,會出錯

csplit,本來是使用strtok來作的,但是,strtok會把要切的符號,個別判斷,例如 \r\n只要是 \r或\n 就切掉了