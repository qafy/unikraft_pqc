CFLAGS  = -I/Users/moritzbeckel/Desktop/IDP/src/opt/include -g -Wall
LDFLAGS = -L/Users/moritzbeckel/Desktop/IDP/src/opt/lib
LDLIBS  =  -loqs -lcrypto -loqsprovider 

example_oqs_static:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ example_oqs_static.c $(LDLIBS)

clean:
	$(RM) example_oqs_static



