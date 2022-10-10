.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10
format: .asciz "%d\n"

.text
sum:
  xorl %eax, %eax    # Suma = 0
  movq $0,   %rcx    # i = 0
sum_loop:
  addl (%rdi,%rcx,4), %eax  # eax = eax + list[i]
  incb %cl                  # i++
  cmpb %sil, %cl
  jnz sum_loop              # si i < length, repetir
  ret

min:
  movl (%rdi), %eax          # eax = list[0]
  movq $0,     %rcx          # i = 0
min_loop:
  incb %cl                   # i++
  cmpb %sil, %cl
  je min_return              # si i == length, retornar
  movl (%rdi,%rcx,4), %ebx   # ebx = list[i]
  cmpl %ebx, %eax
  cmovg %ebx, %eax           # si eax > ebx, entonces eax = ebx
  jmp min_loop
min_return:
  ret

max:
  movq %rsi, %rcx           # i = length
  decb %cl                  # i--
  movl (%rdi), %eax         # eax = list[0]
max_loop:
  movl (%rdi,%rcx,4), %ebx  # ebx = list[i]
  cmpl %ebx, %eax
  cmovl %ebx, %eax          # si eax < ebx, entonces eax = ebx
  loop max_loop             # si i = 1, ya se recorrieron todos los elementos 
  ret                       # Notar que el caso i = 0 se hace fuera del ciclo

avg:
  call sum            # eax = suma de la lista
  movl %eax, %edx     # edx = eax
  shr  $16,   %edx    # dx:ax = eax
  movl %esi, %ebx     # ebx = length (usamos movl para que el resto del registro quede en 0)
  idivw %bx           # ax = (eax / length)
  ret

prepare_list_arguments:
  leaq list, %rdi
  xorq %rsi, %rsi
  movb length, %sil
  ret

prepare_printf:
  movq %rax, %rsi
  leaq format, %rdi
  xorq %rax, %rax
  ret 

.global main
main:
  # Suma
  call prepare_list_arguments
  call sum
  call prepare_printf
  call printf

  # Promedio  
  call prepare_list_arguments
  call avg
  call prepare_printf
  call printf
  
  # Minimo
  call prepare_list_arguments
  call min
  call prepare_printf
  call printf
  
  # Maximo
  call prepare_list_arguments
  call max
  call prepare_printf
  call printf

  ret

