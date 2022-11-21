@ Determinante de matriz [[a b], [c d]]
@ donde los argumentos se pasan en orden por fila y luego columna

.global det22
det22:
  vmul.f32 s0, s0, s3  @ s0 = a * d
  vmul.f32 s1, s1, s2  @ s1 = b * c
  vsub.f32 s0, s0, s1  @ s0 = a * d - b * c
  bx lr

