TARGET:=libcalmmedia.la

VERSION_CURRENT=`cat VERSION|cut -d '.' -f 1`
VERSION_REVISION=`cat VERSION|cut -d '.' -f 2`
VERSION_AGE=`cat VERSION|cut -d '.' -f 3`
VERSION=$(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)

AR:=ar rcs
CC:=gcc
RM:=rm -rf
CP:=cp
LN:=ln -s

LIBTOOL=libtool
LIBTOOL_COMPILE=$(LIBTOOL) --mode=compile $(CC)
LIBTOOL_LINK=$(LIBTOOL) \
	--mode=link $(CC) \
	-version-info $(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)
LIBTOOL_INSTALL=$(LIBTOOL) --mode=install

SRCS:=mininl.c calm.c attr.c
HEADERS:=calm.h mininl.h
OBJS:=${SRCS:.c=.o}
LIBOBJS:=$(SRCS:.c=.lo)

ifdef KERNDIR
 KERNEL_SRC := $(KERNDIR)
else
 KERNEL_SRC := /lib/modules/$(shell uname -r)/build/include
endif

CFLAGS:= -g -Wall -I.. -I/usr/include -I$(KERNEL_SRC) -D_GNU_SOURCE
LDFLAGS = -lpthread

PREFIX:=/usr/local
PREFIX_INC:=$(PREFIX)/include/calm/calmmedia
PREFIX_LIB:=$(PREFIX)/lib

ifdef LIBROOT
 LIBDIR := $(LIBROOT)
else
 LIBDIR := $(PREFIX_LIB)
endif

all: lib

lib: $(LIBOBJS)
	$(LIBTOOL_LINK) -O $(LIBOBJS) $(LDFLAGS) -rpath $(PREFIX_LIB) -o $(TARGET)

%.lo : $(SRCS) $(HEADERS)
	$(foreach SRC,$(SRCS), \
		$(LIBTOOL_COMPILE) $(CFLAGS) -c $(SRC) \
	;)
	
install: lib $(HEADERS)
	$(LIBTOOL_INSTALL) install -c $(TARGET) $(PREFIX_LIB)/$(TARGET)	
	sed -i -e "s#^libdir=.*#libdir='$(LIBDIR)'#" $(PREFIX_LIB)/$(TARGET)
	mkdir -p $(PREFIX_INC)
	$(CP) $(HEADERS) $(PREFIX_INC)

clean :
	$(RM) .libs $(OBJS) $(LIBOBJS) $(TARGET)
	$(RM) *.o *.a *.so.*
.PHONY : clean

## --- only for testing

ifeq ($(__CALM__TEST__),1)
 CFLAGS += -D__CALM__TEST__
endif

calm_objs: $(OBJS)

calmmedia_test:
	$(MAKE) __CALM__TEST__=1 calm_objs
	$(CC) -o libcalmmedia_test $(CFLAGS) $(OBJS) $(LDFLAGS)

mininl_test:
	$(CC) -o mininl_test mininl.c $(CFLAGS) $(LDFLAGS) -D__MININLLIB__TEST__

cckidtest: cckidtest.c
	$(CC) -o cckidtest cckidtest.c -Wall -g -L. -lcalmmedia

