#vim markdown

Vim's syntax highlighting doesn't work for .md file extension by default.  
It's because .md extension is for both markdown and ???? script.

Append this code to your .vimrc file.

```
"Markdown highlighting
augroup markdown
	" remove previous autocmds
	autocmd!

	" set every new or raed *.md buffer to use the markdown filetype
	autocmd BufRead,BufNew *.md set filetype=markdown

augroup END
```
