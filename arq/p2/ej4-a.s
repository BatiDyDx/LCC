.global main
main:
  movl $1, %eax
	sall $31, %eax # eax = eax << 31
	ret
