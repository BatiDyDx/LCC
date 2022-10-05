.data
custom_format: .asciz "%ld\n"
i: .quad 0xDEADBEEF

format_hex: .asciz "%X\n"


.text
.global main
main:
  movq $custom_format, %rdi  # El primer argumento es el formato.
  movq $1234, %rsi    # El valor a imprimir.
  xorq %rax, %rax     # Cantidad de valores de punto flotante.
  call printf

  # rsp
  movq $custom_format, %rdi
  movq %rsp, %rsi
  xorq %rax, %rax 
  call printf
  
  # &custom_format
  movq $custom_format, %rdi
  movq $custom_format, %rsi
  xorq %rax, %rax 
  call printf

  # &custom_format in hex
  movq $format_hex, %rdi
  movq $custom_format, %rsi
  xorq %rax, %rax 
  call printf
  
  # *rsp
  movq $custom_format, %rdi
  pushq $0xFFFF
  movq (%rsp), %rsi
  xorq %rax, %rax
  call printf

  # *(rsp + 8)
  movq $custom_format, %rdi
  movq 8(%rsp), %rcx
  movq (%rcx), %rsi
  xorq %rax, %rax
  call printf
  
  # i
  movq $custom_format, %rdi
  movq i, %rsi
  xorq %rax, %rax
  call printf
  
  # &i
  movq $custom_format, %rdi
  movq $i, %rsi
  xorq %rax, %rax
  call printf

  ret

