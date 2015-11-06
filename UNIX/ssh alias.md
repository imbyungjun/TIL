#SSH Alias
-
<big>Remembering the server address, port, user and password can be hard - but it doesn’t have to be.</big>

	$ ssh -p [portnum] username@server.com

There is better way.

	~/.ssh/config
	
Within this file you can define the hostname, user and port of a server and associate it to a short name.

	Host pi
		hostname 192.168.1.2
		user pi
		
Now you connect like this

	$ ssh pi
		
This setting also applies to scp

	$ scp test pi:~/