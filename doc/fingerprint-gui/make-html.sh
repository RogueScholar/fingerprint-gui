#!/bin/bash

# simple script to make new html-files from xml

XML=`ls *.xml`
echo $XML
rm *.html

for WHAT in $XML ; do
xmlto html-nochunks $WHAT
done

