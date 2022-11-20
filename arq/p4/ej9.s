@ Algoritmo del campesino ruso

.global campesino_ruso
campesino_ruso:
  eor r2, r2, r2  @ eor = 0
  
while_start:
  cmp r1, #1
  bls while_end

  tst r1, #1
  addne r2, r2, r0
  subne r1, r1, #1
  lsleq r0, r0, #1
  lsreq r1, r1, #1
  b while_start

while_end:
  add r0, r2, r0
  bx lr

