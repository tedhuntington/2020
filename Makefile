LINUX_DIR = /usr/src/linux

CC=gcc
MAKE=make
OSFLAG=-DLinux
RELEASE = $(shell uname -r)
MODULE_INC=-I$(LINUX_DIR)/include
#MODULE_OPT = -O3
#MODULE_OPT_WARN =  -Wall -Wstrict-prototypes -fomit-frame-pointer  -pipe
CFLAGS = -g -O2 -fomit-frame-pointer -ffast-math -mpreferred-stack-boundary=4 $(MODULE_INC) $(OSFLAG)
LIBDIRS = -L/usr/lib/x86_64-linux-gnu -L/usr/X11R6/lib 
LIBS = -lX11

#CFLAGS = -mpreferred-stack-boundary=2 $(MODULE_INC) $(OSFLAG)

SRCS=path.c 2020.c desc.c bit.c lang.c lang2.c
OBJS=path.o 2020.o desc.o bit.o lang.o lang2.o
EXE=2020
EVENTSRCS=Event.c
EVENTOBJS=Event.o
EVENT=Eventl
CHARSRCS=path.c char.c
CHAROBJS=path.o char.o
CHAR=char

all:	
	@echo  \#include \<stdlib\.h\> \\n\
	\#include \<string\.h\> \\n \\n\
	\#include \<stddef\.h\> \\n \\n\
	char *PATH\; \\n\
	set2020path\(\) \\n\
	\{PATH\=malloc\(256\)\;  strcpy\(PATH\,\"`pwd`\"\)\;\}>path.c; 
	$(MAKE) CH20 

less:
	@echo  char *PATH\; \\n \
	set2020path\(\) \\n \
	\{PATH\=malloc\(256\)\;  strcpy\(PATH\,\"`pwd`\"\)\;\}>path.c;
	$(MAKE) "CFLAGS=-O2 -mpentium -fomit-frame-pointer -ffast-math -mpreferred-stack-boundary=2 $(MODULE_INC) $(OSFLAG) -DFILL" CH20 

CH20:	$(EXE) $(CHAR)

install: 
	@if test -f /usr/local/bin/2020; then \
		rm -f /usr/local/bin/2020; \
	fi; \
	ln -s `pwd`/2020 /usr/local/bin/2020

event: $(EVENT)

#char: $(CHAR)

clean:
	rm *.o -f

$(EXE):	$(OBJS)
	$(CC) $(CFLAGS) $(LIBDIRS) -o $(EXE) $(OBJS) $(LIBS)

$(EXE2): $(OBJS)
	 $(CC) -DFILL $(CFLAGS) $(LIBDIRS) -o $(EXE) $(OBJS) $(LIBS)

$(EVENT): $(EVENTOBJS)
	$(CC) -o $(EVENT) $(EVENTOBJS)

$(CHAR): $(CHAROBJS)
	$(CC) $(CFLAGS) $(LIBDIRS) -o $(CHAR) $(CHAROBJS) $(LIBS)

.c.o:	$(SRCS) $(EVENTSRCS) 
	$(CC) -c $(CFLAGS) $*.c

