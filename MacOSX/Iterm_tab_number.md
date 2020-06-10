# ITerm2 Get the Tab Number

We can get the iterm session id like below
```bash
$ echo ${ITERM_SESSION_ID}
w0t0p0:4A510CA7-A170-48FF-8341-127719F3240A
```

This varibale has a pattern that `w_t_p_:${random_serial}`
```
w0t0p0:4A510CA7-A170-48FF-8341-127719F3240A
w0t0p1:B742F156-E045-4D04-A890-5D01998F5018
w0t0p2:C758523C-652D-41E9-94FC-A07E5A46482C
...
```

Get each session id in different window
```bash
$ echo ${ITERM_SESSION_ID:1:1}
```

Get each session id in different tab
```bash
$ echo ${ITERM_SESSION_ID:3:1}
```

Get each session id in different pane
```bash
$ echo ${ITERM_SESSION_ID:5:1}
```
