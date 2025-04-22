# TODOs
- [ ] Build vanilla ssl Unikernel
- [ ] Build oqs ssl Unikernel

## Vanilla SSL Unikernel Doc: [ssl_uk]
- ~~ Build openssl directly into unikernel ~~
	-> Building openssl again and again inefficient
	-> Building openssl into Unikraft unikernel  
- Instead build openssl as prebuild binary into unikernel
	-> Call openssl binary and header files during unikraft build in Makefile.uk
``` Makefile.uk
APPOPENSSL_OBJS-y += $(APPOPENSSL_BASE)/openssl-3.3.0/libssl.a
```
	-> see [Unikraft Build System](https://unikraft.org/docs/internals/build-system)
- Build successfull, but nothing to do, as only the library was added
- ssl keygen through c file (chat gpt generated :D)
- Include c file with
``` Makefile.uk
APPOPENSSL_SRCS-y += $(APPOPENSSL_BASE)/ssl_keygen_2024_no_time.c
```
	-> ssl header files missing. Include them with 

``` Makefile.uk
APPOPENSSL_CINCLUDES += -I$(APPOPENSSL_BASE)/openssl-3.3.0/include/
```
- pthread header missing
	-> kraft menu shows it is included ...
	-> pull from [lib-pthread-embedded](https://github.com/unikraft/lib-pthread-embedded)
	-> include pthread like openssl above

## OQS SSL Unikernel Doc

