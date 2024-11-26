extern printf
extern scanf

section .data 
    noti1 db "Enter n: ", 0
    noti2 db "%d is a perfect number", 10, 10, 0
    noti3 db "%d is not a perfect number", 10, 10, 0
    fmt db "%d", 0

section .bss
    n resd 1
    i resd 1
    s resd 1

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

    push dword[n]
    call _is_perfect
    mov dword[i], eax

    cmp dword[i], 1
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
    add esp, 8

_end:
    xor eax, eax
    ret

global _is_perfect
_is_perfect:
    push ebp 
    mov ebp, esp
    push esi

    mov esi, 1 
    mov dword[s], 0
    cmp dword[ebp + 8], 1
    jle _is_perfect.false
    
    
_is_perfect.loop:
    xor edx, edx     
    mov eax, dword[ebp + 8]
    div esi 
    cmp edx, 0
    jne _is_perfect.cont
    mov eax, dword[s]
    add eax, esi
    mov dword[s], eax

_is_perfect.cont:
    inc esi 
    cmp esi, dword[ebp + 8]
    jl _is_perfect.loop

    mov eax, dword[s]
    cmp eax, dword[ebp + 8]
    jne _is_perfect.false

_is_perfect.true:
    mov eax, 1
    jmp _is_perfect.end

_is_perfect.false:
    mov eax, 0

_is_perfect.end:
    pop esi
    pop ebp
    ret