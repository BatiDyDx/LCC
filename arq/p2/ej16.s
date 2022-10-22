.data
a: .word -1
b: .byte 0xaa, 99
c: .float 1.5
str: .asciz "Hola mundo\n"

.text
.global main
main:
leaq a, %rdx
movw $0xffff, %ax  # ax = 0xffff
movb $0x63, %al    # al = 0x63
movl $0x486f6c61 %esi # esi = "Hola"
movl $0x3fc00000   # edi = 0x3fc00000
movl %esi, (%rdi)
retq
