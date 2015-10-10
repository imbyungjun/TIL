#Time Redirection to File
**'time'** command report us how long it took to excute other command

**SYNOPSIS**

	$ time [options] command[arguments...]

We can get report like this

	$ time sleep 1

	real	0m1.006s
	user	0m0.001s
	sys		0m0.002s

If you want to redirection time command's output,
you should use like this...

	$ { time sleep 1; } 2> time.txt
	