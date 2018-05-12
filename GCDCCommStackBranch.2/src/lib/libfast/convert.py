#!/usr/bin/env python

import sys
import os
import re

def usage():
    print "Usage: " + sys.argv[0] + " <tags/file/path>"

if len(sys.argv) < 2:
    usage()
    sys.exit(1)

tagsPath = sys.argv[1]

if not os.access(tagsPath, os.R_OK):
    usage()
    sys.exit(1)

tagsFile = open(tagsPath, "r")

sourcePaths = os.listdir(".")
sourceFiles = []
for sf in sourcePaths:
    sfLen = len(sf)
    ext = sf[sfLen-2:]
    if ext == ".c" or ext == ".h":
        if sf[:3] != "temp":
            sourceFiles.append(sf)

lines = 0
while tagsFile:
    tagLine = tagsFile.readline()
    if len(tagLine) == 0:
        break
    if tagLine[0] == "!":
        continue
    #i = tagLine.find(";\"")
    #tagLine = tagLine[:i]
    tagLineParts = tagLine.partition(";\"")
    tagLine = tagLineParts[0]

    tagExtensions = tagLineParts[2].split("\t")
    type = "-"
    if len(tagExtensions) > 1:
        if len(tagExtensions[1]) > 0:
            type = tagExtensions[1][:1]

    tags = tagLine.split("\t", 2)
    if len(tags) < 3:
        continue
    id = tags[0]
    file = tags[1]
    pattern = tags[2]
    pattern = pattern.replace("\t", "\\t")
    pattern = pattern.replace("\/", "/")
    patternLen = len(pattern)
    try : 
        lineNo = int(pattern)
    except ValueError:
        lineNo = -1
    pattern = pattern[1:patternLen-1]

#    if lineNo > -1:
#        print "+ " + id + " " + file + " at " + str(lineNo)
#    else:
#        print "* " + id + " " + file + " >> " + pattern
#    print "   Type: " + type

    if lineNo > -1:
        continue

    if type != 'f':
#        print "Skip non-function tag: " + id + "(type: " + type + ")"
        continue

    for sf in sourceFiles:
        sfFile = open(sf, "r")
        rawData = sfFile.readlines()
        sfFile.close()

        data = []
        s = 0
        for rawLine in rawData:
            regexpPat = r'([^a-zA-Z0-9_]+)' + id + r'([^a-zA-Z0-9_])'
            line = re.sub(regexpPat,
                    r'\1' + "__LIBFAST__" + id + r'\2',
                    rawLine)

            if rawLine == line:
                regexpPat = r'^' + id + r'([^a-zA-Z0-9_])'
                line = re.sub(regexpPat,
                        "__LIBFAST__" + id + r'\1',
                        rawLine)

            if rawLine != line:
                s += 1
            data.append(line)

        if s == 0:
            continue

        temp = open("temp" + sf, "w")
        temp.writelines(data)
        temp.close()

        os.rename("temp" + sf, sf)

        print "S: %s in %s %d times" % (id, file, s)
    
        lines += 1

print "Substituted ids: " + str(lines)

tagsFile.close()

