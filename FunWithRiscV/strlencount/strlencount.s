.global _start
.section .text

_start:
print_starting:
	la a1, starting
	li a2, 9
	li a7, 64        # print
	ecall

	li t0, '\0'
	li t1, 'a'
	li t2, 20
	bne t0, t1, bnottaken

	li a0, 0
	li a7, 93 
	ecall

bnottaken:
        la   a1, hello
        li   a2, 13
        li   a7, 64
				addi t2, t2, -1 # decrement t2
        ecall
				j _start

btaken:
        la a1, nolo
        li a2, 7
        li a7, 64
				ecall
				j _start

.section .data
starting: .ascii "starting\n"
hello:    .ascii "hello world!\n"
nolo:     .ascii "nolo!!\n"
