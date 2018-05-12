#!/bin/bash

#Remove existing sources
make clean_srcs

#Genererate ASN.1 C sources
asn1c -fnative-types -fcompound-names -fskeletons-copy interoperability.asn

#Cleanup
make clean
