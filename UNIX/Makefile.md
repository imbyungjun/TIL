#Makefile
###Example
```
CC = gcc
OBJS = server.o client.o
TARGET = 

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(OBJS) $(TARGET)
```	
###1. Macro
We can use macro in *makefile*. We can make complicate commands to simplified commands.

```
OBJS = main.o read.o write.o

test : $(OBJS)
gcc -o trest $(OBJS)
...
```
is same as

```
test : main.o read.o write.o
gcc -o test main.o read.o write.o
```

###* Pre-defined macro
Make has some pre-defined macros.  
**AS** - Program for compling assembly files; default is 'as'.  
**CC** - Program for compling C programs; default is 'cc'.
**CXX** - Program for compling C++ programs; default is 'g++'.  
**CPP** - Program for running the C preprocessor, with results to standard output; default is '$(CC) -E'.  
**RM** - Command to remove a file; default is 'rm -f'.

####Additional arguments for program above.
**ASFLAGS** - Extra flags to give to the assembler when explicitly invoked on a '.s' or '.S' file.  
**CFLAGS** - Extra flags to give to the C compiler.  
**CXXFLAGS** - Extra flags to give to the C++ compiler.  
**CPPFLAGS** - Extra flags to give to the C preprocessor and programs.

#####You can get all informations about pre-defined macro
```
$ make -p
```
###2. Suffix Rule
 It's rule for filename extension.  
`.SUFFIXES : .c .o ` means compile from .c file to .o file.  Make process files that have the extensions in suffix rules.
