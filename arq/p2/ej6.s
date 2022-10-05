.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10

.text
sum:
  xorl %eax, %eax # Suma = 0
  movq $0,   %rcx # Contador = 0
sum_loop:
  addl list(,%rcx,4), %eax
  incb %cl
  cmpb length, %cl
  jnz sum_loop
  ret

min:
  movl list, %eax  # eax = list[0]
  movq $0,   %rcx  # contador = 0
min_loop:
  incb %cl
  cmpb length, %cl
  je min_return
  movl list(,%rcx,4), %ebx # ebx = list[cl]
  cmpl %ebx, %eax
  cmovg %ebx, %eax
  jmp min_loop
min_return:
  ret

max:
  movl list, %eax  # eax = list[0]
  movq $0,   %rcx  # contador = 0
max_loop:
  incb %cl
  cmpb length, %cl
  je max_return
  movl list(,%rcx,4), %ebx # ebx = list[cl]
  cmpl %ebx, %eax
  cmovl %ebx, %eax
  jmp max_loop
max_return:
  ret

avg:
  call sum
  movl %eax, %edx
  shr  $16,   %edx
  movl  length, %ebx
  idivw %bx
  ret

.global main
main:
  call sum
  call avg 
  call min
  call max
  ret

