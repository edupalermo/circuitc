set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set number

augroup project
  autocmd!
  autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END
