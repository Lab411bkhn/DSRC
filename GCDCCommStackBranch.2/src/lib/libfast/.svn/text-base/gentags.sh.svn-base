#!/bin/bash

ctags -f tags *.c
ctags -a -f tags *.h

grep -v "msg.c" tags > tags2
grep -v "msg.h" tags2 > tags
grep -v "mng.c" tags > tags2
grep -v "mng.h" tags2 > tags

rm -f tags2

