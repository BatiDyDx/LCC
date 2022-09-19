.global  main
main:
  movl  $-1, %eax
  movl  $2 , %ecx
  imull %ecx

  #-------------
  salq $32 , %rdx
  orq  %rdx, %rax
  #-------------

  xorq  %rax, %rax
  movw  $-1 , %ax
  movw	$2  , %cx
  mulw  %cx

  #-------------
  sall $16, %edx
  orq  %edx, %eax
  #-------------

  ret
