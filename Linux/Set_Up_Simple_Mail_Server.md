#Set Up Simple Mail Server

This document is written based on this  [article](http://cnedelcu.blogspot.kr/2014/01/how-to-set-up-simple-mail-server-debian-linux.html).

###Requirement
Domain name. ex) example.com

###1. Installing required software
`Postfix` : SMTP server for Linux. (Receiver)
`Dovecot` : A open source IMAP and POP3 server. (Sender)  
This will be able to communicate with postfix for managing user accounts and mailboxes.
`Saslauthd` :Simple Authentication and Security Layer Authentication Daemon.

1) install Postfix
```
$ apt-get install postfix
```
You need to set up for some configurations.

2) install Dovecot
```
$ apt-get install dovecot-common dovecot-imapd dovecot-pop3d
```

3) install Saslauthd
```
$ apt-get install libsasl2-2 libsasl2-modules sasl2-bin
```
You should be getting a message warning you that the SASL auth daemon won't be started when you boot the machine; so open `/etc/default/saslauthd` and set START=yes to make it so.

###2. Setting up SSL certificates (Optional)
1) Generate the certificate files required by Postfix and Dovecot.
```
$ openssl req -new -x509 -days 3650 -nodes -out "example.com.cert" -keyout "example.com.key"
```
Now, we got two files `example.com.cert` and `example.com.key`.

2) Concatenate two file into a third file.
```
$ cat example.com.cert example.com.key > example.com.pem
```
3) Move files.
```
$ mv example.com.cert /etc/ssl/private/
$ mv example.com.key /etc/ssl/private/
$ mv example.com.pem /etc/ssl/private/
```

###3. Postfix Configuration
Creating a special user and group for programs.
1) Create a new group
```
$ groupadd email -g 7788
```

2) Create a new user
```
$ useradd email -r -g 7788 -u 7788 -d /var/email -m -c "mail user"
```
3) Edit configuration file for Postfix
open file `/etc/postfix/main.cf`
```
# Your hostname and domain name here
myhostname=example.com
mydomain=example.com
myorigin=$mydomain

# Virtual mailbox configuration (/var/email should have been created through the previous commands)
virtual_mailbox_base=/var/email
virtual_mailbox_domains=hash:/etc/postfix/vmail_domains
virtual_mailbox_maps=hash:/etc/postfix/vmail_mailbox
virtual_alias_maps=hash:/etc/postfix/vmail_aliases
virtual_minimum_uid=100
virtual_uid_maps=static:7788
virtual_gid_maps=static:7788
virtual_transport=dovecot

# SSL configuration, make sure to use the certificates from step 2 (optional)
smtpd_tls_cert_file=/etc/ssl/private/example.com.cert
smtpd_tls_key_file=/etc/ssl/private/example.com.key
smtpd_tls_CAfile=/etc/ssl/certs/ca-certificates.crt
smtp_tls_CAfile=/etc/ssl/certs/ca-certificates.crt
smtp_use_tls=yes
smtpd_use_tls=yes
smtpd_tls_loglevel=1
smtpd_tls_received_header=yes
tls_random_source=dev:/dev/urandom
smtp_tls_note_starttls_offer=yes
smtpd_tls_session_cache_timeout=3600s
smtpd_tls_session_cache_database = btree:${data_directory}/smtpd_scache
smtp_tls_session_cache_database = btree:${data_directory}/smtp_scache
queue_directory=/var/spool/postfix

# Authentication settings, making use of SASL
smtpd_sasl_type=dovecot
smtpd_sasl_path=private/auth
smtpd_sasl_auth_enable=yes
broken_sasl_auth_clients=yes
smtpd_sasl_security_options=noanonymous
smtpd_sasl_tls_security_options=$smtpd_sasl_security_options
smtpd_sasl_local_domain=$myhostname
smtpd_sasl_application_name=smtpd
smtpd_helo_required=yes
smtpd_helo_restrictions=reject_invalid_helo_hostname
smtpd_recipient_restrictions=reject_unknown_recipient_domain, reject_unauth_pipelining, permit_mynetworks, permit_sasl_authenticated, reject_unauth_destination
```

