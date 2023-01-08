# mysql_exec

Perform shell system calls from MySQL using user defined functions.


## Requirements

OS: Ubuntu 22.04

```
sudo apt install mysql-server libmysqlclient-dev -y
```

**Tested Versions**
|Sofware|Version|
|---|---|
|mysql|8.0.31|
|gcc/g++|11.3.0|

## Build and Install

```
make mysql_exec
sudo cp mysql_exec.so $(mysql_config --variable=plugindir)
systemctl restart mysqld 
```

In mysql as root:

```
CREATE FUNCTION shell_exec RETURNS STRING SONAME "mysql_exec.so";

```

## Warnings

* Disable apparmor for mysql to be able to fork/spawn shell process:
```
sudo ln -s /etc/apparmor.d/usr.sbin.mysqld /etc/apparmor.d/disable/
sudo apparmor_parser -R /etc/apparmor.d/usr.sbin.mysqld
```

To reenable:
```
sudo rm /etc/apparmor.d/disable/usr.sbin.mysqld
sudo apparmor_parser -r /etc/apparmor.d/usr.sbin.mysqld
sudo aa-status
```


* You must allow mysql to make connections (for selinux: https://linux.die.net/man/8/mysqld_selinux)

```
setsebool -P mysql_connect_any 1 
```

* Invoke client with --binary-as-hex=0 to rid hex output



## Usage

* Execute
```
select shell_exec("whoami");
```




## Links

* [Loadble UDF](https://dev.mysql.com/doc/extending-mysql/8.0/en/adding-loadable-function.html)

* [Install MySQL in Ubuntu 22.04](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-22-04)


