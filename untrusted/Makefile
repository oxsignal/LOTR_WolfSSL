CC = cc
ARC64 = -m64
CFLAGS = -Wall -lm -lpthread
RM = rm -f
STATIC_LIB = wolfssl
STATIC_LIB_DIR = ../lib
DEBUG_FLAGS = -g -DDEBUG
CLIENT = client
SERVER = server
BENCHMARK = benchmark
NO_STACK_PROTECT = -fno-stack-protector
STACKCFLAGS = $(CFLAGS) $(NO_STACK_PROTECT)


all: build

build: client server benchmark

client:
	$(CC) -static -o $@ client-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

server:
	$(CC) -static -o $@ server-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

benchmark:
	$(CC) -static -o $@ benchmark.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(STACKCFLAGS) -I../../wolfssl

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: all

clean:
	$(RM) $(CLIENT)
	$(RM) $(SERVER)
	$(RM) $(BENCHMARK)
