CC:=$(CROSS_COMPILE)gcc
KERNDIR ?= ../lib/
CFLAGS += -g -I$(KERNDIR)/libfast -I$(KERNDIR)/libcalmfast -I$(KERNDIR) -Wall
LDFLAGS += -Wl,-rpath -Wl,/usr/local/lib -L../lib/ -L/usr/local/lib -lfast -lcalmfast

all: calmd

calmd:	calmd.o
	$(CC) calmd.o -o calmd $(LDFLAGS)
	
