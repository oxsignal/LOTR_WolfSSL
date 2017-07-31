######## Intel(R) SGX SDK Settings ########
ifeq ($(shell getconf LONG_BIT), 32)
	SGX_ARCH := x86
else ifeq ($(findstring -m32, $(CXXFLAGS)), -m32)
	SGX_ARCH := x86
endif

ifeq ($(SGX_ARCH), x86)
	SGX_COMMON_CFLAGS := -m32
else
	SGX_COMMON_CFLAGS := -m64
endif

ifeq ($(SGX_DEBUG), 1)
        SGX_COMMON_CFLAGS += -O0 -g -DSGX_DEBUG
else
        SGX_COMMON_CFLAGS += -O2
endif



Wolfssl_C_Extra_Flags := -DWOLFSSL_SGX
Wolfssl_Include_Paths := -I$(WOLFSSL_ROOT)/ \
						 -I$(WOLFSSL_ROOT)/wolfcrypt/


Wolfssl_Enclave_C_Files := trusted/Wolfssl_Enclave.c

ifeq ($(HAVE_WOLFSSL_TEST), 1)
	Wolfssl_Include_Paths += -I$(WOLFSSL_ROOT)/wolfcrypt/test/
	Wolfssl_C_Extra_Flags += -DHAVE_WOLFSSL_TEST
endif

ifeq ($(HAVE_WOLFSSL_BENCHMARK), 1)
	Wolfssl_Include_Paths += -I$(WOLFSSL_ROOT)/wolfcrypt/benchmark/
	Wolfssl_C_Extra_Flags += -DHAVE_WOLFSSL_BENCHMARK
endif


Flags_Just_For_C := -Wno-implicit-function-declaration -std=c11


Wolfssl_Enclave_C_Objects := $(Wolfssl_Enclave_C_Files:.c=.o)




ifeq ($(SGX_MODE), HW)
ifneq ($(SGX_DEBUG), 1)
ifneq ($(SGX_PRERELEASE), 1)
Build_Mode = HW_RELEASE
endif
endif
endif


.PHONY: all run

ifeq ($(Build_Mode), HW_RELEASE)
all: Wolfssl_Enclave.so
	@echo "Build enclave Wolfssl_Enclave.so [$(Build_Mode)|$(SGX_ARCH)] success!"
	@echo
	@echo "*********************************************************************************************************************************************************"
	@echo "PLEASE NOTE: In this mode, please sign the Wolfssl_Enclave.so first using Two Step Sign mechanism before you run the app to launch and access the enclave."
	@echo "*********************************************************************************************************************************************************"
	@echo

run: all
endif
ifneq ($(Build_Mode), HW_RELEASE)
	@$(CURDIR)/app
	@echo "RUN  =>  app [$(SGX_MODE)|$(SGX_ARCH), OK]"
endif


######## Wolfssl_Enclave Objects ########


trusted/Wolfssl_Enclave_t.o: ./trusted/Wolfssl_Enclave_t.c
	@$(CC) $(Wolfssl_Enclave_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

trusted/%.o: trusted/%.c
	@echo $(CC) $(Wolfssl_Enclave_C_Flags) -c $< -o $@
	@$(CC) $(Wolfssl_Enclave_C_Flags) -c $< -o $@
	@echo "CC  <=  $<"

Wolfssl_Enclave.so: trusted/Wolfssl_Enclave_t.o $(Wolfssl_Enclave_C_Objects)
	@echo $(Wolfssl_Enclave_Link_Flags)@
	@$(CXX) $^ -o $@ $(Wolfssl_Enclave_Link_Flags)
	@echo "LINK =>  $@"

clean:
	@rm -f Wolfssl_Enclave.* trusted/Wolfssl_Enclave_t.*  $(Wolfssl_Enclave_C_Objects)
