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

###Export markdown to html
```
$ grip my_file.md --export my_file.html
```
