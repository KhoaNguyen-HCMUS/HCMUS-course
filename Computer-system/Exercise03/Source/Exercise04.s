.extern printf
.extern scanf

.section .data
	noti_fmt: .asciz "Enter n: "
	pfmt: .asciz "%d\n"
	true_fmt: .asciz "%d is a symmetry number\n\n"
	false_fmt: .asciz "%d is not a symmetry number\n\n"
	sfmt: .asciz "%ld"

.section .bss
	n: .space 4
	sum: .space 4

.section .text
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

	bl _is_symmetry

	cmp x0, #1
	b.eq _print_true
	
	cmp x0, #0
	b.eq _print_false

	mov x0, xzr
	mov x8, #93
	svc #0

	.global _is_symmetry
_is_symmetry:
    sub sp, sp, #40
    stp x19, x20, [sp, #16]
    stp x21, x22, [sp, #0]
    str x30, [sp, #32]

    mov x19, x0 
    mov x20, #0 
    mov x23, #10 

_is_symmetry.loop:
    cbz x19, _is_symmetry.check

    udiv x21, x19, x23 
    msub x22, x21, x23, x19 

    mul x20, x20, x23
    add x20, x20, x22

    mov x19, x21
    b _is_symmetry.loop

_is_symmetry.check:
    cmp x0, x20
    cset x0, eq 
    b _is_symmetry.exit

_is_symmetry.exit:
    ldr x30, [sp, #32]
    ldp x21, x22, [sp, #0]
    ldp x19, x20, [sp, #16]
    add sp, sp, #40
    ret

_is_symmetry.true:
    mov x0, #1 
    b _is_symmetry.exit

_is_symmetry.false:
    mov x0, #0 
    b _is_symmetry.exit

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
