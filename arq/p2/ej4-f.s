.global main
main:
  movl $-1, %eax
  movl $1, %ebx
  sall $8, %ebx
  notl %ebx
  andl %ebx, %eax
  retl

