PROGRAMS= hash.out

CC=gcc

CFLAGS=--std=c99 -O3

RM=rm -f

.PHONY: all
all: $(PROGRAMS:%=%)

.PHONY: clean
clean:
	-$(RM) $(PROGRAMS:%=%.s) $(PROGRAMS:%=%)

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<
