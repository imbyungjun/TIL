#MySQL Basic Commands
###1. Show databases
```
mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
4 rows in set (0.00 sec)
```
###2. Create databases
```
mysql> CREATE DATABASE db_name;
```
###3. Add user
```
mysql> CREATE USER 'user_name'@'localhost' IDENTIFIED BY 'passwd';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'user_name'@'localhost' 
	->	WITH GRANT OPTION;
	
mysql> CREATE USER 'user_name'@'%' IDENTIFIED BY 'passwd';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'user_name'@'%'
	->	WITH GRANT OPTION;
	
mysql> CREATE USER 'admin'@'localhost' IDENTIFIED BY 'admin_passwd'
mysql> GRANT RELOAD, PROCESS ON *.* TO 'admin'@'localhost';

mysql> CREATE USER 'dummy'@'localhost';
```

###4. Grant to specific databases
```
mysql> CREATE USER 'user_name'@'localhost' IDENTIFIED BY 'passwd';
mysql> GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP
	->	ON bankaccount.*
	->	TO 'user_name'@'localhost';	
```

###5. See privileges for a user
```
mysql> SHOW GRANTS FOR 'user_name'@'localhost';
```
[Go to mysql manual page](http://dev.mysql.com/doc/refman/5.7/en/adding-users.html)