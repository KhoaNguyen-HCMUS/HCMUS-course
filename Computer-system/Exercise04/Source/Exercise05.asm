extern printf
extern scanf

section .data
    sfmt db "%d", 0
    pfmt db "%d", 0
    pfmt2 db "%d ", 0
    choose_fmt db "%d", 0

    menu.fmt db " ",10 ,"----------------MENU----------------", 10, "1. Output array", 10, "2. List prime numbers", 10, "3. Find max value", 10, "4. Calculate average value", 10, "5. Exit", 10, "------------------------------------", 10, "Choose: ", 0
    noti_fmt db "Enter number of elements in array: ", 0
	invalid_fmt db "Invalid choice, please choose again", 10, 0
    in_ai_fmt db "Enter a[%d]: ", 0
    out_ai_fmt db "a[%d] = %d", 10, 0
    output_fmt db "Value in array: ", 10, 0
    one_prime_fmt db "is prime number in array ", 10, 0
    have_prime_fmt db "are prime numbers in array ", 10, 0
    not_prime_fmt db "There are no prime numbers in the array", 10, 0
    max_fmt db "The max value in array: %d", 10, 0
    avg_fmt db "The average value of array: %d", 10, 0

section .bss
    arr resd 100
    n resd 1
    choose resd 1


section .text
    global menu
    global input_array
    global output_array
    global list_primes
    global is_prime
    global find_max
    global calculate_avg
    global main

main:
    push noti_fmt
    call printf
    add esp, 4

    push n
    push sfmt
    call scanf
    add esp, 8

    mov ebx,arr 
    mov esi,0

input_loop:
    push esi
    push in_ai_fmt
    call printf
    
    push ebx
    push sfmt
    call scanf
    
    add ebx,4
    inc esi
    cmp esi, [n]
    jl input_loop
    
	call menu
	
	xor eax, eax
	ret

menu:
    push menu.fmt
    call printf
    add esp, 4

    push choose
    push choose_fmt
    call scanf
    add esp, 8

    mov eax, [choose]

    cmp eax, 1
    je menu.output

    cmp eax, 2
    je menu.list_primes

    cmp eax, 3
    je menu.find_max

    cmp eax, 4
    je menu.calculate_avg

    cmp eax, 5
    je menu.exit

	push invalid_fmt
	call printf
	add esp, 4

    jmp menu

menu.output:
    push dword [n]
    push dword arr
    call output_array
    jmp menu

menu.list_primes:
    push dword [n]
    push dword arr
    call list_primes
    jmp menu

menu.find_max:
    push dword [n]
    push dword arr
    call find_max
    jmp menu

menu.calculate_avg:
    push dword [n]
    push dword arr
    call calculate_avg
    jmp menu

menu.exit:
    xor eax, eax
    ret

output_array:
    push output_fmt
	call printf
	add esp, 4

	mov ebx, arr
	mov esi, 0

output_array.loop:
    push dword [ebx]
	push pfmt2
	call printf
	add esp, 8

	add ebx, 4
	inc esi
	cmp esi, [n]
	jl output_array.loop

	xor eax, eax
	ret

list_primes:
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ebx

    mov esi, [ebp + 8] 
    xor edi, edi
    xor ebx, ebx


list_prime.loop:
    cmp edi, [ebp + 12]
    jge list_prime.end

    push dword [esi]
    call is_prime
    add esp, 4

    cmp eax, 0 	
    je list_prime.loop.next

    inc ebx
    push dword [esi]
    push pfmt2
    call printf
    add esp, 8

list_prime.loop.next:
	inc edi
    add esi, 4
    jmp list_prime.loop

list_prime.end:
    cmp ebx, 0
    je list_prime.not_prime

    cmp ebx, 1
    je list_prime.one_prime

    jmp list_prime.have_prime

list_prime.one_prime:
    push one_prime_fmt
    call printf
    add esp, 4
    jmp list_prime.exit

list_prime.not_prime:
    push not_prime_fmt
    call printf
    add esp, 4
    jmp list_prime.exit

list_prime.have_prime:
    push have_prime_fmt
    call printf
    add esp, 4
    jmp list_prime.exit

list_prime.exit:
    pop ebx
    pop edi
    pop esi
    pop ebp
    ret


is_prime:
    push ebp
    mov ebp, esp
    push ebx
    push ecx
    push edx

    mov eax, [ebp + 8]
    cmp eax, 2
    jl is_prime.false

    cmp eax, 3
    jle is_prime.true

    mov ecx, 2

is_prime.loop:
    mov ebx, ecx
    imul ebx, 2
    cmp ebx, [ebp + 8]
    jg is_prime.true

    mov eax, [ebp + 8]
    xor edx, edx
    div ecx
    cmp edx, 0
    je is_prime.false

    inc ecxc
    jmp is_prime.loop

is_prime.true:
    mov eax, 1
    jmp is_prime.end

is_prime.false:
    mov eax, 0
    jmp is_prime.end

is_prime.end:
    pop edx
    pop ecx
    pop ebx
    pop ebp
    ret


find_max:
    push ebp
    mov ebp, esp
    push esi
    push edi

    mov esi, [ebp + 8] 
	mov ecx, [ebp + 12] 
    mov eax, [esi]
    xor edi, edi

find_max.loop:
    cmp edi, ecx
    jge find_max.end

    cmp eax, [esi]
    jge find_max.skip

    mov eax, [esi]

find_max.skip:
    add esi, 4
    inc edi
    jmp find_max.loop

find_max.end:
    push eax
    push max_fmt
    call printf
    add esp, 8

    pop edi
    pop esi
    pop ebp
    ret

calculate_avg:
    push ebp
    mov ebp, esp
    push esi
    push edi

    mov esi, [ebp + 8] 
	mov ecx, [ebp + 12] 
    xor eax, eax
    xor edx, edx
    xor edi, edi

calculate_avg.loop:
    cmp edi, ecx
    jge calculate_avg.end

    add eax, [esi]
    add esi, 4
    inc edi
    jmp calculate_avg.loop

calculate_avg.end:
    cdq
    idiv ecx

    push eax
    push avg_fmt
    call printf
    add esp, 8

    pop edi
    pop esi
    pop ebp
    ret
