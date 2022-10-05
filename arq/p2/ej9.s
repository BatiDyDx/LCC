.data
array: .byte 1, 2, 3, 4, 5, 6, 7
length: .byte 7
inverted: .space 7 

.text
.global main
main:
  movq $0, %rax

push_to_stack:
  push array(, %rax, 1)
  incb %al
  cmpb %al, length
  jne push_to_stack

  movq $0, %rax

pull_from_stack:
  pop inverted(, %rax, 1)
  incb %al
  cmpb %al, length
  jne pull_from_stack

  ret

