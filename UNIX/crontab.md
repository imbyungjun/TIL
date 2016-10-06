# Crontab - Schedule Tasks
The **crontab** (cron derives from chronos, Greek for time; tab stands for table) is used to schedule commands to be executed periodically.

### Print the list of currently running crontabs
```
$ crontab -l
```

### To edit the list of cronjobs
```
$ crontab -e
```
This will open a default editor. If you save tasks and exit the editor, cronjobs are saved into crontab. Cronjobs need to be written in the following format;
```
* * * * * /bin/execute/this/script.sh
```

### Scheduling task format
The stars represent different date parts in the following order
* minute (0-59)
* hour (0-23)
* day of month (1-31)
* month (1-12)
* day of week (0-6) (0 is Sunday)

### Execute every minute
```
* * * * * /bin/execute/this/script.sh
```
It means that execute the script `/bin/execute/this/script.sh` :
* **every** minute
* of **every** hour 
* of **every** day of the month 
* of **every** month 
* and **every** day in the week.

### Execute every Friday 1AM
So, if we want to schedule the script to run at 1AM every Friday, we would need the following cronjob:
```
0 1 * * 5 /bin/execute/this/script.sh
```

* mintue: `0`
* of hour: `1`
* of day of month: `*` (every day of month)
* of month: `*` (every month)
* and weekday: `5` (= Friday)

### Execute on weekdays 1AM
So if we want to schedule the script to Monday till Friday at 1 AM, we would need the following cronjob:
```
0 1 * * 1-5 /bin/execute/this/script.sh
```

* mintue: `0`
* of hour: `1`
* of day of month: `*` (every day of month)
* of month: `*` (every month)
* and weekday: `1-5` (= Monday to Friday)

### Execute 10 past after every hour on the 1st of every month
```
10 * 1 * * /bin/execute/this/script.sh
```

### Execute every 10 minutes
```
0,10,20,30,40,50 * * * * /bin/execute/this/script.sh
```

```
*/10 * * * * /bin/execute/this/script.sh
```

Both wiil do exactly the same. 

### Special words
For the first(minute) field, you can also put in a keyword instead of a number:

```
@reboot     Run once, at startup
@yearly     Run once  a year     "0 0 1 1 *"
@annually   (same as  @yearly)
@monthly    Run once  a month    "0 0 1 * *"
@weekly     Run once  a week     "0 0 * * 0"
@daily      Run once  a day      "0 0 * * *"
@midnight   (same as  @daily)
@hourly     Run once  an hour    "0 * * * *"
```

```
@daly /bin/execute/this/script.sh
```

### Storing the crontab output
```
*/10 * * * * /bin/execute/this/script.sh >> /var/log/script_output.log 2>&1
```
Redirection to `2>&1` means that to store STDERR in STDOUT as well.

### Mailing the crontab output
By default cron saves the output in the user's mailbox (root in this case) on the local system. But you can also configure crontab to forward all output to a real email address by starting your crontab with the following line:
```
MAILTO="email@domain.com"
```

### Mailing the crontab output of just one cronjob
If you'd rather receive only one cronjob's output in your mail, you can do it with using mail utilitys like this:
```
*/10 * * * * /bin/execute/this/script.sh 2>&1 | mail -s "Cronjob ouput" yourname@yourdomain.com
```

### Trashing the crontab output
```
*/10 * * * * /bin/execute/this/script.sh > /dev/null 2>&1
```
Just pipe all the output to the null device.

[참고한 포스팅](http://kvz.io/blog/2007/07/29/schedule-tasks-on-linux-using-crontab/)