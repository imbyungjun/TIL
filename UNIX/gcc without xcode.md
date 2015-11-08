#Install gcc without xcode in OSX

When we try to use gcc without installing xcode, alert occured.  
There's way to install gcc without xcode.

1 ) Terminal

    $ xcode-select --install
    
2 ) Download it from **Apple's developer site**

Find "Command Line Tools" and download it.


I think it's little bit different with normal gcc. 
When I use gcc without any argument...

	$ gcc
	clang: error: no input files


