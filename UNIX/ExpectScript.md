#Expect Script
-
**Expect script** is script language that can interact with other program by request and answer.

Basic expect commands

*  send - to send the strigns to the process
*  expect - wait for the specific string from the process
*  spawn - to start the command


**Example Code :**

	#!/usr/bin/expect
	spawn ssh pi@192.168.1.10
	set timeout 5
	
	expect { 
		timeout { puts "Connection Failed"; exit }
		"*assword:" { send "raspberry\r" }
	}
	interact
	

This is my expect script for connect to raspberryPi via ssh.  
I found some easy example codes that can practice expect script.  
**http://www.thegeekstuff.com/2010/10/expect-examples/**
