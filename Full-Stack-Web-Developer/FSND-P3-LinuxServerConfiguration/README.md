# Linux Server Configuration Project
To access the application, open your browser and go to `http://<server_ip>.xip.io/`.

To access the server on Amazon Lightsail,
```
ssh -i <path/to/the/private-key> grader@<server_ip> -p 2200
```
where the `server_ip` is `54.238.193.209`.

## Changes of Configuration
### User Management
To add a new user named `grader` as a sudoer,
```
sudo adduser grader  # with password the same as the username
sudo vim /etc/sudoers.d/grader  # and configured it as follows.
```
```
# User rules for grader
grader ALL=(ALL) NOPASSWD:ALL
```
For ssh login as `grader` with a ssh key,
```
sudo su grader
cd ~
mkdir .ssh
vim .ssh/authorized_keys  # and paste the public key generated on a local PC
chmod 700 .ssh
chmod 644 .ssh/authorized_keys
```
Then, able to SSH in the server with a command like `ssh -i ~/.ssh/linux-server-configuration grader@<server_ip> -p 2200`.

### Security
#### Uncomplicated Firewall (UFW) configuration
```
$ sudo ufw status  #  should be `Status: inactive`
$ sudo ufw default deny incoming
$ sudo ufw default allow outgoing
$ sudo ufw allow www
$ sudo ufw allow ntp
$ sudo ufw allow 2200/tcp
$ sudo ufw enable  # `Proceed with operation (y|n)? y`
```

Then, `sudo ufw status` showed the status bellow:

```
Status: active

To                         Action      From
--                         ------      ----
2200/tcp                   ALLOW       Anywhere
80/tcp                     ALLOW       Anywhere
123                        ALLOW       Anywhere
2200/tcp (v6)              ALLOW       Anywhere (v6)
80/tcp (v6)                ALLOW       Anywhere (v6)
123 (v6)                   ALLOW       Anywhere (v6)
```

#### LightSail Networking configuration
In the Amazon Lightsail console, select the `Networking` tab and add the following configurations in the Firewall section.
```
Custom  UDP 123
Custom  TCP 2200
```
Then, in the server, changed the `sshd_config` as follows.
```
$ sudo vim /etc/ssh/sshd_config
```
Configured as
```
...
# What ports, IPs and protocols we listen for
Port 2200
...
PermitRootLogin no
...
PasswordAuthentication no
```
Then, restarted the sshd
```
$ sudo service sshd restart
```

Lastly, remove the default ssh configuration in the Firewall section on the Amazon Lightsail console.

To configure the timezone to UTC,
```
$ sudo timedatectl set-timezone UTC
($ sudo dpkg-reconfigure tzdata  # might be optional)
$ sudo apt-get install ntp  # for better time synchronization
```

To update and install the packages,
```
$ sudo apt-get update  && sudo apt-get upgrade
$ sudo apt-get dist-upgrade
$ sudo apt install python-pip, python3-pip
$ sudo apt-get install apache2, apache2-dev
$ sudo apt-get install libapache2-mod-wsgi, libapache2-mod-wsgi-py3
$ sudo apt-get install postgresql
$ sudo pip3 install mod_wsgi
```

## Application Functionality
As `grader` user,
```
$ git clone https://github.com/Fujiki-Nakamura/FSND-P2-ItemCatalog.git
$ sudo pip install -r ~/FSND-P2-ItemCatalog/requirements.txt
$ sudo pip3 install -r ~/FSND-P2-ItemCatalog/requirements.txt
```
```
$ sudo vim /etc/apache2/sites-enabled/000-default.conf
```
and editted the `/etc/apache2/sites-enabled/000-default.conf` as follows.
```
...
        WSGIScriptAlias / /var/www/html/app.wsgi
</VirtualHost>
```
Then,
```
$ sudo vim /var/www/html/app.wsgi
```
and added `/var/www/html/app.wsgi` as follows.
```
import sys
import os

sys.path.insert(0, '/home/grader/FSND-P2-ItemCatalog')

from views import app as application
```
Lastly, restart the apache.
```
$ sudo apache2ctl restart
```

### setup database: PostgreSQL
```
$ sudo -u postgres psql
```
In the PostgreSQL commandline,
```sql
CREATE USER catalog WITH PASSWORD 'catalog';
CREATE DATABASE catalog OWNER catalog;
\q
```
Lastly, created the database and some test data.
```
$ cd ~/FSND-P2-ItemCatalog
$ python3 test_data.py
```

## Resources
- [Google Sign-In for server-side apps](https://developers.google.com/identity/sign-in/web/server-side-flow)
- the Student Hub (by watching it, found that Google OAuth API had changed)
- [Ubuntu Server message says packages can be updated, but apt-get does not update any [duplicate]](https://serverfault.com/questions/265410/ubuntu-server-message-says-packages-can-be-updated-but-apt-get-does-not-update) (added afther the Review#1)
