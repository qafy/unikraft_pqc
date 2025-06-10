
# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDLIB = -I/local/include 
# Targets
all: target

target: main.c speed_common.c speed_kem.c speed_sig.c
	$(CC) $(CFLAGS) $(LDLIB) -o $@ /local/lib/libcrypto.a /local/lib/liboqs.a $^ 

clean:
	rm -f *.o target

.PHONY: all clean
