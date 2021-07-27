# This Makefile is set up for CS201 A3
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=gcc
# compile for 32-bit rather than 64-bit
CFLAGS=-O0
DFLAGS=-g
PROGS=fp_parse
LDLIBS=-lm

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(PROGS) *.o ~* 

