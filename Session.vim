let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Documents/dev/Smedja
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +81 Smedja/src/Smedja/Application.cpp
badd +51 Smedja/src/Smedja/Renderer/Texture.cpp
badd +21 Session.vim
badd +49 Smedja/src/Smedja/Application.h
badd +11 data/shaders/test.frag
badd +8 data/shaders/test.vert
badd +14 Smedja/src/Smedja/Renderer/Texture.h
badd +68 Smedja/src/Smedja/Renderer/Shader.h
badd +151 Smedja/src/Smedja/Renderer/Shader.cpp
argglobal
%argdel
$argadd NvimTree_1
edit Smedja/src/Smedja/Application.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt Smedja/src/Smedja/Renderer/Shader.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 80 - ((22 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 80
normal! 029|
lcd ~/Documents/dev/Smedja
wincmd w
argglobal
if bufexists(fnamemodify("~/Documents/dev/Smedja/data/shaders/test.frag", ":p")) | buffer ~/Documents/dev/Smedja/data/shaders/test.frag | else | edit ~/Documents/dev/Smedja/data/shaders/test.frag | endif
if &buftype ==# 'terminal'
  silent file ~/Documents/dev/Smedja/data/shaders/test.frag
endif
balt ~/Documents/dev/Smedja/Smedja/src/Smedja/Renderer/Shader.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 11 - ((10 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 11
normal! 051|
lcd ~/Documents/dev/Smedja
wincmd w
wincmd =
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
