# Git commands

1 ) Setting git account
```
$ git config --global user.name "Name"
$ git config --global user.email im@byungjun.me
```

2 ) Check overall configuration
```
$ git config --list
```

3 ) Cloning git repository
```
$ git clone remote_git_repository
```

4 ) Check file status
```
$ git status
On branch master
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   Staged

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   Modified

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	Untracked
```

5 ) Make a file to be tracked
```
$ git add modified_or_new_files
```

6 ) Commit a change
```
$ git commit -m "commit messages"
```
Commit is an action of storing changes that are staged

7 ) View change history
```
$ git log
commit 218b3d5135886dad8d9cbd4f2e81f9dbf0abd684
Author: imbyungjun <20113316@kookmin.ac.kr>
Date:   Wed Dec 14 21:43:27 2016 +0900

    Initial commit
```
options :  
 --graph : show in graph form  
 --stat : show a summary of changes

8 ) Share your change publicly
```
$ git push remote_name branch_name
```

9 ) Create a branch
```
$ git branch new_branch_name
```

10 ) Check the list of branches
```
$ git branch
```

11 ) Change a brach
```
$ git checkout branch_name
```

12 ) Modify commit message
```
$ git commit --amend
```
It will redirect you to a default editor to reset the most recent commit

13 ) Modify older and multiple commits
```
$ git rebase
```

14 ) Update a branch from remote
```
$ git fetch remote_name
```
It only downloads the change locally

```
$ git pull remote_name
```
It fetches the newest changes from the remote origin and update your local copies (fetch + merge)

15 ) Reset all the changes
```
# --soft option will remain new files
$ git reset --soft

# --hard option will remove all new files
$ git reset --hard
```

16 ) Save current changes before commit.
```
# Make the current working stage clean
$ git stash

# Restore the stashed result
$ git stash list
$ git stash apply STASH_ID
```
It is useful when you want to checkout to another branch, but you don't want to commit or push current changes.


