TARGET = sread
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu11 # Otherwise CRTSCTS flags is undefined

all: $(TARGET)

$(TARGET): main.o sread.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

main.o: main.c sread.o
	$(CC) $(CFLAGS) -c $< -o $@

sread.o: src/sread.c src/sread.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
