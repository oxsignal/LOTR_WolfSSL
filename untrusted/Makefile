CC = cc
ARC64 = -m64
CFLAGS = -Wall -lm -lpthread
RM = rm -f
STATIC_LIB = wolfssl
STATIC_LIB_DIR = ../lib
DEBUG_FLAGS = -g -DDEBUG

all: build

build: client server

client:
	$(CC) -static -o $@ client-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

server:
	$(CC) -static -o $@ server-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: all

clean:
	$(RM) client
	$(RM) server
