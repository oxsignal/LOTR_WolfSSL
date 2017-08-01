CC = cc
ARC64 = -m64
CFLAGS = -Wall -lm
RM = rm -f
CLIB_INCLUDE = /usr/local/include
STATIC_LIB = wolfssl.lotr.gcc.x64.static.lib
STATIC_LIB_DIR = ../lib
DEBUG_FLAGS = -g -DDEBUG

all: build

build: client server

client:
	$(CC) -o $@ client-tls.c -I$(CLIB_INCLUDE) -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS)

server: 
	$(CC) -o $@ server-tls.c -I$(CLIB_INCLUDE) -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS)

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: all

clean:
	$(RM) client
	$(RM) server
