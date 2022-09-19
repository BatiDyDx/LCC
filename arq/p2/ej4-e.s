.global main
main:
  movw $5, %ax
	salw $8, %ax # ax = ax << 8
	ret

