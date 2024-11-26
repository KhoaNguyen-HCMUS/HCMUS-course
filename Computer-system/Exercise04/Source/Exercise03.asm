extern printf
extern scanf

section .data
    noti1 db "Enter n: ", 0
    noti2 db "%d is a square number", 10, 10, 0       
    noti3 db "%d is not a square number", 10, 10, 0 
    fmt db "%d", 0

section .bss
    n resd 1
    i resd 1

section .text
    global main

main:
    push noti1
    call printf
    add esp, 4

    push n            
    push fmt
    call scanf
    add esp, 8

    push dword [n]          
    call _is_square
    add esp, 4

    mov [i], eax

    cmp dword [i], 1
    jne _false

_true:
	push dword[n]
    push noti2
    call printf
    add esp, 8
    jmp _end

_false:
	push dword[n]
    push noti3
    call printf
    add esp, 4

_end:
    xor eax, eax
    ret

global _is_square
_is_square:
    push ebp
    mov ebp, esp
    push esi
    push edi

    mov eax, [ebp + 8]    
    cmp eax, 0
    jl _is_square.false   
    je _is_square.true           

	mov esi, 1  

_is_square.loop:
	mov edi, esi		 
	imul edi, edi       
	cmp edi, [ebp + 8] 
	jg _is_square.false 
	je _is_square.true  

    inc esi                
    jmp _is_square.loop

_is_square.true:
    mov eax, 1
    jmp _is_square.end

_is_square.false:
    mov eax, 0
	jmp _is_square.end

_is_square.end:
    pop edi
    pop esi
    pop ebp
    ret