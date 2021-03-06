CC = cc
ARC64 = -m64
ARC32 = -m32
CFLAGS = -Wall -lm -lpthread
RM = rm -rf
STATIC_LIB = wolfssl
STATIC_LIB32 = wolfssl32
STATIC_LIB_DIR = ../lib
DEBUG_FLAGS = -g -DDEBUG
CLIENT = client
SERVER = server
BENCHMARK = ../.libs/benchmark
BENCHMARK32 = ../.libs/benchmark
BENCHMARK_DIR = ../.libs/
NO_STACK_PROTECT = -fno-stack-protector
STACKCFLAGS = $(CFLAGS) $(NO_STACK_PROTECT)
WOLFSSL_ROOT = ../../wolfssl/

all: build

build: $(CLIENT) $(SERVER) $(BENCHMARK)

arc32: $(BENCHMARK32)

$(CLIENT):
	$(CC) -static -o $@ client-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

$(SERVER):
	$(CC) -static -o $@ server-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

$(BENCHMARK):
	mkdir ../.libs
	cp $(WOLFSSL_ROOT)/wolfcrypt/benchmark/benchmark ../
	$(CC) -static -o $@ benchmark.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(STACKCFLAGS) -I../../wolfssl

$(BENCHMARK32):
	mkdir ../.libs
	cp $(WOLFSSL_ROOT)/wolfcrypt/benchmark/benchmark ../
	$(CC) -static -o $@ benchmark.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB32) $(ARC32) $(CFLAGS) -I../../wolfssl

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: all

clean:
	$(RM) $(CLIENT)
	$(RM) $(SERVER)
	$(RM) $(BENCHMARK_DIR)
	$(RM) ../benchmark
