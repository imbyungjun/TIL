# Merged Commit Log

Github에서 Pull request를 통해 branch를 merge할 경우, 어떤 branch가 merge되었는지 commit log가 추가된다.  

```
Github에서 Pull request를 사용한 경우의 커밋 로그
```

Git을 이용해서 local에서 merge할 경우, 기본 설정으로는 별도의 merged commit log가 남지 않는다.

```
Git을 이용해서 merge한 경우의 커밋 로그
```

다음과 같은 명령어로 merged commit을 추가하여 병합된 기록을 명시적으로 남길 수 있다.

```
 $ git log
 병합전의 커밋 로그
 $ git merge --no-ff branch_to_merge
 $ git log
 병합후의 커밋 로그
```

위 옵션을 Git의 기본 설정으로 변경하기 위해서는 아래 명령어를 사용하면 된다.

```
 $ git config --add merge.ff false
```

하지만 Github의 pull request를 사용하지 않으면 branch를 삭제할 경우 변경내역을 추적할 수 없다는 단점이 있다. 병합된 branch가 삭제된 경우 어떤 branch로부터 병합되었는지는 commit log를 통해서 알 수 있지만 해당 병합과정에서의 변경 사항을 조회할 수 없으므로 pull reqeust를 통해서 병합하는것이 history 관리 측면에서는 더 좋다.
