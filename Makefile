NAME = ztable
LDFLAGS =
DFLAGS = -g -O0 -fsanitize=address -fsanitize-undefined-trap-on-error
CLANGFLAGS = -Wall -Werror -std=c99 -Wno-unused -Wno-format-security
GCCFLAGS = -Wall -Werror -std=c99 -Wno-unused -DLT_TABDUMP
CFLAGS = $(CLANGFLAGS)
CFLAGS = $(GCCFLAGS)
CC = clang
CC = gcc
PREFIX = /usr/local
VERSION = 0.01

test:
	$(CC) $(CFLAGS) -DDEBUG_H -o $(NAME)-test $(NAME).c main.c

win: CC = clang
win: CFLAGS = $(CLANGFLAGS)
win:
	$(CC) $(CFLAGS) -DDEBUG_H -o $(NAME)-test.exe $(NAME).c main.c

clang: CC = clang
clang: CFLAGS = $(CLANGFLAGS)
clang: test
	@printf '' > /dev/null

debug: CC = clang
debug: CFLAGS += $(DFLAGS)
debug: test
	@printf '' > /dev/null

clean:
	@rm *.o $(NAME)-test*
