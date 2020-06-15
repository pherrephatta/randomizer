# Raspberry Pi

- [GPIO Access](#gpio-access)
- [Arch Linux ARM Installation](#arch-linux-arm-installation)
- [Programs and Tools](#programs)
- [File Sharing with Samba](#file-sharing-with-samba)
- [Install Apache](#install-apache)
- [Install Lighttpd](#install-lighttpd)
- [Install MariaDB](#setup-mariadb)
- [Install PHP](#install-php)
- [Install Adminer](#install-adminer)
- [Install phpMyAdmin](#install-phpmyadmin)
- [Pin Guide](https://roboticsbackend.com/raspberry-pi-3-pins/)
- [Interfaces Guide](https://www.seeedstudio.com/blog/2019/09/25/uart-vs-i2c-vs-spi-communication-protocols-and-uses/)

## GPIO Access

```
// `gpio readall`
+-----+-----+---------+------+---+-Model B1-+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
 |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
 |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | ALT0 | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | ALT0 | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+-Model B1-+---+------+---------+-----+-----+
```

**Architecture**: ARMv6
**Processor**: Broadcom BCM2835 700MHz
**RAM**: 512MB
**Ethernet**: 10/100

### sys/class 

```
su
cd /sys/class/gpio
echo 27 > export 
cd gpio27
echo out > direction
echo 1 > value
```

### WiringPi
1. Setup wiringPi
- `wiringPiSetup(void)` for wiringPi number scheme [0,16], run with root
- `wiringPiSetupGpio(void)` for Broadcom GPIO pin numbering, run with root
- `wiringPiSetupPhys(void)` for physical pin numbering, works on P1 connector only, with root
- `wiringPiSetupSys(void)` for Broadcom numbering, works without root but pins must be exported first 
2. Other functions
- `pinMode(int pin_nb, [INPUT|OUTPUT])`
- `delay(int time_ms)`
- `digitalRead(int pin_nb)`
- `analogRead(int pin_nb)`
- `digitalWrite(int pin_nb, [LOW|HIGH])`
- `analogWrite(int pin_nb, int value)` 

## Arch Linux ARM Installation
1. `fdisk /dev/sdX` (or use cfdisk for tui)
	- type `o` to delete partition
	- type `p` to list partitions`
	- type `n` for new, `p` for primary, `1` for first partition, `ENTER` to accept start byte, `+100M` for last byte.
	- type `t` for type, `c` to set to `W95 FAT32 (LBA)`
	- type `n`, `p`, `2`, `ENTER` twice
	- type `w` to write and exit
2. Create the Filesystem
	- `mkfs.vfat -F32 /dev/sdX1` 
	- `mkfs.ext4 -F /dev/sdX2`
3. Download Arch
	- `wget http://os.archlinuxarm.org/os/ArchLinuxARM-rpi-latest.tar.gz`
	- `sudo tar -xf [file] -C [location]`
4. Mount Partitions and Move File
	- `sudo mkdir -p [location]/{boot, root}`
	- `sudo mount /dev/sdX1 [location]/boot`
	- `sudo mount /dev/sdX2 [location]/root`
	- `sudo mv [location]/root/boot/* [location]/boot/` 
	- `sudo umount -R [location]/boot [location]/root`
5. Boot and Set Pacman Keyring
	- log in with `root::root`
	- `pacman-key --init`
	- `pacman-key --populate archlinuxarm`
	- `pacman -Syu sudo vim` to update and install `sudo`
	- `EDITOR=vim visudo` to configure `sudo` by uncommenting chosen group.
	- `usermod -aG [chosen group] alarm`
	- reboot and log in as `alarm::alarm`
6. Adjust Boot Options (as root)
	- add needed properties to `/boot/config.txt`
	- _Display Properties_: hdmi_drive, hdmi_forcehotplus, hdmi_mode, cofig_hdmi_boost, hdmi_group, hdmi_safe, overscan_[left|right|top|bottom], disable_overscan, sdtv_mode, sdtv_aspect
	- _Performace and Overclocking_: arm_freq, gnu_freq, core_freq, h264_freq, isp_freq, v3d_freq
	- _Voltage Control_: over_voltage, over_voltage_sdram, over_voltage_sdram_c, over_voltage_sdram_i

## Programs
python, gcc, gpio-utils, wiringpi

### Tools
_groups_: `usermod`, `groups`, `id`, `passwd`, `getent`, `/etc/shadow`, `/etc/passwd`
_logging_: `journalctl`, `dmesg`
_memory_: `watch grep -e Dirty -e Writeback /proc/meminfo`
_network_: `iface`, `inet`, `networkctl`, `ifconfig`, `ip`, `route`, `hostnamectl`, `/etc/resolv.conf`, `/etc/dhcpcd.conf`, `/etc/host.conf`

### SSH
Verify that `sshd` is running with the command `sudo systemctl status sshd.service`.

## File Sharing with Samba
_Tools_: `testparm`, `smbclient -L [server]`, `pbdedit -L -v`, `smbtree -b -N`, 
	`nmap -p 139 -sT "[ADDR]"`, `nmblookup -A [ADDR]`
1. To Install
- Main configuration file is `/etc/samba/smb.conf` but it isn't present by default, it has to be copied from the git repository.
- Each [value] represents a share. `[home]` can be used to share unix account home directories by default. 
- Use options `read only = no` and `writable = yes` to allow modification of file system from remote.
- add a new user with `sudo smbpasswd -a [user]`
- if a firewall is present, open ports 137,138,139,445
- change log location to a writable one, e.g. `log file = /var/log/samba/%m.log`, or use `logging = systemd`
- start with `sudo systemctl [start|restart|enable] smb.service`
2. To Connect
2.1. use command `smbclient //[server]/[share] -U [user]%[pass]`
2.2. mount to client from server with `sudo mount -t cifs //[server]/[share] /[mount] -o username=[user],password=[pass],workgroup=[wg]`; username and password options can be given through a credential file, such as the one below; this file should explicitely be R/W to root

```
// file at /etc/samba/credentials/share
username=user
password=mypass
```

3. Options
- to disable shell for a user, `usermod --shell /user/bin/nologin --lock [user]`
- to disable ssh, edit `/etc/ssh/sshd_config` and change `AllowUsers` option

_Note_ the default workgroup name for Windows is `WORKGROUP.`

## Install Apache
_Tools_: `apachectl configtest`, `httpd -t`
_See also_: `Xampp`
- `pacman -S apache`
- edit `/etc/httpd/conf/httpd.conf` file
- comment out the following line `#LoadModule unique_id_module modules/mod_unique_id.so`(?)
- `systemctl enable httpd`
- `systemctl restart httpd`
- `systemctl status httpd`

- create a dummy index at `/srv/http/index.html`
- open with `http://localhost`

## Install Lighttpd
Alternative to Apache
- `pacman -Sy lighttpd`
- configuration file is `/etc/lighttpd/lighttpd.conf`
- verify configuration with `lighttpd -[t|tt] -f /etc/lighttpd/lighttpd.conf` 
- configuration files are available in `/usr/share/doc/lighttpd/`
- enable logging by adding below settings to `lighttpd.conf`
```
server.modules += (
   "mod_access",
   "mod_accesslog",
)

server.errorlog   = "/var/log/lighttpd/error.log"
accesslog.filename = "/var/log/lighttpd/access.log"
```

- http and php can be served from localhost through `/srv/http/`
- to enable phpmyadmin, add `alias.url = ( "/phpmyadmin" => "/usr/share/webapps/phpmyadmin/")`
- in the same file, if not already present, add `server.modules += ( "mod_alias" )`


## Install MariaDB
_Note_: `mariadb` could be `mysqld`
- `mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql`

```
// Sample Output
Two all-privilege accounts were created.
One is root@localhost, it has no password, but you need to
be system 'root' user to connect. Use, for example, sudo mysql
The second is mysql@localhost, it has no password either, but
you need to be the system 'mysql' user to connect.
After connecting you can set the password, if you would need to be
able to connect as any of these users with a password and without sudo

See the MariaDB Knowledgebase at http://mariadb.com/kb or the
MySQL manual for more instructions.

You can start the MariaDB daemon with:
cd '/usr' ; /usr/bin/mysqld_safe --datadir='/var/lib/mysql'

You can test the MariaDB daemon with mysql-test-run.pl
cd '/usr/mysql-test' ; perl mysql-test-run.pl
```

- `systemctl enable mysqld`
- `systemctl start mysqld`
- `systemctl status mysqld`
- `mysql_secure_installation`
- `mysql -u root -p`
```
create database $your_db default character set utf8 default collate utf8_bin;
create user $your_user@'localhost' IDENTIFIED BY '$your_user';
GRANT ALL PRIVILEGES ON $your_db.* to $your_user@'localhost' IDENTIFIED BY '$your_user';
FLUSH PRIVILEGES;
quit
```
- data directory is `/var/lib/mysql`
- config files are read in this order `/etc/my.cnf`, `/etc/my.cnf.d/`, `~/.my.cnf`

```
// MariaDB commands
SHOW DATABASES;																// Show all databases
USE msql; SHOW TABLES;														// Show all mysql table
DESCRIBE tbl_name [col_name|wild];											// Info about columns in table
SELECT user FROM mysql.user;											// Show all users
SHOW [COLUMNS|FIELDS] FROM tbl_name [FROM db_name];							// Show all columns in table
UPDATE user SET Password=PASSWORD('my_password') where USER='root';			// Change password
CREATE USER 'monty'@'localhost' IDENTIFIED BY 'some_pass';					// Create new user
GRANT ALL PRIVILEGES ON mydb.* TO 'monty'@'localhost';						// Change user rights
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
DROP USER 'root'@'localhost';												// Delete user
FLUSH PRIVILEGES;															// Reload grant tables
```

## Install PHP
- `pacman -S php php-apache`
- edit `/etc/httpd/conf/httpd.conf`
- comment out the following `#LoadModule mpm_event_module modules/mod_mpm_event.so`
- uncomment `LoadModule mpm_prefork_module modules/mod_mpm_prefork.so` and `LoadModule rewrite_module modules/mod_rewrite.so`
- add the following lines
```
	LoadModule php7_module modules/libphp7.so
	AddHandler php7-script php
	Include conf/extra/php7_module.conf
```
- create a `test.php` file in `/srv/http/test.php` with the following
```
	<?php
	phpinfo();
	?>
```
- restart with `systemctl restart httpd`
- open `http://ip-address/test.php`

## Install Adminer
- Download and install `adminer` from the AUR.
- The program will be installed under `/usr/share/webapps/adminer/index.php`
- Ensure that `extension=pdo_mysql` is uncommented in `/etc/php/php.ini`
- Add `Include conf/extra/httpd-adminer.conf` to `/etc/httpd/conf/httpd.conf`

## Install phpMyAdmin
- `pacman -S phpmyadmin`
- edit `/etc/php/php.ini`
- uncomment the following lines
```
	extension=bz2.so
	extension=mcrypt.so
	extension=mysqli.so
```
- `sudo vim /etc/httpd/conf/extra/phpmyadmin.conf` and add the following lines
```
	Alias /phpmyadmin "/usr/share/webapps/phpMyAdmin"
	<Directory "/usr/share/webapps/phpMyAdmin">
		DirectoryIndex index.php
		AllowOverride All
		Options FollowSymlinks
		Require all granted
	</Directory>
```
- In the same file, modify `open_basedir` to contain paths ex. `open_basedir = /srv/http/:/var/www/:/tmp/:/usr/share/webapps/:/etc/webapps`
- open `/etc/httpd/conf/httpd.conf` and add `Include conf/extra/phpmyadmin.conf`
- `systemctl restart httpd`
- test on `http://IP-Address/phpmyadmin`
