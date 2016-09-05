# Set Up Samba in Ubuntu and Mac OS

### Samba allows to share files among different kinds of operating systems.

## 1. Settings for Ubuntu
1) Install Samba
```
$ sudo apt-get install Samba
```

2) Edit configuration file
```
$ sudo vi /etc/samba/smb.conf
```
3) Set workgroup (if you need it)
```
# Change this to the workgroup
  workgroup = WORKGROUP
```

4) Set your shared folders.
```
# My shared folder
[MyShare]
  comment = COMMENTS
  path = /shared/folder/path
  read only = no
  guest ok = yes
```

5) Restart Samba
```
$ /etc/init.d/smbd restart
```

6) Create shared folder
```
$ sudo mkdir /shared/folder/path
```

7) Set the permissions
```
$ sudo chmod 0777 /shared/folder/path
```

## 2. Mac OS
1) Open finder  
2) Menu Go -> Connect to server  (command-k)  
3) Type `smb://<ubuntu-server-ip>`  
4) Connect  
5) Select guest and OK  
6) Now you can access to `/shared/folder/path`  


## Samba require these ports be opened to work properly
```
port type   port no
udp         137
udp         138
tcp         139
tcp         445
```
