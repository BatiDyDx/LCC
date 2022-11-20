@ Determinante de matriz [[a b], [c d]]
@ donde los argumentos se pasan en orden por fila y luego columna

.global det22
det22:
  mul r0, r0, r3  @ r0 = a * d
  mul r1, r1, r2  @ r1 = b * c
  sub r0, r0, r1  @ r0 = a * d - b * c
  bx lr

