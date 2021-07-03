"===================================================================
" Vundle stuff
"===================================================================

set nocompatible
filetype off

set rtp+=~/.vim/bundle/vundle/
call vundle#rc()

Bundle 'gmarik/vundle'

Bundle 'prabirshrestha/async.vim'
Bundle 'prabirshrestha/asyncomplete-lsp.vim'
Bundle 'prabirshrestha/asyncomplete.vim'
Bundle 'prabirshrestha/vim-lsp'
Bundle 'drmingdrmer/xptemplate'
Bundle 'nvie/vim-flake8'
Bundle 'xsnippet/vim-xsnippet'
Bundle 'majutsushi/tagbar'
Bundle 'kien/ctrlp.vim'
Bundle 'tpope/vim-fireplace'
Bundle 'w0ng/vim-hybrid'
Bundle 'mhinz/vim-grepper'


filetype plugin indent on

"===================================================================
" OPTIONS
"===================================================================

" general
set nocompatible                " No compatibility with vi
set shellslash                  " Set forward slash to be the slash of note (for Windows - backslashes suck)
set backspace=2                 " Allow backspacing over indent,  eol,  and the start of an insert
set scrolloff=8                 " Number of lines from the end of the screen when start scrolling
set sidescrolloff=3             " Number of columns from the end of the screen when start scrolling
set incsearch                   " Enable incremental search
set ignorecase                  " Ignore search case
set smartcase                   " Match upper case in the search string if specified
set isfname+=32                 " Make Vim understand filenames with spaces
set showfulltag                 " When completing by tag, show the whole tag, not just the function name
set history=128                 " How much lines of command line history to remember
set undolevels=2048             " Number of possible undo's
set hidden                      " Enable unwritten buffers to be hidden
set autochdir                   " Automatically switch directory to current
set virtualedit=all             " Enable a full virtual editing mode
set showmode                    " Show what mode are you in
set wildmenu                    " Enable enhanced command line completion
set browsedir=current           " Directory to use for the file browser
set diffopt+=iwhite             " Add ignorance of whitespace to diff
set autoread                    " Automatically read files, edited outside of Vim
set showcmd                     " Show current command buffer
set splitbelow                  " Put the new window below when vertical splitting
set splitright                  " Put the new window right when horizontal splitting
set backup                      " Save file backups
set backupdir=~/.vim/backups    " Directory for backup storing
set directory=~/.vim/swap       " Directory for storing swaps
set list!
set listchars=tab:->,trail:-    " Set unprintable characters
set iminsert=0                  " Turn of :lmap and Input Method
set imsearch=-1                 " Set search layout same is iminsert
set lazyredraw                  " Don't update the display while executing macros
set ffs=unix,dos,mac            " End-of-line symbol processing order
set fileencodings=utf-8,windows-1251,iso-8859-15,koi8-r " Order of encodings recognition attempts

set guicursor=n-v-c:block-Cursor-blinkon0
set guicursor+=ve:ver35-Cursor
set guicursor+=o:hor50-Cursor
set guicursor+=i-ci:ver25-Cursor
set guicursor+=r-cr:hor20-Cursor
set guicursor+=sm:block-Cursor-blinkwait175-blinkoff150-blinkon175

if has("gui_macvim")
    set guifont=Monaco:h14
else
    set guifont=Liberation\ Mono\ 14
endif

set guioptions-=m  "remove menu bar
set guioptions-=T  "remove toolbar
set guioptions-=r  "remove right-hand scroll bar

inoremap <silent> <S-F10> <ESC>:set keymap=russian-jcukenwin<CR>a
inoremap <silent> <S-F11> <ESC>:set keymap=ukrainian-jcuken<CR>a

" xptemplate autocompletion
let g:xptemplate_vars = 'SParg=' " don't insert a space between autocompleted braces
let g:xptemplate_brace_complete = '({["' " autocompleted braces

" leader key
let mapleader=";"

"========================================
" TEXT FORMATTING
"========================================

" Indentation settings
set autoindent              " Inherit current indentation in the next line
set smartindent             " Smart indenting based on syntax conventions
set tabstop=4               " Set tab size (in spaces)
set shiftwidth=4            " Shift lines by 4 spaces
set smarttab                " Align tab instead of just inserting 4 spaces
set expandtab               " Expand tab with spaces
set softtabstop=4           " Set soft tab size
set textwidth=120           " Set the text width to be 120 chars
set nowrap                  " Disable text wrapping
set wrapscan                " Set the search scan to wrap lines

set spelllang=en,ru_yo,uk   " Define languages to spell check
set spellsuggest=10         " Limit spell suggestions with 10 entries (z= to activate)

"========================================
" LOOKS
"========================================

set t_Co=256             " Enable 256 color mode
set background=dark
let g:hybrid_reduced_contrast = 1
set termguicolors
colorscheme hybrid

