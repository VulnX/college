CC = gcc
CFLAGS = -g -Wall -Wpedantic -O3 -fsanitize=address -fno-omit-frame-pointer
TARGET = main

$(TARGET): main.c dataset.c model.c list.h
	$(CC) $(CFLAGS) -o main main.c dataset.c model.c -lm
clean:
	rm -f main
