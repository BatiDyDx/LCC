.global main
main:
  # a)
  rorq $32, %rax
  
  # b)
  movq $0xaaaaaaaaaaaaaaaa, %rax
  xorb %bl, %bl
  movl $64, %ecx
start:
  rolq $1, %rax
  adcb $0, %bl
  loop start
  
  ret

  # Prueba de rcl y rcr
  clc
  movb $0xaa, %al
  rclb $1, %al

  stc 
  movb $0xaa, %al
  rclb $1, %al

  clc
  movb $0x55, %al
  rclb $1, %al

  stc
  movb $0x55, %al
  rclb $1, %al
  ret
