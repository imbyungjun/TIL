# Rebase
다수의 Commit들을 작성하게되는 경우가 있다. 그리고 그 중에는 같은 분류로 묶일 수 있는 작업들이 여러개인 경우도 존재한다. 혹은 커밋 순서를 바꾸고 싶은 경우도 생긴다. 예를 들면 아래와 같다.

```
commit 55805d3bd160ddb9e67f92ec09ab924a8b6ed73a
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:48 2017 +0900

    버그 재수정

commit e749c03be85676f2addbc9c1480688b47d91e6ab
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:40 2017 +0900

    리펙터링

commit a74b330ae735b73419301740e47d6587916434c7
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:34 2017 +0900

    버그 수정

commit fefe2facc851f6182d54fd2618ee44c8e5bf7d15
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:24 2017 +0900

    체크 스타일 적용

```

버그 수정을 커밋한 이후에 리펙터링을 진행하였고, 리펙터링이 완료되고 나서 버그를 다시 수정해야한다는 사실을 깨닫게 되었다. 그리고 체크 스타일 적용과 리펙터링의 순서를 바꾸고싶다. 위의 예시는 4개의 커밋만 존재하지만 훨씬 많은 양의 커밋을 Pull request 보내려한다면 커밋들이 서로 얽혀있어서 깔끔하지 못하고 병합할 수 있는 불필요한 커밋들이 다수 존재할 것이다. 이런 경우 Rebase 명령어를 사용하여 Commit들을 병합하여 깔끔하게 정리할 수있다.

DEV 브랜치에서 checkout한 feature 브랜치에서 commit들을 정리한다고 가정하면 다음과 같은 방식으로 정리할 수 있다.
> git rebase 명령어에는 부모 branch를 명시해야한다??? man page에는 다음과 같이 설명되어있다.
```
If <branch> is specified, git rebase will perform an automatic git
checkout <branch> before doing anything else. Otherwise it remains on
the current branch.
```

### 1. feature 브랜치에서 git rebase 명령어를 사용
```
(feature/___) $ git rebase -i DEV
```

### 2. Commit들을 수정할 수 있는 editor가 열림
```
pick fefe2fa 체크 스타일 적용
pick a74b330 버그 수정
pick e749c03 리펙터링
pick 55805d3 버그 재수정

# Rebase fef27d7..55805d3 onto fef27d7 (4 commands)
#
# Commands:
# p, pick = use commit
# r, reword = use commit, but edit the commit message
# e, edit = use commit, but stop for amending
# s, squash = use commit, but meld into previous commit
# f, fixup = like "squash", but discard this commit's log message
# x, exec = run command (the rest of the line) using shell
# d, drop = remove commit
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
```

### 3. 버그 재수정 커밋을 버그 수정 커밋에 병합하기위해서는 다음과 같이 수정
```
pick fefe2fa 체크 스타일 적용
pick a74b330 버그 수정
squash 55805d3 버그 재수정
pick e749c03 리펙터링
```

### 4. 리펙터링 커밋과 체크 스타일 적용 커밋의 순서를 변경하려면 다음과 같이 수정
```
pick e749c03 리펙터링
pick a74b330 버그 수정
squash 55805d3 버그 재수정
pick fefe2fa 체크 스타일 적용
```

### 5. 설정을 저장하면 수행될 Rebase 작업에 대한 명세가 나오고 새로운 커밋 메세지를 작성할 수 있다.
```
# This is a combination of 2 commits.
# This is the 1st commit message:

버그 수정

# This is the commit message #2:

버그 재수정

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# Date:      Fri Aug 11 15:57:34 2017 +0900
#
# interactive rebase in progress; onto fef27d7
# Last commands done (3 commands done):
#    pick a74b330 버그 수정
#    squash 55805d3 버그 재수정
# Next command to do (1 remaining command):
#    pick fefe2fa 체크 스타일 적용
# You are currently editing a commit while rebasing branch 'feature/___' on 'fef27d7'.
```

### 6. 해당 내용을 저장하면 Rebase 작업이 수행된다. 수행결과는 다음과 같다.
```
(feature/___) $ git log

commit 3099488f78a84010ecee1d7768e74d8d26d14735
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:24 2017 +0900

    체크 스타일 적용

commit 38b392327cd40b83c36e52ebf96d8744c6e34f88
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:34 2017 +0900

    버그 수정

    버그 재수정

commit 7df9cfcfa83159631b7f140a9be67307acf03ee8
Author: imbyungjun <im@byungjun.me>
Date:   Fri Aug 11 15:57:40 2017 +0900

    리펙터링

```
