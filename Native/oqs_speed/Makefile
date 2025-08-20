
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I$(PWD)/../local/include
LDLIB =  -L$(PWD)/../local/lib -loqs -lcrypto -lm

all: benchmark

benchmark: main.c speed_kem.c speed_sig.c speed_common.c speed_vanilla.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIB) 

clean:
	rm -f benchmark

.PHONY: all clean
