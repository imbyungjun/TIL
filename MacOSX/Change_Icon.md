#How to change folder icon in terminal

```
# Take an image and make the image its own icon:
sips -i icon.png

# Extract the icon to its own resource file:
/Developer/Tools/DeRez -only icns icon.png > tmpicns.rsrc

# append this resource to the file you want to icon-ize.
/Developer/Tools/Rez -append tmpicns.rsrc -o file.ext

# Use the resource to set the icon.
/Developer/Tools/SetFile -a C file.ext

# clean up.
rm tmpicns.rsrc
# rm icon.png # probably want to keep this for re-use.
```

###Apply on folder
```
# Append a resource to the folder you want to icon-ize.
Rez -append tmpicns.rsrc -o $'myfolder/Icon\r'

# Use the resource to set the icon.
SetFile -a C myfolder/

# Hide the Icon\r file from Finder.
SetFile -a V $'myfolder/Icon\r'
```

[Related link](http://apple.stackexchange.com/questions/6901/how-can-i-change-a-file-or-folder-icon-using-the-terminal)