CC = gcc
CFLAGS = -Wall -Wextra -O2 -I/local/include
LDLIB =  -L/local/lib -loqs -lcrypto 
# Targets
all: benchmark

main: main.o
	$(CC) -c main.c
speed_common: speed_common.o
	$(CC) -c speed_comon.c
speed_kem: speed_kem.o
	$(CC) -c speed_kem.c
speed_sig: speed_sig.o
	$(CC) -c speed_sig.c

benchmark: main.o speed_common.o speed_kem.o speed_sig.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIB)

clean:
	rm -f *.o benchmark

.PHONY: all clean
