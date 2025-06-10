
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDLIB = -I$(PWD)/../local/include -L$(PWD)/../local/lib -lcrypto -lssl -loqs 
# Targets
all: target

target: main.c speed_common.c speed_kem.c speed_sig.c
	$(CC) $(CFLAGS) $(LDLIB) -o $@ $^

clean:
	rm -f *.o target

.PHONY: all clean
