TARGET:=libcam.la

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
	constr_CHOICE.c \
	per_decoder.c \
	per_encoder.c \
	per_opentype.c \
	per_support.c \
	xer_decoder.c \
	xer_encoder.c \
	xer_support.c

CAM_SRCS:= \
	AccelerationControl.c \
	CamHeader.c \
	CamPayload.c \
	CamTaggedList.c \
	CooperativeAwarenessMessage.c \
	Elevation.c \
	ExteriorLights.c \
	Heading.c \
	IncompleteCovarianceMatrix.c \
	LatitudePosition.c \
	LongitudePosition.c \
	LongitudinalAcceleration.c \
	NearestRsu.c \
	NodeID.c \
	NodeType.c \
	Position2D.c \
	PositionCovariance.c \
	PositionVariance.c \
	Priority.c \
	RsuCamPayload.c \
	SpeedModule.c \
	Temperature.c \
	Timestamp.c \
	VehicleAttribute.c \
	VehicleCamPayload.c \
	VehicleDescription.c \
	VehicleHeight.c \
	VehicleLength.c \
	VehicleSize.c \
	VehicleType.c \
	VehicleWidth.c \
	VisibilityRange.c \
	Weather.c \
	YawRate.c
LIB_SRCS:= \
	cam.c
SRCS:=$(ASN_SRCS) $(CAM_SRCS) $(LIB_SRCS)

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
	constraints.h
CAM_HDRS:= \
	CooperativeAwarenessMessage.h
LIB_HDRS:= \
	cam.h
HDRS:= $(ASN_HDRS) $(CAM_HDRS) $(LIB_HDRS)
OBJS:=${SRCS:.c=.o}
LIBOBJS:=$(SRCS:.c=.lo)

ifdef KERNDIR
 KERNEL_SRC := $(KERNDIR)
else
 KERNEL_SRC := /lib/modules/$(shell uname -r)/build/include
endif

CFLAGS:= -g -Wall -I.. -I/usr/include -I$(KERNEL_SRC) -I/usr/include/libxml2 -I. \
		 -D__LIBCAM_COMPILE__ -DDISABLE_STC_DATA_RESTRICTION
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
	$(RM) *.o *.a *.so.* camtest
.PHONY : clean

debug: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o camtest $(SRCS) -DLIBCAM_DEBUG -DLIBCAM_TEST -DEMIT_ASN_DEBUG=1

test: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o camtest $(SRCS) -DLIBCAM_TEST

clean_srcs: 
	$(RM) $(ASN_SRCS) $(CAM_SRCS)
	$(RM) $(ASN_HDRS) $(CAM_HDRS)
.PHONY : clean_srcs

