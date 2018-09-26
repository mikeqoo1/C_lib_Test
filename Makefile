vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

INC=-I/usr/local/include/google
LIB=-L/usr/local/lib -I/usr/local/include

C_FLAGS = -lcheck -lm -lzlog -lpthread -g -Wall
objects = cmap.o map.o mocha.o csplit.o
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
	gcc -I clib $^ -o test.out $(C_FLAGS)

all: C_FLAGS += -Dmocha -Dgitmap -Dcmap -Dcsplit
all: main.c $(objects)
	gcc -I clib $^ -o test.out $(C_FLAGS)

# 只make clib
lib: $(objects)
$(objects): %.o: %.c
	gcc -c -I clib $< -o $@ -g

# google版本test
google: Google/google.c
	gcc -o Google/google.out $(INC) $(LIB) -lcmockery $^ -lm

# check版本test
check: Check/main.c
	gcc -o Check/check.out Check/main.c -lcheck

clean:
	rm *.o test.out
