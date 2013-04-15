#
#
#
#
#
#
#
#
#
#
#
#
#
#
#

CC		= gcc
CFLAGS		= -Wall -O2 -D_REENTRANT -c -g
LIBS		= -lpthread
AR		= ar r

all:		abuffer.a

strip-teste:	teste
		strip teste

teste:		teste.o abuffer.a
		$(CC) teste.o abuffer.a $(LIBS) -o $@

teste.o:	teste.c abuffer.h
		$(CC) $(CFLAGS) teste.c

abuffer.a:	abuffer.o
		$(AR) abuffer.a abuffer.o

abuffer.o:	abuffer.c abuffer.h
		$(CC) $(CFLAGS) abuffer.c

clean:
		@rm -rf *.o *.a teste
