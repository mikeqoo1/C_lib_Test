vpath %.h clib  #vpath 指定搜尋路徑
vpath %.c clib

objects = cmap.o map.o mocha.o
test: main.c $(objects)
	gcc -I clib $^ -o test -lcheck -lm

all: $(objects)
$(objects): %.o: %.c
	gcc -c -I clib $< -o $@

.PHONY: clean
clean:
	rm *.o test