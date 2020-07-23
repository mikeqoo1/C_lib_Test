vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

INC=-I/usr/local/include/google
LIB=-L/usr/local/lib -I/usr/local/include
MYSQL = `mysql_config --include --libs`

C_FLAGS = -lcheck -lm -lzlog -lpthread -luv -Wall
CI_FLAGS = -lm -lpthread -Wall
objects = cmap.o map.o mocha.o csplit.o timesub.o log.o
.PHONY: clean all debug
	buildall builddebug
	google bench utest check
	libuvS libuvC

ifeq ($(mocha),1)
C_FLAGS += -Dmocha
endif

ifeq ($(gitmap),1)
C_FLAGS += -Dgitmap
endif

ifeq ($(cmap),1)
C_FLAGS += -Dcmap
endif

ifeq ($(csplit),1)
C_FLAGS += -Dcsplit
endif

ifeq ($(Coo),1)
C_FLAGS += -DCoo
endif

# 編譯執行檔出來
all: buildall clean
debug: builddebug clean

# 編譯指令
builddebug: main.c $(objects)
	gcc -I clib -o main.out $(CI_FLAGS) -g $^

buildall: CI_FLAGS += -Dmocha -Dgitmap -Dcmap -Dcsplit
buildall: main.c $(objects)
	gcc -I clib -o main.out $(C_FLAGS) $(CI_FLAGS) -O3 $^

# 只make clib
lib: $(objects)
$(objects): %.o: %.c
	gcc -c -I clib $(C_FLAGS) $< -o $@ -g

# clib的BenchMark
bench: benchmark.c $(objects)
	gcc -I clib -o bench.out $(LIB) $(C_FLAGS) -O3 $^

# clib的單元測試
utest: Google/unittest.c $(objects)
	gcc -o Google/unittest.out -I clib $(INC) $(LIB) $(C_FLAGS) -lcmockery $^

# google版本test的範例
google: Google/google.c
	gcc -o Google/google.out $(INC) $(LIB) -lcmockery $^

# check版本test的範例
check: Check/main.c
	gcc -o Check/check.out Check/main.c -lcheck $^

# libuv的範例
libuvS: libuv/libuv_Server.c
	gcc -o libuvS.out -luv $^

libuvC: libuv/libuv_Client.c
	gcc -o libuvC.out -luv $^

sheet: clib/sheet.c sheet.o test_sheet.c
	gcc -c clib/sheet.c
	gcc test_sheet.c -I clib sheet.o -o sheet.out

# Regular Expression
reg: regex/regex.c
	gcc -o regex/regex.out regex/regex.c

# ini test...
#ini:
#	gcc -c clib/dictionary.c -I clib
#	gcc -c clib/iniparser.c -I clib
#	gcc -c clib/iniconfig.c -I clib $(MYSQL)
#	gcc testdb.c -I clib -o db.out dictionary.o iniparser.o iniconfig.o $(MYSQL)

# 清理.o檔案
clean:
	rm *.o

# 特殊符號說明
#  – $@ 代表工作目標 (上例中的 %.o)
#  – $^ 代表所有的必要條件 (上例中的 %.c)
#  – $< 代表第一個必要條件 (上例中的 %.c，因為例子中只有一個必要條件)
