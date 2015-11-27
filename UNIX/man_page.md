#Man page
###1. Section
Man pages are divided to sections by program's feature. Each sections have section number.  

Section|Description
:-----:|:---------:
1		| General Commands
2		| System calls
3		| Library functions, covering in particular the C standard library
4		| Special files (devices) and drivers
5		| File formats and conventions 
6		| Games and screensvaers
7		| Miscellanea
8		| System administration commands and daemons
9		| Etc

`section numbers depend on system enviroment.`

###2. Make man page
```
1) .TH  :  Title of man page
2) .SH  :  Section head
3) .PP  :  New paragraph
4) ."   :  Comment
5) .TP  :  For indent
```
1) .TH

```
.TH [ Program_name ] [ Section # ] [ Center footer ] [ Left footer ] [Center header ]
```
2) .SH

```
.SH Title_Is_Here
```
###3. Layout
**NAME**	
 - The name of command or function.  
**SYNOPSIS**  
 - A formal description of how to run it and what command line options it takes.  
**DESCRIPTION**  
 - A textual description of the functioning of the command or function.  
**EXAMPLES**  
 - Some examples of common usage.  
**SEE ALSO**  
 - A list of related commands or functions.