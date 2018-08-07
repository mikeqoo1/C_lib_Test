vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

C_FLAGS = -lcheck -lm -g -Wall
objects = cmap.o map.o mocha.o csplit.o
.PHONY: clean all lib debug
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
	gcc -I clib $^ -o test $(C_FLAGS)

all: C_FLAGS += -Dmocha -Dgitmap -Dcmap -Dcsplit -DCoo
all: main.c $(objects)
	gcc -I clib $^ -o test $(C_FLAGS)

# 只make clib
lib: $(objects)
$(objects): %.o: %.c
	gcc -c -I clib $< -o $@ -g

clean:
	rm *.o test