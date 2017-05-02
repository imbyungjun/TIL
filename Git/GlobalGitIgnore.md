# Global GitIgnore File setting

Git 사용시 불필요한 파일이 Repository에 등록되지 않도록 .gitignore을 사용한다.  
 사용하는 OS나 IDE의 특성상 매번 중복되는 .gitignore파일을 작성해야하는 경우가 있다.  
다음과 같이 모든 프로젝트에 대하여 .gitignore설정을 하면 좀 더 편리하다.

1. `~/.gitignore`파일을 작성

```
# Global gitignore configuration
.DS_Store
.idea
target/
```

2. 다음 명령어로 전체 설정으로 적용

```
 $ git config --global core.excludesfile '~/.gitignore'
```
