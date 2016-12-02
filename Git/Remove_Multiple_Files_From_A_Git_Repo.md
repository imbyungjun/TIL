#Removing multiple files from a Git repo that have already been deleted from disk

1. Check you have already been deleted files.
```
$ git status

	deleted:    file1
	deleted:    file2
	deleted:    file3
	deleted:    file4
	deleted:    file5

```

2. Remove the files from git.
```
$ git ls-files --deleted -z | xargs -0 git rm 
```

link : http://stackoverflow.com/questions/492558/removing-multiple-files-from-a-git-repo-that-have-already-been-deleted-from-disk
