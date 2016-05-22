#Hang Up On Exit.

Many people use Linux via terminal. And sometimes it border us because when we logout from the shell, 
all processes we excuted in background or foreground are kill by default. This is because the hang up signal. When process got hang up signal, process shuts itself down.

But there's the way to continue our long job when we logout, or terminate controlling terminal.

***nohup*** command allow us to ignore hang up signal.

	$ nohup ./a.out
	
But, recent Linux unset huponexit option, so people can continue their jobs when they exit their terminal.

If you want to check your Linux's huponexit option,

	$ shopt | grep huponexit
	
then, you can get value off or on

And if you want to set or unset your huponexit oprtion,

	$ shopt -s huponexit	#set hang up on exit
	$ shopt -u huponexit	#unset hang up on exit
