.extern printf
.extern scanf

.data
	noti_fmt: .asciz "Enter n: "
	pfmt: .asciz "%d\n"
  	true_fmt: .asciz "%d is a square number\n\n"
	false_fmt: .asciz "%d is not a square number\n\n"
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

	bl _is_square

	cmp x0, #1
	b.eq _print_true
	
	cmp x0, #0
	b.eq _print_false

	mov x0, xzr
	mov x8, #93
	svc #0

.global _is_square
_is_square:
	sub sp,sp,#8
	str x30,[sp]
	
	sub sp,sp,#8
	str x19,[sp]
	
	sub sp,sp,#8
	str x20,[sp]

    cmp x0, #0
    blt _is_square.false

    cmp x0, #0
    beq _is_square.true

    cmp x0, #1
    beq _is_square.true

    mov x19, xzr 

_is_square.loop:
    mul x20, x19, x19
    cmp x20, x0
    b.ge _is_square.end

    add x19, x19, #1
    b _is_square.loop

_is_square.end:
    cmp x20, x0
    beq _is_square.true
    b _is_square.false

_is_square.true:
    mov x0, #1 
    b _is_square.exit

_is_square.false:
    mov x0, #0 
    b _is_square.exit

_is_square.exit:
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
	