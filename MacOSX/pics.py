#!/usr/bin/python
#-*-coding:utf-8-*-

from subprocess import Popen, PIPE
from sys import argv
from getopt import getopt
import re
import os

# file extension
EXT = ['.jpg', '.jpeg', '.CR2']
	
	
# Photo class
class Photo :
	def __init__(self, name):
		self.name = name
		self.date = get_date(name)

# Print usage
def usage():
	print 'usage: pics <folder>'
	exit(1)

# Get given picture's create date 
# from external command line tool's output
# and return create date 
def get_date(pic_name):
	# get result
	# sample.jpg -> argv[1] 
	pipe1 = Popen(['exiftool', pic_name], stdout=PIPE, 
												stderr=PIPE)
	pipe2 = Popen(['grep', '-m', '1', 'Create Date'], stdin=pipe1.stdout, 
												stdout=PIPE,
												stderr=PIPE)
	
	out , err = pipe2.communicate()

	# get date from result
	date_form = re.compile('\d+')
	return date_form.findall(out)

def pics():
	# argv check
	if len(argv) < 2 :
		usage()
	
	# change cwd
	os.chdir(argv[1])

	# Photo objects list initialize
	photos = []

	# get all file names in current directory
	# ends with jpg, jpeg and png
	for file_name in os.listdir('.'):
		if file_name.endswith(tuple(EXT)):
			photos.append(Photo(file_name))

	for photo in sorted(photos, key=lambda x: x.date):
		print photo.name, photo.date

		if len(photo.date) is 0:
			print 'Date info error'
			continue

		path = str(photo.date[0]) + '.' + \
				str(photo.date[1]) + '.' + \
				str(photo.date[2])
		
		try:
			os.mkdir(path)
			print 'Create directory ' + path
		except:
			pass
		# move files in each directory
		print 'change from ' + photo.name + ' to ' + path+'/'+photo.name
		os.rename(photo.name, path+'/'+photo.name)


if __name__ == '__main__':
	pics()
