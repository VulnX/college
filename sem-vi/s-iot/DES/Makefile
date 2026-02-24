CC = gcc
CFLAGS = -g -Wall -Wpedantic -O3 -fsanitize=address -fno-omit-frame-pointer
TARGET = main

$(TARGET): main.c
	$(CC) $(CFLAGS) -o main main.c -lcrypto
clean:
	rm -f main
