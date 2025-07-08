
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O0 -g
LDLIB = -I$(PWD)/../local/include -L$(PWD)/../local/lib -loqs -lcrypto -lm
# Targets
all: benchmark

benchmark: main.c speed_common.c speed_kem.c speed_sig.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIB) 

clean:
	rm -f *.o benchmark

.PHONY: all clean
