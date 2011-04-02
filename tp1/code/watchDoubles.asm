
section .data
	nro: dd 0,2.0

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

	
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	
