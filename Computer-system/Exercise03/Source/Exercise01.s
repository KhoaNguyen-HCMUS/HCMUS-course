.extern printf
.extern scanf

.data
	noti_fmt: .asciz "Enter n: "

	pfmt: .asciz "%d\n"
  	true_fmt: .asciz "%d is a prime number\n\n"
	false_fmt: .asciz "%d is not a prime number\n\n"
	sfmt: .asciz "%ld"


.bss
	n: .space 4

.text
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

	adrp x0, pfmt
	add x0, x0, :lo12:pfmt
	adrp x1, n 
	add x1, x1, :lo12:n	
	ldr x1, [x1]
	bl printf

	adrp x0, n
	add x0, x0, :lo12:n
	ldr x0, [x0]

	bl _is_prime

	cmp x0, #1
	b.eq _print_true
	
	cmp x0, #0
	b.eq _print_false


	mov x0, xzr
	mov x8, #93
	svc #0

.global _is_prime
_is_prime:
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
    blt _is_prime.false

    cmp x0, #2
    beq _is_prime.true

    cmp x0, #3
    beq _is_prime.true

    mov x19, #2 
    udiv x20, x0, x19 

_is_prime.loop:
    udiv x21, x0, x19
    mul x22, x21, x19
    cmp x22, x0
    beq _is_prime.false

    add x19, x19, #1
    cmp x19, x20
    blt _is_prime.loop

_is_prime.true:
    mov x0, #1 
    b _is_prime.exit

_is_prime.false:
    mov x0, #0 
    b _is_prime.exit

_is_prime.exit:
	
	ldr x22,[sp]
	add sp,sp,#8
	
	ldr x21,[sp]
	add sp,sp,#8

	ldr x20,[sp]
	add sp,sp,#8

	ldr x19,[sp]
	add sp,sp,#8

	ldr x30,[sp]
	add sp,sp,#8

    ret

.global _print_true
_print_true:
	sub x28, x28, #8 
	stur x30, [x28] 

	adrp x0, true_fmt
	add x0, x0, :lo12:true_fmt
	adrp x1, n
	add x1, x1, :lo12:n
	ldr x1, [x1]
	bl printf
	
	ldur x30, [x28] 
	add x28, x28, #8 
	ret

.global _print_false
_print_false:
	sub x28, x28, #8 
	stur x30, [x28] 

    adrp x0, false_fmt
    add x0, x0, :lo12:false_fmt
	adrp x1, n
	add x1, x1, :lo12:n
	ldr x1, [x1]
    bl printf

	ldur x30, [x28] 
	add x28, x28, #8 
	ret
