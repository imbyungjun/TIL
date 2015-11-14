#Install the 'tree' command 	on Mac
###1. Download the source code and unzip

```
$ curl -O ftp://mama.indstate.edu/linux/tree/tree-1.7.0.tgz
$ tar xzvf tree-1.7.0.tgz	
```

###2. Edit 'Makefile' to fit in Mac OS

```
$ vi Makefile

```

####1 ) Comment following lines
```
# Linux defaults:
CFLAGS=-ggdb -Wall -DLINUX -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#CFLAGS=-O4 -Wall  -DLINUX -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#LDFLAGS=-s
```
####2 ) Uncomment these liens
```
# Uncomment for OS X:
CC=cc
CFLAGS=-O2 -Wall -fomit-frame-pointer -no-cpp-precomp
LDFLAGS=
MANDIR=/usr/share/man/man1
OBJS+=strverscmp.o
```
###3. Install
```
$ sudo make install
Password:
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o tree.o tree.c
tree.c:1250:87: warning: format specifies type 'long' but the argument has type
      'long long' [-Wformat]
  ...== sizeof(long long)? " %11lld" : " %9ld", (long long int)size);
                                         ~~~~   ^~~~~~~~~~~~~~~~~~~
                                         %9lld
/usr/include/secure/_stdio.h:47:56: note: expanded from macro 'sprintf'
  __builtin___sprintf_chk (str, 0, __darwin_obsz(str), __VA_ARGS__)
                                                       ^
1 warning generated.
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o unix.o unix.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o html.o html.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o xml.o xml.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o json.o json.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o hash.o hash.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o color.o color.c
cc -O2 -Wall -fomit-frame-pointer -no-cpp-precomp -c -o strverscmp.o strverscmp.c
cc  -o tree tree.o unix.o html.o xml.o json.o hash.o color.o strverscmp.o
install -d /usr/bin
install: chmod 755 /usr/bin: Operation not permitted
install -d /usr/share/man/man1
if [ -e tree ]; then \
		install tree /usr/bin/tree; \
	fi
install: /usr/bin/tree: Operation not permitted
make: *** [install] Error 71
```
#####It occurs error but, you can find excutable binary file 'tree' in current directory.  
#####Move 'tree' file to appropriate PATH.

```
$ mv tree ~/bin
```