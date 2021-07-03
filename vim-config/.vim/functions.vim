"================================================================= 
" DESCRIPTION: Functions needed for .vimrc file
"    MODIFIED: 2010 Aug 05
"      AUTHOR: Zoresvit    zoresvit@gmail.com
"              Kharkiv National University of Radioelectronics
"=================================================================



" Save current session to .vim/sessions
function! SaveSession()
    execute 'mksession! ~/.vim/sessions/session.vim'
endfunction

" Load last session from .vim/sessions
function! LoadSession()
    if argc() == 0
        execute 'source ~/.vim/sessions/session.vim'
    endif
endfunction

" Insert the date of file creation
function DateCreated()
    if line("$") > 20
        let l = 20
    else
        let l = line("$")
    endif
    exe "1," . l . "g/CREATED: /s/CREATED: .*/CREATED: " .
                \ strftime("%Y %b %d")
endfunction

" Get short and convenient tab label
function ShortTabLabel()
    let ret = ''
    for i in range(tabpagenr('$'))
        " select the color group for highlighting active tab
        if i + 1 == tabpagenr()
            let ret .= '%#errorMsg#'
        else
            let ret .= '%#TabLine#'
        endif

        " find the buffer name for the tab label
        let buflist = tabpagebuflist(i+1)
        let winnr = tabpagewinnr(i+1)
        let buffername = bufname(buflist[winnr - 1])
        let filename = fnamemodify(buffername, ':t')
        " check if there is no name
        if filename == ''
            let filename = 'noname'
        endif
        " only show the first 6 letters of the name and if the filename is more than 8 letters long
        if strlen(filename) >= 8
            let ret .= '['. filename[0:5].'..]'
        else
            let ret .= '['.filename.']'
        endif
    endfor
    " reset tab page
    let ret .= '%#TabLineFill#%T'
    return ret
endfunction

" Get short and convenient tab label in GUI
function GShortTabLabel()
    let bufnrlist = tabpagebuflist(v:lnum)
    " show only the first 6 letters of the name + ..
    let label = bufname(bufnrlist[tabpagewinnr(v:lnum) - 1])
    let filename = fnamemodify(label, ':h')
    " only add .. if string is longer than 8 letters
    if strlen (filename) >= 8
        let ret=filename[0:5].'..'
    else
        let ret = filename
    endif
    return ret
endfunction

