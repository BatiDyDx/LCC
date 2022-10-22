.data
format_args: .asciz "Cantidad de argumentos ingresados: %d. La suma es %d."
format_noargs: .asciz "Ingrese al menos un arguento."

.text
sum:
  xorq %rbx, %rbx  # rdx = suma
  movq %rdi, %rcx
  decq %rcx
  pushq %rdi

sum_loop:
  movq (%rsi, %rcx, 8), %rdi
  call square_str
  addq %rax, %rbx
  loop sum_loop

  movq %rbx, %rax
  popq %rdi
  ret

square_str:
  # Dada una cadena representando un entero
  # retorna el entero al cuadrado
  pushq %rcx
  pushq %rsi

  call atoi
  mulq %rax

  popq %rsi
  popq %rcx
  ret

.global main
main:
  cmp $1, %rdi
  je no_args 
  jmp args

no_args:
  xorq %rax, %rax
  leaq format_noargs, %rdi
  call printf
  ret

args:
  call sum
  movq %rax, %rdx
  xorq %rax, %rax
  movq %rdi, %rsi
  leaq format_args, %rdi
  call printf
  ret

