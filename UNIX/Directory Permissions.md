#Directory Permission in UNIX
UNIX control access by permission. 
( ex. rwxr-xr-x )

Read / Write / Execute

Owner / Group / Others

and **Directories** also have their permissions.

Read - allow read the directories' entry. So if you have r permission, you can use 
	
	$ ls dir/

Write - allow write the files in directory. It doesn't mean you can modify files in the directory, but you can remove file, and make new file with same name.

	$ rm file_name
	$ touch file_name

Execute - allow searching. You can search the directory. And you can excute and move to the other directory across the directory.
	
	$ /PATH/excutable/a.out