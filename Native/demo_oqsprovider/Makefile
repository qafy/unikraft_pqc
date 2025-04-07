CFLAGS  = -I/workspace/Native/opt/include -g -Wall
LDFLAGS = -L/workspace/Native/opt/lib
LDLIBS  =  -loqs -lcrypto -loqsprovider 
CC		= /workspace/Native/musl-install/bin/musl-gcc

example_oqs_static:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ example_oqs_static.c $(LDLIBS)

clean:
	$(RM) example_oqs_static



