.extern scanf
.extern printf

.section .data
    sfmt: .asciz "%ld"
    pfmt: .asciz "%d\n"
    pfmt2: .asciz "%d "
    choose_fmt: .asciz "%ld"

    menu_fmt: .asciz "\n----------------MENU----------------\n1. Display array\n2. List prime numbers in array\n3. Find the max value in array\n4. Calculate the average value of array \n5. Exit\n------------------------------------\nEnter your choose: "
    noti_fmt: .asciz "Enter number of elements in array: "
    in_ai_fmt: .asciz "Enter a[%d]: "
    out_ai_fmt: .asciz "a[%d] = %d\n"
    output_fmt: .asciz "Value in array: "
    one_prime_fmt: .asciz "is prime number in array \n"
    have_prime_fmt: .asciz "are prime numbers in array \n"
	not_prime_fmt: .asciz "There are no prime numbers in the array\n"
    max_fmt: .asciz "The max value in array: %d\n"
    avg_fmt: .asciz "The average value of array: %d\n"

.section .bss
    arr: .space 800
    n: .space 8
    choose: .space 8

.section .text
    .global menu
    .global input_array
    .global output_array
    .global list_primes
	.global is_prime
    .global find_max
    .global calculate_avg
    .global main

main:
    adrp x0, noti_fmt
    add x0, x0, :lo12:noti_fmt
    bl printf

    adrp x0, sfmt
    add x0, x0, :lo12:sfmt
    adrp x1, n
    add x1, x1, :lo12:n
    bl scanf

    adrp x0, n
    add x0, x0, :lo12:n
    ldr x0, [x0]
    adrp x1, arr
    add x1, x1, :lo12:arr
    bl input_array

    bl menu

    mov x0, xzr
    mov x8, #93
    svc #0

menu:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]

    adrp x0, menu_fmt
    add x0, x0, :lo12:menu_fmt
    bl printf

    adrp x0, choose_fmt
    add x0, x0, :lo12:choose_fmt
    adrp x1, choose
    add x1, x1, :lo12:choose
    bl scanf

    adrp x19, choose
    add x19, x19, :lo12:choose
    ldr x19, [x19]

    cmp x19, #1
    b.eq menu.output

    cmp x19, #2
    b.eq menu.list_primes

    cmp x19, #3
    b.eq menu.find_max

    cmp x19, #4
    b.eq menu.calculate_avg

    cmp x19, #5
    b.eq menu.exit

    b menu

menu.output:
    sub sp, sp, #8
    stur x30, [sp]

    adrp x0, n
    add x0, x0, :lo12:n
    ldr x0, [x0]
    adrp x1, arr
    add x1, x1, :lo12:arr

    bl output_array

    ldur x30, [sp]
    add sp, sp, #8

    b menu

menu.list_primes:
    sub sp, sp, #8
    stur x30, [sp]

    adrp x0, n
    add x0, x0, :lo12:n
    ldr x0, [x0]
    adrp x1, arr
    add x1, x1, :lo12:arr

    bl list_primes

    ldur x30, [sp]
    add sp, sp, #8

    b menu

menu.find_max:
    sub sp, sp, #8
    stur x30, [sp]

    adrp x0, n
    add x0, x0, :lo12:n
    ldr x0, [x0]
    adrp x1, arr
    add x1, x1, :lo12:arr

    bl find_max

    ldur x30, [sp]
    add sp, sp, #8

    b menu

menu.calculate_avg:
    sub sp, sp, #8
    stur x30, [sp]

    adrp x0, n
    add x0, x0, :lo12:n
    ldr x0, [x0]
    adrp x1, arr
    add x1, x1, :lo12:arr

    bl calculate_avg

    ldur x30, [sp]
    add sp, sp, #8

    b menu

menu.exit:
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8

    ret

input_array:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]
    sub sp, sp, #8
    stur x20, [sp]
    sub sp, sp, #8
    stur x21, [sp]

    mov x19, x0 
    mov x20, x1
    mov x21, xzr 

input_array.loop:
    cmp x21, x19
    b.ge input_array.exit

    adrp x0, in_ai_fmt
    add x0, x0, :lo12:in_ai_fmt
    mov x1, x21
    bl printf

    adrp x0, sfmt
    add x0, x0, :lo12:sfmt
    mov x1, x20
    bl scanf

    add x20, x20, #8 
    add x21, x21, #1 
    b input_array.loop

input_array.exit:
    ldur x21, [sp]
    add sp, sp, #8
    ldur x20, [sp]
    add sp, sp, #8
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8
    ret

output_array:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]
    sub sp, sp, #8
    stur x20, [sp]
    sub sp, sp, #8
    stur x21, [sp]

    mov x19, x0 
    mov x20, x1
    mov x21, xzr 

output_array.loop:
    cmp x21, x19
    b.ge output_array.exit

    adrp x0, out_ai_fmt
    add x0, x0, :lo12:out_ai_fmt
    mov x1, x21
    mov x2, x20
    ldr x2, [x2]
    bl printf

    add x20, x20, #8 
    add x21, x21, #1 
    b output_array.loop

