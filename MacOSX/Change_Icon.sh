#!/bin/bash
# This script change the icon of given directory/file.

function usage(){
	echo "Usage: $0 [*.png] [direcotry | file]"
	exit 
}

# main function
if [ $# -lt 2 ] ; then
	usage
fi

# change *.png file's icon as its own image.
sips -i $1	

# Extract the icon to its own resource file
DeRez -only icns $1 > /tmp/tmp.rsrc

# check is it directory
if [ -d $2 ]
then
	# Directory
	# Append a resource
	Rez -append /tmp/tmp.rsrc -o $2/Icon$'\r'

	# Use the resource to set the icon.
	SetFile -a C $2

	# Hide Icon\r
	SetFile -a V $2/Icon$'\r'
else
	# File
	# Append resource to the target file.
	Rez -append /tmp/tmp.rsrc -o $2

	# Set up the icon
	SetFile -a C $2
fi

# Clean up
rm /tmp/tmp.rsrc
