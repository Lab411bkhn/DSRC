TARGET:=libfast.la

VERSION_CURRENT=`cat VERSION|cut -d '.' -f 1`
VERSION_REVISION=`cat VERSION|cut -d '.' -f 2`
VERSION_AGE=`cat VERSION|cut -d '.' -f 3`
VERSION=$(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)

USRINCLUDE?=/usr/include

AR:=$(CROSS_COMPILE)ar rcs
CC:=$(CROSS_COMPILE)gcc
RM:=rm -rf
CP:=cp
LN:=ln -s

LIBTOOL=$(CROSS_COMPILE)libtool
LIBTOOL_COMPILE=$(LIBTOOL) --tag=CC --mode=compile $(CC)
LIBTOOL_LINK=$(LIBTOOL) \
	--tag=CC --mode=link $(CC) \
	-version-info $(VERSION_CURRENT):$(VERSION_REVISION):$(VERSION_AGE)
LIBTOOL_INSTALL=$(LIBTOOL) --mode=install

ASN_SRCS:= \
	asn_SEQUENCE_OF.c \
	asn_SET_OF.c \
	constr_SEQUENCE.c \
	constr_SEQUENCE_OF.c \
	constr_SET_OF.c \
	OCTET_STRING.c \
	BIT_STRING.c \
	NativeEnumerated.c \
	NativeInteger.c \
	INTEGER.c \
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
	per_opentype.c \
	per_encoder.c
ISO29281_SRCS:= \
	MedType.c	\
	StationID.c	\
	TransportAddressType.c	\
	TransportAddress.c	\
	IpServiceID.c	\
	IpPrefix.c	\
	IpPrefixList.c	\
	ServiceChannel.c	\
	IpAddressInfo.c	\
	IpInfo.c	\
	IpContextData.c	\
	IpServiceData.c	\
	IpContext.c	\
	IpService.c	\
	ServiceID.c	\
	NWref.c	\
	ContextData.c	\
	ServiceData.c	\
	FastContext.c	\
	FastService.c	\
	MessageType.c	\
	ServiceList.c	\
	ChannelList.c	\
	IpServList.c	\
	ServContextList.c	\
	IpContextList.c	\
	Sta.c \
	Stc.c \
	Request.c \
	Response.c
ASN_PATCH_SRCS:= \
	ExtensibleInteger.c 
LIB_SRCS:= \
	msg.c \
	mng.c
SRCS:=$(ASN_SRCS) $(ISO29281_SRCS) $(LIB_SRCS) $(ASN_PATCH_SRCS)
ASN_HDRS:= \
	asn_SEQUENCE_OF.h \
	asn_SET_OF.h \
	constr_SEQUENCE.h \
	constr_SEQUENCE_OF.h \
	constr_SET_OF.h \
	OCTET_STRING.h \
	BIT_STRING.h \
	NativeEnumerated.h \
	NativeInteger.h \
	INTEGER.h \
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
	per_opentype.h \
	per_encoder.h
ISO29281_HDRS:= \
	MedType.h	\
	StationID.h	\
	TransportAddressType.h	\
	TransportAddress.h	\
	IpServiceID.h	\
	IpPrefix.h	\
	IpPrefixList.h	\
	ServiceChannel.h	\
	IpAddressInfo.h	\
	IpInfo.h	\
	IpContextData.h	\
	IpServiceData.h	\
	IpContext.h	\
	IpService.h	\
	ServiceID.h	\
	NWref.h	\
	ContextData.h	\
	ServiceData.h	\
	FastContext.h	\
	FastService.h	\
	MessageType.h	\
	ServiceList.h	\
	ChannelList.h	\
	IpServList.h	\
	ServContextList.h	\
	IpContextList.h	\
	Sta.h \
	Stc.h \
	Request.h \
	Response.h
ASN_PATCH_HDRS:= \
	ExtensibleInteger.h 
LIB_HDRS:= \
	msg.h \
	mng.h
HDRS:= $(ASN_HDRS) $(ISO29281_HDRS) $(LIB_HDRS) $(ASN_PATCH_HDRS)
OBJS:=${SRCS:.c=.o}
LIBOBJS:=$(SRCS:.c=.lo)

ifdef KERNDIR
 KERNEL_SRC := $(KERNDIR)
else
 KERNEL_SRC := /lib/modules/$(shell uname -r)/build/include
endif

CFLAGS:= -g -Wall -I.. -I$(USRINCLUDE) -I$(KERNEL_SRC) -I$(USRINCLUDE)/libxml2 -I. \
		 -D__LIBFAST_COMPILE__ -DDISABLE_STC_DATA_RESTRICTION
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

%.lo : $(SRCS) $(HDRS)
	$(foreach SRC,$(SRCS), \
		$(LIBTOOL_COMPILE) $(CFLAGS) -c $(SRC) \
	;)
	
install: lib $(HDRS)
	$(LIBTOOL_INSTALL) install -c $(TARGET) $(PREFIX_LIB)/$(TARGET)	
	sed -i -e "s#^libdir=.*#libdir='$(LIBDIR)'#" $(PREFIX_LIB)/$(TARGET)
	mkdir -p $(PREFIX_INC)
	$(CP) $(LIB_HDRS) $(PREFIX_INC)

clean :
	$(RM) .libs $(OBJS) $(LIBOBJS) $(TARGET)
	$(RM) *.o *.a *.so.* fastmsg
.PHONY : clean

debug: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o fastmsg $(SRCS) -DLIBFAST_DEBUG -DLIBFAST_TEST -DEMIT_ASN_DEBUG=1

test: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o fastmsg $(SRCS) -DLIBFAST_TEST

clean_srcs: 
	$(RM) $(ASN_SRCS) $(ISO29281_SRCS)
	$(RM) $(ASN_HDRS) $(ISO29281_HDRS)
.PHONY : clean_srcs