syntax  on              " Turn on syntax highlighting
set cursorline          " Highlight the line with cursor
set cursorcolumn        " Highlight the column with cursor
set number              " Enable line numbering
set synmaxcol=256       " Syntax coloring long lines slows down the editor
set cpoptions+=ces      " Change the <c> motion behavior
set mousehide           " Hide mouse cursor while typing 
set timeoutlen=500      " Timeout between keystrokes on shortcuts
set fillchars=""        " Get rid of characters in windows separators
set hlsearch            " Highlight search results

let python_highlight_all=1

" Set the status line format
set laststatus=2
set stl=%f\ %m\ %r\ %y\ [Len\ %L:%p%%]\ [Pos\ %02l:%02c\ 0x%O]\ [%3b][%02Bh]\ [Buf\ #%n]

"========================================
" MAPPINGS
"========================================

" F3 - call file explorer
map <silent> <F3>   :Explore<CR>

" Compile file
nmap <silent> <F5>  :make<CR>

" Remap <gf> to open included files in the new buffer if current buffer is busy
map gf :edit <cfile><CR>

" Spellcheck trigger
nmap <silent> ,sp :set spell!<CR>

" Key mapping for simple .vimrc editing
nmap <silent> ,ev :e $MYVIMRC<CR>

" Key mapping for simple .gvimrc editing
nmap <silent> ,eg :e ~/.gvimrc<CR>

" Source .vimrc file
nmap <silent> ,sv :source $MYVIMRC<CR>

" Source .gvimrc file
nmap <silent> ,sg :source ~/.gvimrc<CR>

" Load last saved session from .vim/sessions/
map ,ls :call LoadSession()<CR>

" Buffer commands
noremap <silent> ,bd :bd<CR>    " delete current buffer
noremap <silent> ,bn :bn<CR>    " move to the next buffer
noremap <silent> ,bp :bp<CR>    " move to previous buffer
noremap <silent> ,bl :b#<CR>    " back to the last buffer

" Map the <+ +> placeholder navigation
nnoremap <c-j> /<+.\{-1,}+><cr>c/+>/e<cr>
inoremap <c-j> <ESC>/<+.\{-1,}+><cr>c/+>/e<cr>

" Tagbar side panel
nmap <F8> :TagbarToggle<CR>

"========================================
" PLUGINS
"========================================
"

let g:grepper = {
    \ 'dir': 'repo,file',
    \ 'tools': ['git', 'ag', 'grep'],
  \ }"
nnoremap <leader>g :Grepper<CR>

map <F6> :call PostToXsnippet() <CR>

"=== ctrl-p
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlPMixed'

set encoding=utf-8


if executable('pyls')
    au User lsp_setup call lsp#register_server({
        \ 'name': 'pyls',
        \ 'cmd': {server_info->['pyls']},
        \ 'whitelist': ['python'],
        \ 'priority': 1,
        \ 'workspace_config': {
          \ 'pyls': {'plugins': {'jedi_completion': {'include_params': v:false}}},
        \ },
        \ })
    autocmd FileType python setlocal omnifunc=lsp#complete
endif
if executable('rust-analyzer')
    au User lsp_setup call lsp#register_server({
        \ 'name': 'rust-analyzer',
        \ 'cmd': {server_info->['rust-analyzer']},
        \ 'whitelist': ['rust'],
        \ 'priority': 1,
        \ })
    autocmd FileType rust setlocal omnifunc=lsp#complete
endif
if executable('clangd')
    au User lsp_setup call lsp#register_server({
        \ 'name': 'clangd',
        \ 'cmd': {server_info->['clangd']},
        \ 'whitelist': ['c', 'cpp', 'objc', 'objcpp'],
        \ 'priority': 1,
        \ })
    autocmd FileType c,cpp,objc,objcpp setlocal omnifunc=lsp#complete
endif
if executable('clojure-lsp')
    au User lsp_setup call lsp#register_server({
        \ 'name': 'clojure-lsp',
        \ 'cmd': {server_info->['clojure-lsp']},
        \ 'whitelist': ['clojure'],
        \ 'priority': 1,
        \ })
    autocmd FileType clojure setlocal omnifunc=lsp#complete
endif

noremap <silent> ;d :LspDefinition<CR>
noremap <silent> ;r :LspReferences<CR>
noremap <silent> ;f :LspDocumentFormat<CR>
noremap <silent> ;n :LspRename<CR>

let g:lsp_signs_enabled = 1            " enable signs
let g:lsp_diagnostics_echo_cursor = 1  " enable echo under cursor when in normal mode

" TAB completion
inoremap <expr> <Tab> pumvisible() ? "\<C-n>" : "\<Tab>"
inoremap <expr> <S-Tab> pumvisible() ? "\<C-p>" : "\<S-Tab>"
inoremap <expr> <cr> pumvisible() ? "\<C-y>" : "\<cr>"
