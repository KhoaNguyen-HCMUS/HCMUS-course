extern printf
extern scanf

section .data
    noti1 db "Enter n: ", 0
    noti2 db "%d is a prime number", 10, 10, 0       
    noti3 db "%d is not a prime number", 10, 10, 0 
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
    call _is_prime
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

global _is_prime
_is_prime:
    push ebp
    mov ebp, esp
    push esi
    push edi

    mov eax, [ebp + 8]    
    cmp eax, 2
    jl _is_prime.false          
    je _is_prime.true           

	mov esi, 2  

_is_prime.loop:
    mov edi, esi		 
	imul edi, 2			
	cmp edi, [ebp + 8]  
	jg _is_prime.true

    mov eax, [ebp + 8]     
    xor edx, edx
    div esi                
    cmp edx, 0
    je _is_prime.false           

    inc esi                
    jmp _is_prime.loop

_is_prime.true:
    mov eax, 1
    jmp _is_prime.end

_is_prime.false:
    mov eax, 0
	jmp _is_prime.end

_is_prime.end:
    pop edi
    pop esi
    pop ebp
    ret