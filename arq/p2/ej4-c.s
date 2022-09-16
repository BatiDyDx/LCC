.global main
main:
  movl $-1, %ebx
	movl $0xFFFFFF00, %eax
	andl %ebx, %eax # eax = eax & ebx
	retl

