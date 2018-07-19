vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

objects = cmap.o map.o mocha.o csplit.o
debug: main.c $(objects)
	gcc -I clib $^ -o test -lcheck -lm -g -Wall

all: $(objects)
$(objects): %.o: %.c
	gcc -c -I -g clib $< -o $@
.PHONY: clean debug all
clean:
	rm *.o test