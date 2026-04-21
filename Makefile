all: keyfilter

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror

.PHONY: all run clean

keyfilter: keyfilter.c
	$(CC) $(CFLAGS) keyfilter.c -o "$@"

run: keyfilter
	./keyfilter

clean:
	rm keyfilter
