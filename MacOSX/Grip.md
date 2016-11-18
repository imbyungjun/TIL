#Grip

Render local markdown files before sending to Github.

###Install
```
$ pip install grip
```

###Use it
```
$ grip file.md
```

###Change port
```
$ grip 8080
```

###specifically render GitHub-Flavored Markdown, optionally with repository context
```
$ grip --gfm --context=username/repo issue.md
```
