.global exp
exp:
  mov r1, #1
  mov r0, r1, LSL r0
  bx lr

.global main
main:
  mov r0, #4
  push {lr}
  bl exp
  pop {lr}
  bx lr

