NAME = ztable
OS = $(shell uname | sed 's/[_ ].*//')
LDFLAGS =
DFLAGS = -g -O0 -fsanitize=address -fsanitize-undefined-trap-on-error 
CLANGFLAGS = -Wall -Werror -std=c99 -Wno-unused -Wno-format-security
GCCFLAGS = -Wall -Werror -std=c99 -Wno-unused
CFLAGS = $(CLANGFLAGS)
CFLAGS = $(GCCFLAGS)
CC = clang
CC = gcc
PREFIX = /usr/local
VERSION = 0.01

# Adding debug flags is necessary, b/c we need to print out the table.
test: CFLAGS += -DDEBUG_H
test:
	$(CC) $(CFLAGS) -o $(NAME)-test $(NAME).c main.c

debug: CC = clang
debug: CFLAGS += $(DFLAGS)
debug: test
	@printf '' > /dev/null

clean:
	-@rm *.o $(NAME)-test
