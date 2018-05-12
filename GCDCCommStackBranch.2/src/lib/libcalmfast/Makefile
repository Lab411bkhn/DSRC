TARGET:=libcalmfast.la

VERSION_CURRENT=`cat VERSION|cut -d '.' -f 1`
VERSION_REVISION=`cat VERSION|cut -d '.' -f 2`
VERSION_AGE=`cat VERSION|cut -d '.' -f 3`
VERSION=$(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)

AR:=$(CROSS_COMPILE)ar rcs
CC:=$(CROSS_COMPILE)gcc
RM:=rm -rf
CP:=cp
LN:=ln -s

USRINCLUDE ?= /usr/include

LIBTOOL=$(CROSS_COMPILE)libtool
LIBTOOL_COMPILE=$(LIBTOOL) --tag=CC --mode=compile $(CC)
LIBTOOL_LINK=$(LIBTOOL) \
	--tag=CC --mode=link $(CC) \
	-version-info $(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)
LIBTOOL_INSTALL=$(LIBTOOL) --mode=install

ASN_SRCS:= \
	INTEGER.c \
	NativeEnumerated.c \
	NativeInteger.c \
	constr_CHOICE.c \
	constr_SEQUENCE.c \
	OCTET_STRING.c \
	BIT_STRING.c \
	asn_codecs_prim.c \
	ber_tlv_length.c \
	ber_tlv_tag.c \
	ber_decoder.c \
	der_encoder.c \
	constr_TYPE.c \
	constraints.c \
	xer_support.c \
	xer_decoder.c \
	xer_encoder.c \
	per_support.c \
	per_decoder.c \
	per_encoder.c \
	per_opentype.c

API_SRCS:= \
	SendRequest.c \
	RequestMessage.c \
	ReplyMessage.c \
	PublishRequest.c \
	EmptyRequest.c \
	OpenRequest.c \
	UrlString.c \
	OpenReply.c \
	MsgReply.c \
	CloseReply.c \
	FaultReply.c \
	ByteString.c

LIB_SRCS:= \
	calmfast.c

SRCS:=$(ASN_SRCS) $(API_SRCS) $(LIB_SRCS)

ASN_HDRS:= \
	INTEGER.h \
	NativeEnumerated.h \
	NativeInteger.h \
	constr_CHOICE.h \
	constr_SEQUENCE.h \
	asn_system.h \
	asn_application.h \
	asn_codecs.h \
	asn_internal.h \
	OCTET_STRING.h \
	BIT_STRING.h \
	asn_codecs_prim.h \
	ber_tlv_length.h \
	ber_tlv_tag.h \
	ber_decoder.h \
	der_encoder.h \
	constr_TYPE.h \
	constraints.h \
	xer_support.h \
	xer_decoder.h \
	xer_encoder.h \
	per_support.h \
	per_decoder.h \
	per_encoder.h \
	per_opentype.h

API_HDRS:= \
	SendRequest.h \
	RequestMessage.h \
	ReplyMessage.h \
	PublishRequest.h \
	EmptyRequest.h \
	OpenRequest.h \
	UrlString.h \
	OpenReply.h \
	MsgReply.h \
	CloseReply.h \
	FaultReply.h \
	ByteString.h

LIB_HDRS:= \
	calmfast.h
HDRS:= $(ASN_HDRS) $(API_HDRS) $(LIB_HDRS)
OBJS:=${SRCS:.c=.o}
LIBOBJS:=$(SRCS:.c=.lo)

ifdef KERNDIR
 KERNEL_SRC := $(KERNDIR)
else
 KERNEL_SRC := /lib/modules/$(shell uname -r)/build/include
endif

CFLAGS:= -g -Wall -I$(USRINCLUDE) -I$(KERNEL_SRC) -I/usr/include/libxml2 -I. \
		 -D__LIBCALMFAST_COMPILE__ -DDISABLE_STC_DATA_RESTRICTION
LDFLAGS:=-lpthread

PREFIX:=/usr/local
PREFIX_INC:=$(PREFIX)/include/calm/fast
PREFIX_LIB:=$(PREFIX)/lib

ifdef LIBROOT
 LIBDIR := $(LIBROOT)
else
 LIBDIR := $(PREFIX_LIB)
endif
  
all: lib

lib: $(LIBOBJS)
	$(LIBTOOL_LINK) -O $(LIBOBJS) $(LDFLAGS) -rpath $(PREFIX_LIB) -o $(TARGET)

%.lo : %.c
	$(LIBTOOL_COMPILE) $(CFLAGS) -c $< -o $@
	
install: lib $(HDRS)
	$(LIBTOOL_INSTALL) install -c $(TARGET) $(PREFIX_LIB)/$(TARGET)	
	sed -i -e "s#^libdir=.*#libdir='$(LIBDIR)'#" $(PREFIX_LIB)/$(TARGET)
	mkdir -p $(PREFIX_INC)
	$(CP) $(LIB_HDRS) $(PREFIX_INC)

clean :
	$(RM) .libs $(OBJS) $(LIBOBJS) $(TARGET)
	$(RM) *.o *.a *.so.* calmfasttest
.PHONY : clean

debug: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o calmfasttest $(SRCS) -DLIBCALMFAST_DEBUG -DLIBCALMFAST_TEST -DEMIT_ASN_DEBUG=1

test: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o calmfasttest $(SRCS) -DLIBCALMFAST_TEST

clean_srcs: 
	$(RM) $(ASN_SRCS) $(API_SRCS)
	$(RM) $(ASN_HDRS) $(API_HDRS)
.PHONY : clean_srcs

