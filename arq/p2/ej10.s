.global main
main:
  # a)
  rorq $32, %rax
  
  # b)
  movl $64, %ecx
  xorq %rbx, %rbx
start:
  rolq $1, %rax
  adcb $0, %bl
  loop start
  
  ret