output_array.exit:
    ldur x21, [sp]
    add sp, sp, #8
    ldur x20, [sp]
    add sp, sp, #8
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8
    ret
is_prime:
	sub sp,sp,#8
	str x30,[sp]
	
	sub sp,sp,#8
	str x19,[sp]
	
	sub sp,sp,#8
	str x20,[sp]

	sub sp,sp,#8
	str x21,[sp]

	sub sp,sp,#8
	str x22,[sp]
    cmp x0, #2
    blt is_prime.false

    cmp x0, #2
    beq is_prime.true

    cmp x0, #3
    beq is_prime.true

    mov x19, #2 
    udiv x20, x0, x19 

is_prime.loop:
    udiv x21, x0, x19
    mul x22, x21, x19
    cmp x22, x0
    b.eq is_prime.false 

    add x19, x19, #1
    cmp x19, x20
    b.lt is_prime.loop 

is_prime.true:
    mov x0, #1 
    b is_prime.exit

is_prime.false:
    mov x0, #0 
    b is_prime.exit

is_prime.exit:
    ldr x22, [sp]
    add sp, sp, #8

    ldr x21, [sp]
    add sp, sp, #8

    ldr x20, [sp]
    add sp, sp, #8

    ldr x19, [sp]
    add sp, sp, #8

    ldr x30, [sp]
    add sp, sp, #8

    ret


list_primes:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]
    sub sp, sp, #8
    stur x20, [sp]
    sub sp, sp, #8
    stur x21, [sp]
    sub sp, sp, #8
    stur x22, [sp]

    mov x19, x0 
    mov x20, x1 
    mov x21, xzr
    mov x22, xzr

list_primes.loop:
    cmp x21, x19
    b.ge list_primes.end

    ldr x0, [x20, x21, LSL #3] 
    bl is_prime
    cmp x0, #0 
    b.eq not_prime

    add x22, x22, #1 
    adrp x0, pfmt2
    add x0, x0, :lo12:pfmt2
    ldr x1, [x20, x21, LSL #3]
    bl printf

not_prime:
    add x21, x21, #1 
    b list_primes.loop

list_primes.end:
    cmp x22, #0
    b.eq list_primes.not_prime

    cmp x22, #1
    b.eq list_primes.one_prime

    b list_primes.have_prime

list_primes.one_prime:
    adrp x0, one_prime_fmt
    add x0, x0, :lo12:one_prime_fmt
    bl printf
    b list_primes.exit

list_primes.not_prime:
    adrp x0, not_prime_fmt
    add x0, x0, :lo12:not_prime_fmt
    bl printf
    b list_primes.exit

list_primes.have_prime:
    adrp x0, have_prime_fmt
    add x0, x0, :lo12:have_prime_fmt
    bl printf
    b list_primes.exit


list_primes.exit:
    ldur x22, [sp]
    add sp, sp, #8
    ldur x21, [sp]
    add sp, sp, #8
    ldur x20, [sp]
    add sp, sp, #8
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8

    ret


find_max:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]
    sub sp, sp, #8
    stur x20, [sp]
    sub sp, sp, #8
    stur x21, [sp]

    mov x19, x0 
    mov x20, x1 
    mov x21, xzr 
    mov x22, xzr 

find_max.loop:
    cmp x21, x19
    b.ge find_max.exit

    ldr x0, [x20]
    cmp x0, x22
    ble not_max
    mov x22, x0

not_max:
    add x20, x20, #8 
    add x21, x21, #1 
    b find_max.loop

find_max.exit:
    adrp x0, max_fmt
    add x0, x0, :lo12:max_fmt
    mov x1, x22
    bl printf

    ldur x21, [sp]
    add sp, sp, #8
    ldur x20, [sp]
    add sp, sp, #8
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8
    ret

calculate_avg:
    sub sp, sp, #8
    stur x30, [sp]

    sub sp, sp, #8
    stur x19, [sp]
    sub sp, sp, #8
    stur x20, [sp]
    sub sp, sp, #8
    stur x21, [sp]

    mov x19, x0 
    mov x20, x1 
    mov x21, xzr 
    mov x22, xzr 

calculate_avg.loop:
    cmp x21, x19
    b.ge calculate_avg.exit

    ldr x0, [x20]
    add x22, x22, x0

    add x20, x20, #8 
    add x21, x21, #1 
    b calculate_avg.loop

calculate_avg.exit:
    udiv x22, x22, x19

    adrp x0, avg_fmt
    add x0, x0, :lo12:avg_fmt
    mov x1, x22
    bl printf

    ldur x21, [sp]
    add sp, sp, #8
    ldur x20, [sp]
    add sp, sp, #8
    ldur x19, [sp]
    add sp, sp, #8

    ldur x30, [sp]
    add sp, sp, #8
    ret

