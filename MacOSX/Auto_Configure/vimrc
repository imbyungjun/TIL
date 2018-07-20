"if you want to set configure for all users,
"make file /etc/vim/vimrc.local 

syntax enable
filetype plugin indent on
set number
set tabstop=4
set shiftwidth=4
set smartindent
set expandtab
set hlsearch
set cursorline
"set expandtab

"Auto complete config
hi Pmenu ctermfg=white ctermbg=245
hi PmenuSel ctermfg=lightgrey ctermbg=darkblue 

"Highlight color
hi Search cterm=NONE ctermbg=darkgrey ctermfg=white

"Visual color
hi Visual cterm=NONE ctermbg=darkgrey ctermfg=44

"Empty lines(~) color
hi NonText ctermfg=7

"Line number color
hi LineNr ctermfg=228

"Statement color
hi Statement ctermfg=228

"String color
hi String ctermfg=203

"Number color
hi Number ctermfg=203

"CursorLine
hi CursorLine cterm=BOLD

"Command
:command W w
:command Wq wq
:command Q q
:command WQ wq

"Markdown highlighting
augroup markdown
	" remove previous autocmds
	autocmd!

	" set every new or raed *.md buffer to use the markdown filetype
	autocmd BufRead,BufNew *.md set filetype=markdown

augroup END

"TERM setting
set term=screen-256color

"Duplicate a line shortcut
nnoremap D yyp
vnoremap D y`>pgv
