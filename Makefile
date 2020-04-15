TARGET = SRead
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): main.o sread.a
	$(CC) $(CFLAGS) $^ -o $@ -lm

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

sread.a: sread.o
	ar rcs $@ $^

sread.o: src/sread.c src/sread.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
