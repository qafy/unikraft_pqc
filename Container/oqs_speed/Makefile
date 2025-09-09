CC = gcc
CFLAGS = -Wall -Wextra -O2 -static -I/local/include
LDLIB = -L/local/lib -loqs -lcrypto 

all: benchmark

benchmark: main.c speed_kem.c speed_sig.c speed_common.c speed_vanilla.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIB) 

clean:
	rm -f benchmark

.PHONY: all clean