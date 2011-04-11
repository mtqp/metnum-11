
section .data
	nro: dd 0,43.0

section .text
	global asm_watchDouble
	
asm_watchDouble:
	push ebp
	mov ebp,esp
	push edi
	push esi
	push ebx
	
break_asm:
	mov eax,nro
	movddup xmm0,[eax]

	finit
	fld1
	
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	
	
	
	
	
	
