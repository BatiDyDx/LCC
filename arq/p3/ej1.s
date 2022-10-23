.global convert
convert: # h = f * 1.5 + c
  # Representacion en IEEE 754 precision doble de 1.5
  movl $0x3ff8, %eax          # Se almacena en memoria
  shlq $48, %rax              # Paso intermedio para almacenarlo
  movq %rax, -8(%rsp)
  movsd -8(%rsp), %xmm1       # Se guarda en xmm1
  cvtsi2sdq %rdi, %xmm2       # Se convierte el arg. c a doble

  mulsd %xmm1, %xmm0          # xmm0 = f * 1.5
  addsd %xmm2, %xmm0          # xmm0 = xmm0 + c

  ret
  
