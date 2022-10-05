.text

.global fact_iter
fact_iter:
  movq $1, %rax
  movq $0, %rcx  # i = 0
  cmpq %rcx, %rdi
  je return
fact_loop:
  incq %rcx
  mulq %rcx
  cmpq %rcx, %rdi
  jne fact_loop
return:
  ret

