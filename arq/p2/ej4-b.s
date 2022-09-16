.global main
main:
  movl $1, %eax
	movl $1, %ebx
	sall $31, %eax # eax = eax << 31
	sall $15, %ebx # ebx = ebx << 15
	orl %ebx, %eax # eax = eax | ebx
	retl
