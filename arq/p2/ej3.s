.global main
main:
  movb $100, %ah  # N1
	movb $120, %al  # N2
	addb %ah, %al   # S1 = N1 + N2

	movb $-63, %bh  # N3
	movb $-56, %bl  # N4
	addb %bh, %bl   # S2 = N3 + N4

	movb $-91, %cl  # N5
	addb %bh, %cl   # S3 = N3 + N5

	movb $120, %al  # N2
	movb $-56, %bl  # N4
  subb %bl, %al   # S4 = N2 - N4

  movb $120, %al  # N2
	movb $-91, %cl  # N5
	subb %al, %cl   # S5 = N5 - N2

