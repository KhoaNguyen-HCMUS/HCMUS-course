extern printf
extern scanf

section .data
    noti1 db "Enter n: ", 0
    noti2 db "%d is a palindrome number", 10, 10, 0       
    noti3 db "%d is not a palindrome number", 10, 10, 0 
    fmt db "%d", 0

section .bss
    n resd 1
    reversed resd 1
    original resd 1

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

    mov eax, [n]
    mov [original], eax

    push dword [n]          
    call _reverse_number
    add esp, 4

    mov [reversed], eax

    mov eax, [original]
    cmp eax, [reversed]
    jne _false

_true:
    push dword [n]
    push noti2
    call printf
    add esp, 8
    jmp _end

_false:
    push dword [n]
    push noti3
    call printf
    add esp, 8

_end:
    xor eax, eax
    ret

global _reverse_number
_reverse_number:
    push ebp
    mov ebp, esp
    push ebx
    push ecx
    push edx

    mov eax, [ebp + 8]    
    mov ebx, 0            

_reverse_number.loop:
    cmp eax, 0
    je _reverse_number.end_loop

    xor edx, edx
	mov ecx, 10
	div ecx				
	imul ebx, 10		
	add ebx, edx		

    jmp _reverse_number.loop

_reverse_number.end_loop:
    mov eax, ebx
    pop edx
    pop ecx
    pop ebx
    pop ebp
    ret