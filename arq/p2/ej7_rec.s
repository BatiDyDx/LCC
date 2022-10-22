.text
.global fact_rec
fact_rec:
  cmpq $0, %rdi
  jne retorno_recursivo
  movq $1, %rax
  ret
retorno_recursivo:
  decq %rdi
  call fact_rec
  incq %rdi
  mulq %rdi
  ret

