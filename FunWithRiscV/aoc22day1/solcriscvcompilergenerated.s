	.file	"solc.c"
	.option pic
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"r"
	.align	3
.LC1:
	.string	"input.txt"
	.align	3
.LC2:
	.string	"open failed"
	.align	3
.LC3:
	.string	"Elf count: %d\n"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-64
	sd	ra,56(sp)
	sd	s0,48(sp)
	addi	s0,sp,64
	lla	a1,.LC0
	lla	a0,.LC1
	call	fopen@plt
	mv	a5,a0
	sd	a5,-40(s0)
	ld	a5,-40(s0)
	bne	a5,zero,.L2
	lla	a0,.LC2
	call	perror@plt
	li	a5,1
	j	.L3
.L2:
	li	a2,2
	li	a1,0
	ld	a0,-40(s0)
	call	fseek@plt
	ld	a0,-40(s0)
	call	ftell@plt
	sd	a0,-32(s0)
	ld	a0,-40(s0)
	call	rewind@plt
	ld	a5,-32(s0)
	addi	a5,a5,1
	mv	a0,a5
	call	malloc@plt
	mv	a5,a0
	sd	a5,-24(s0)
	ld	a5,-24(s0)
	bne	a5,zero,.L4
	ld	a0,-40(s0)
	call	fclose@plt
	li	a5,1
	j	.L3
.L4:
	ld	a5,-32(s0)
	ld	a3,-40(s0)
	mv	a2,a5
	li	a1,1
	ld	a0,-24(s0)
	call	fread@plt
	ld	a5,-32(s0)
	ld	a4,-24(s0)
	add	a5,a4,a5
	sb	zero,0(a5)
	ld	a0,-40(s0)
	call	fclose@plt
	sw	zero,-56(s0)
	sw	zero,-52(s0)
	sd	zero,-48(s0)
	j	.L5
.L9:
	ld	a5,-48(s0)
	ld	a4,-24(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	mv	a4,a5
	li	a5,10
	bne	a4,a5,.L6
	ld	a5,-48(s0)
	addi	a5,a5,1
	ld	a4,-24(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	mv	a4,a5
	li	a5,10
	bne	a4,a5,.L6
	lw	a5,-52(s0)
	sext.w	a5,a5
	beq	a5,zero,.L8
	lw	a5,-56(s0)
	addiw	a5,a5,1
	sw	a5,-56(s0)
	sw	zero,-52(s0)
	j	.L8
.L6:
	ld	a5,-48(s0)
	ld	a4,-24(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	mv	a4,a5
	li	a5,10
	beq	a4,a5,.L8
	li	a5,1
	sw	a5,-52(s0)
.L8:
	ld	a5,-48(s0)
	addi	a5,a5,1
	sd	a5,-48(s0)
.L5:
	ld	a4,-48(s0)
	ld	a5,-32(s0)
	blt	a4,a5,.L9
	lw	a5,-52(s0)
	sext.w	a5,a5
	beq	a5,zero,.L10
	lw	a5,-56(s0)
	addiw	a5,a5,1
	sw	a5,-56(s0)
.L10:
	lw	a5,-56(s0)
	mv	a1,a5
	lla	a0,.LC3
	call	printf@plt
	ld	a0,-24(s0)
	call	free@plt
	li	a5,0
.L3:
	mv	a0,a5
	ld	ra,56(sp)
	ld	s0,48(sp)
	addi	sp,sp,64
	jr	ra
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
