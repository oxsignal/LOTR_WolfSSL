UNTRUSTED_DIR = untrusted

all:
	$(MAKE) -C $(UNTRUSTED_DIR) all

clean:
	$(MAKE) -C $(UNTRUSTED_DIR) clean
