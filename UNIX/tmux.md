#tmux
A terminal multiplexer. Let us switch easily between several programs in one terminal.

###Words
- session : tmux execution units.
- window : we can make multiple windows in tmux session.
- pane : we can split a window as multiple pane.
- status bar : lowest line for print status.

###Commands
Before input any command, you should press `ctrl+b`.

1) session management

```
# create new session
$ tmux new -s <session-name>

# change session name
ctrl + b, $

# exit session
exit

# detach session
ctrl + b, d

# list up session
$ tmux ls

# restart session
$ tmux attach -t <session-number | session-name>
```

2) window management

```
# create new window
ctrl + b, c

# create session with new window
$ tmux new -s <session-name> -n <window-name>

# change window name
ctrl + b, ,

# close window
ctrl + b, &
ctrl + d

# move to another window
ctrl + b, 0-9 : window number
            n : next window
            p : previous window
            l : last window
            w : window selector
            f : find by name
```

3) pane management

```
# divide pane
ctrl +b, % : divide by row
         " : divide by col
         
# change pane
ctrl + b, q number
ctrl + b, o : change pane in order
ctrl + b, arrow : using arrow keyboard input

# remove pane
ctrl + b, x
ctrl + d

# change pane size
(ctrl + b, :)
resize-pane -L 10
            -R 10
            -D 10
            -U 10
            
# change pane layout
ctrl + b, spacebar
```

4) shortcuts

```
# shortcut list
ctrl + b, ?

# bind and unbind key ?????
(ctrl + b, :)
bind-key [-cnr] [-t key-table] key command [arguments]
unbind-key [-acn] [t key-table] key

# 'set' and 'setw' ?????
set -g <option-name> <option-value>  : set-option
setw -g <option-name> <option-value> : set-window-option
```

5) copy mode

```
# entering copy mode
ctrl + b, [

# quit copy mode
q or ESC
arrow : change cursor position
pasgeUp, pageDown : change page

```

6) tmux.conf

         