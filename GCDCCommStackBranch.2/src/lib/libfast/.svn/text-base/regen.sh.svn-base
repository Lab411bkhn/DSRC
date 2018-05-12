#!/bin/bash

#Remove existing sources
make clean_srcs

#Genererate ASN.1 C sources
asn1c -fnative-types -fcompound-names -fskeletons-copy -gen-PER 29281.asn
rm -f converter-sample.c
rm -f Makefile.am.sample

#Patches for asn1c from Ubuntu package. Please use the latest version from SVN
# (See README file!)
#patch constr_SET_OF.c asn1_patch/constr_SET_OF.c.patch
#patch OCTET_STRING.c asn1_patch/OCTET_STRING.c.patch

#Patch for warning messages
patch NativeInteger.c asn1_patch/NativeInteger.c.patch

#Patch ServiceID. Make it extensible!
patch IpServiceID.c asn1_patch/IpServiceID.c.patch
patch IpServiceID.h asn1_patch/IpServiceID.h.patch
patch ServiceID.c asn1_patch/ServiceID.c.patch
patch ServiceID.h asn1_patch/ServiceID.h.patch

#Cleanup
make clean

#Fix ASN1 function names
./gentags.sh
./convert.py tags

