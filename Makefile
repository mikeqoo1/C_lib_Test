vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

INC=-I/usr/local/include/google
LIB=-L/usr/local/lib -I/usr/local/include

C_FLAGS = -lcheck -lm -lzlog -lpthread -luv -Wall
CI_FLAGS = -lm -lpthread -Wall
objects = cmap.o map.o mocha.o csplit.o timesub.o
.PHONY: clean all lib debug google

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

debug: main.c $(objects)
	gcc -I clib -o main.out $(CI_FLAGS) -g $^

all: CI_FLAGS += -Dmocha -Dgitmap -Dcmap -Dcsplit
all: main.c $(objects)
	gcc -I clib -o main.out $(CI_FLAGS) -O3 $^

bench: benchmark.c csplit.o timesub.o
	gcc -I clib -o bench.out $(C_FLAGS) -O3 $^

# 只make clib
lib: $(objects)
$(objects): %.o: %.c
	gcc -c -I clib $< -o $@ -g

# clib的單元測試
utest: Google/unittest.c $(objects)
	gcc -o Google/unittest.out -I clib $(INC) $(LIB) $(C_FLAGS) -lcmockery $^

# google版本test
google: Google/google.c
	gcc -o Google/google.out $(INC) $(LIB) -lcmockery $^

# check版本test
check: Check/main.c
	gcc -o Check/check.out Check/main.c -lcheck $^

clean:
	rm *.o main.out bench.out


# 特殊符號說明
#  – $@ 代表工作目標 (上例中的 %.o)
#  – $^ 代表所有的必要條件 (上例中的 %.c)
#  – $< 代表第一個必要條件 (上例中的 %.c，因為例子中只有一個必要條件)
