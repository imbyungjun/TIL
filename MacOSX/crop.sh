#!/bin/bash
# Usage : ./crop.sh dir
# convert command is included in imagemagick package

for i in $1/*.png ; do
	convert "$i" -crop 650x416+55+53 "${i%.*}"_crop.png
done
