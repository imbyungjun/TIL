#MySQL install and initialize
###1. Environment
* OS X 10.11.1 (El Capitan)
* mysql-5.7.9-osx10.9-x86_64

###2. Install
* [Get newest version of MySQL](http://dev.mysql.com/downloads/mysql/)
* Download DMG Archive version.
* And Just open and click 'OK'
* After installation is finished, it will alert default password.
 
###3. Initialize
* First, include mysql binaries in PATH.  
  Open ~/.bash_profile and add this line.
  
	```
PATH = $PATH:/usr/local/mysql/bin
	```

* To change 'root' password, open mysql -u option.  
  Then, enter the default password that we got from install step.
  
	```
$ mysql -u root -p
Enter password: 
	```
* You can use mysql after change your 'root' password. So you must change your 'root' password.

	```
mysql> ALTER USER 'root'@'%' IDENTIFIED BY 'new_passwd';
	```
	
#If you forgot password
###1. Stop MySQL
```
sudo /usr/local/mysql/support0files/mysql.server stop
```
###2. Start mysql in safe mode
```
sudo mysqld_safe --skip-grant-tables
```
###3. Open another terminal window, log in without password
```
$ mysql -u root
```
###4. Update your root user's password
```
mysql> UPDATE user SET authentication_string=PASSWORD('new_passwd') WEHRE user='root';
```
###5. Save and quit
```
mysql> FLUSH PRIVILEGES;
mysql> exit;
```