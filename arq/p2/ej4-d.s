.global main
main:
  movl $0xAA, %ebx
	movl $0xAA, %eax
	sall $24, %eax  # eax = eax << 24
	orl %ebx, %eax  # eax = eax | ebx
	retl

