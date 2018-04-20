CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror

all: test_no_logging test_emerg test_info test_no_args

test_no_logging: example.c logger.h
	$(CC) $(CFLAGS) -o test_no_logging example.c -D_DISABLE_LOGGER

test_emerg: example.c logger.h
	$(CC) $(CFLAGS) -o test_emerg example.c	-DLOG_LEVEL=LOG_EMERG

test_info: example.c logger.h
	$(CC) $(CFLAGS) -o test_info example.c	-DLOG_LEVEL=LOG_INFO

test_no_args: example.c logger.h	
	$(CC) $(CFLAGS) -o test_no_args example.c

clean:
	rm -f *.o test_no_args test_info test_emerg test_no_logging

.PHONY: all clean
