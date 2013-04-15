version 5.0
set nocompatible
let cpo_save=&cpo
set cpo=B
map! <xHome> <Home>
map! <xEnd> <End>
map! <S-xF4> <S-F4>
map! <S-xF3> <S-F3>
map! <S-xF2> <S-F2>
map! <S-xF1> <S-F1>
map! <xF4> <F4>
map! <xF3> <F3>
map! <xF2> <F2>
map! <xF1> <F1>
map Q gq
map <xHome> <Home>
map <xEnd> <End>
map <S-xF4> <S-F4>
map <S-xF3> <S-F3>
map <S-xF2> <S-F2>
map <S-xF1> <S-F1>
map <xF4> <F4>
map <xF3> <F3>
map <xF2> <F2>
map <xF1> <F1>
abbr #l /* --------------------------------------- */
abbr #e ===================================================================== */
abbr #b /* =====================================================================
abbr #i #include
abbr #d #define
let &cpo=cpo_save
unlet cpo_save
set autoindent
set autowrite
set background=dark
set backspace=2
set filetype=make
set formatoptions=tcql
set guifont=-b&h-lucidatypewriter-medium-r-normal-*-*-120-*-*-m-*-iso8859-1
set history=50
set hlsearch
set incsearch
set mouse=a
set ruler
set shiftwidth=4
set syntax=make
set viminfo='20,\"50
let v:this_session=expand("<sfile>:p")
1,9999bd
execute "cd " . expand("<sfile>:p:h")
let shmsave = &shortmess | set shortmess=aoO
e +22 Makefile
badd +32 abuffer.h
badd +82 abuffer.c
badd +11 teste.c
let sbsave = &splitbelow | set splitbelow
b Makefile
let &splitbelow = sbsave
normal t9Gzt22G014l
let &shortmess = shmsave
let sessionextra=expand("<sfile>:p:r")."x.vim"
if file_readable(sessionextra)
	execute "source " . sessionextra
endif
