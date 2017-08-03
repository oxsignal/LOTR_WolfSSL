CC = cc
ARC64 = -m64
CFLAGS = -Wall -lm -lpthread
RM = rm -f
STATIC_LIB = wolfssl
STATIC_LIB_DIR = ../lib
DEBUG_FLAGS = -g -DDEBUG
CLIENT = client
SERVER = server
BENCHMARK = ../.libs/benchmark
BENCHMARK_DIR = ../.libs/
NO_STACK_PROTECT = -fno-stack-protector
STACKCFLAGS = $(CFLAGS) $(NO_STACK_PROTECT)


all: build

build: $(CLIENT) $(SERVER) $(BENCHMARK)

$(CLIENT):
	$(CC) -static -o $@ client-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

$(SERVER):
	$(CC) -static -o $@ server-tls.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(CFLAGS) -I../../wolfssl

$(BENCHMARK):
	$(CC) -static -o $@ benchmark.c -L$(STATIC_LIB_DIR) -l$(STATIC_LIB) $(ARC64) $(STACKCFLAGS) -I../../wolfssl

debug: CFLAGS+=$(DEBUG_FLAGS)
debug: all

clean:
	$(RM) $(CLIENT)
	$(RM) $(SERVER)
	$(RM) $(BENCHMARK_DIR)*
