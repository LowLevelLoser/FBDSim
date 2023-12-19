
CC=tcc
CFLAGS=-Wall -g
BINS=libplus1.so libplus2.so test.elf

all: $(BINS)

%.so: %.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.elf: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(BINS)
	rm -r *.dSYM
