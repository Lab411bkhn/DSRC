#!/bin/bash

# Use this script to update from the online git repositories.

CRDA=crda
CRDA_GIT=git://git.kernel.org/pub/scm/linux/kernel/git/mcgrof/${CRDA}.git

REGDB=wireless-regdb
REGDB_GIT=git://git.kernel.org/pub/scm/linux/kernel/git/linville/${REGDB}.git
RBIN=regulatory.bin

TMP="`pwd`/../wireless"

#
# Update or clone the online git repositories.
#
mkdir -p ${TMP}
pushd ${TMP}

[ -d ${CRDA} ] || git clone ${CRDA_GIT}
(cd ${CRDA}; git checkout -f && git fetch origin && git rebase origin)

[ -d ${REGDB} ] || git clone ${REGDB_GIT}
(cd ${REGDB}; git checkout -f && git fetch origin && git rebase origin)

popd

#
# Copy any updated files.
#
rsync -av --exclude=.git --exclude=.gitignore ${TMP}/${CRDA}/ .
rsync -av ${TMP}/${REGDB}/regulatory.bin ${TMP}/${REGDB}/linville.key.pub.pem .

#
# This step generates the arch independent keys-gcrypt.c.sav which
# you will want to commit if it has changed. It depends on python-m2crypto,
# a universe package, which you (the package maintainer) must have installed.
# Frankly, its quite unlikely that this key will change. 
# You'll also need the other build dependencies listed in debian/control.
#
make clean REG_BIN=`pwd`/${RBIN}
make REG_BIN=`pwd`/${RBIN}
cp keys-gcrypt.c keys-gcrypt.c.sav