open file `/etc/postfix/master.cf`
```
submission inet n       -       -       -       -       smtpd
  -o smtpd_tls_security_level=encrypt
  -o smtpd_sasl_auth_enable=yes
  -o smtpd_client_restrictions=permit_sasl_authenticated,reject
  -o milter_macro_daemon_name=ORIGINATING

dovecot   unix  -       n       n       -       -       pipe
  flags=DRhu user=email:email argv=/usr/lib/dovecot/deliver -f ${sender} -d ${recipient}
```
open file `/etc/postfix/sasl/smtpd.conf`

```
pwcheck_method: saslauthd
mech_list: plain login cram-md5 digest-md5
```

###4 Dovecot configuration
open file `/etc/dovecot/dovecot.conf`

```
# Basic configuration
protocols = imap imaps pop3 pop3s
log_timestamp = "%Y-%m-%d %H:%M:%S "
disable_plaintext_auth=yes

# User and group permissions
first_valid_uid=7788
last_valid_uid=7788
first_valid_gid=7788
last_valid_gid=7788
mail_location = maildir:/var/email/%d/%n/Maildir
mail_privileged_group = email
auth_executable = /usr/lib/dovecot/dovecot-auth
auth_verbose = yes

# SSL config
ssl_cert_file = /etc/ssl/private/example.com.cert
ssl_key_file = /etc/ssl/private/example.com.key

# LDA config
protocol lda {
  auth_socket_path = /var/run/dovecot/auth-master
  postmaster_address = postmaster@example.com
  mail_plugins = sieve
  log_path =
}

# Authentication configuration
auth default {
    mechanisms = plain login
    passdb passwd-file {
        args = scheme=SHA1 /etc/dovecot/users.conf
    }
    userdb static {
        #args = /etc/dovecot/users.conf
        args = uid=7788 gid=7788 home=/var/email/%d/%n allow_all_users=yes
    }
    socket listen {
        master {
            path = /var/run/dovecot/auth-master
            mode = 0600
            user = email
            group = email
        }
        client {
            path = /var/spool/postfix/private/auth
            mode = 0660
            user = postfix
            group = postfix
        }
    }
}
```

Create an empty user file.
```
$ touch /etc/dovecot/users.conf
$ chgrp email /etc/dovecot/dovecot.conf
$ chown root:root /etc/dovecot/users.conf
$ chmod 600 /etc/dovecot/users.conf
```

###5. Managing domains and mailboxes
Settings for SMTP and IMAP/POP3 server are finished.
 Now we have to create mailboxes for user accounts for the domains of our choice.

Open and insert each domain and the word OK in this file. `/etc/postfix/vmail_domains`

```
example.com OK
example2.com OK
```

Set up our mailboxes and accounts.
-`/etc/postfix/vmail_mailbox` : contains the list of mailboxes along with their storage path
-`/etc/postfix/vmail_aliases` : the list of email aliases
-`/etc/dovecot/users.conf` : stores your encrypted mailbox passwords

1) vmail_mailbox
```
webmaster@example.com   example.com/webmaster
contact@exmaple.com   example.com/contact
webmaster@example2.com    example2.com/webmaster
```

2) vmail_aliases
```
webmaster@example.com   webmaster@example.com
contact@example.com   contact@example.com
webmaster@example2.com   webmaster@example.com
```

3) users.conf
Generate a password
```
$ dovecotpw -s SHA1
```
and edit users.conf like the form `mailbox@example.com:password`

```
webmaster@example.com:qUqP5cyxm6YcTAhz05Hph5gvu9M=
contact@example.com:EJ9LPFDXsN9ynSmbxvjp75Bmlx8=
webmaster@example2.com:RTzySG+IxBH5rWCLVjrvllztsV0=
```

Apply the changes
```
$ postmap /etc/postfix/vmail_domains
$ postmap /etc/postfix/vmail_mailbox
$ postmap /etc/postfix/vmail_aliases

$ service postfix stop
$ service dovecot stop
$ service postfix start
$ service dovecot start
```
