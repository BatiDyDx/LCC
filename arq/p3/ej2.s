no_singular: # Sistema compatible determinado
  # Despejando las ecuaciones se llega a y = (af - dc)/(ae - bd)
  # y x = (c - by) / a
  
  movss %xmm0, %xmm7
  mulss %xmm5, %xmm7
  movss %xmm3, %xmm8
  mulss %xmm2, %xmm8
  subss %xmm8, %xmm7
  divss %xmm6, %xmm7
  movss %xmm7, (%rsi) # y = (af - dc)/(ae - bd)

  movq $0, -8(%rsp)
  movss -8(%rsp), %xmm8
  ucomiss %xmm8, %xmm0
  je case_2

case_1:  # Caso a != 0
  mulss %xmm1, %xmm7
  subss %xmm7, %xmm2
  divss %xmm0, %xmm2
  movss %xmm2, (%rdi) # x = (c - by) / a

  xorq %rax, %rax
  ret

case_2:  # Caso a == 0 => d != 0
  mulss %xmm4, %xmm7
  subss %xmm7, %xmm5
  divss %xmm3, %xmm5
  movss %xmm5, (%rdi) # x = (f - ey) / d

  xorq %rax, %rax
  ret

.global solve 
solve:
# Calculo de determinante del sistema
  movss %xmm4, %xmm6
  mulss %xmm0, %xmm6 # a * e
  movss %xmm3, %xmm7
  mulss %xmm1, %xmm7 # b * d
  subss %xmm7, %xmm6 # ae - bd

  movq $0, -8(%rsp)
  movss -8(%rsp), %xmm8
  ucomiss %xmm8, %xmm6
  jne no_singular
  movl $-1, %eax
  ret

