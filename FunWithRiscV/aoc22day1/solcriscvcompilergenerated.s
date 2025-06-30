.file	"solc.c"                    # Source file name
	.option pic                     # Enable position-independent code
	.text                           # Code section
	.section	.rodata             # Read-only data section
	.align	3                       # Align to 8-byte boundary
.LC0:                               # String literal label
	.string	"r"                     # File open mode string "r"
	.align	3                       # Align to 8-byte boundary
.LC1:                               # String literal label
	.string	"sample.txt"            # Filename string
	.align	3                       # Align to 8-byte boundary
.LC2:                               # String literal label
	.string	"open failed"           # Error message string
	.align	3                       # Align to 8-byte boundary
.LC3:                               # String literal label
	.string	"Elf count: %d\n"       # Printf format string
	.text                           # Switch back to code section
	.align	1                       # Align to 2-byte boundary
	.globl	main                    # Make main globally visible
	.type	main, @function         # Declare main as function
main:                               # Main function entry point
	addi	sp,sp,-64               # Allocate 64 bytes on stack (stack frame)
	sd	ra,56(sp)                   # Save return address at sp+56
	sd	s0,48(sp)                   # Save frame pointer at sp+48
	addi	s0,sp,64                # Set frame pointer (s0 = sp + 64)
	lla	a1,.LC0                     # Load address of "r" string into a1
	lla	a0,.LC1                     # Load address of "sample.txt" into a0
	call	fopen@plt               # Call fopen("sample.txt", "r")
	mv	a5,a0                       # Move fopen result to a5
	sd	a5,-40(s0)                  # Store file pointer at s0-40
	ld	a5,-40(s0)                  # Load file pointer from s0-40
	bne	a5,zero,.L2                 # If file pointer != NULL, jump to .L2
	lla	a0,.LC2                     # Load address of "open failed" string
	call	perror@plt              # Call perror("open failed")
	li	a5,1                        # Load immediate 1 into a5 (exit code)
	j	.L3                         # Jump to function exit
.L2:                                # File opened successfully
	li	a2,2                        # Load immediate 2 (SEEK_END)
	li	a1,0                        # Load immediate 0 (offset)
	ld	a0,-40(s0)                  # Load file pointer
	call	fseek@plt               # Call fseek(file, 0, SEEK_END)
	ld	a0,-40(s0)                  # Load file pointer
	call	ftell@plt               # Call ftell(file) to get file size
	sd	a0,-32(s0)                  # Store file size at s0-32
	ld	a0,-40(s0)                  # Load file pointer
	call	rewind@plt              # Call rewind(file) to go back to start
	ld	a5,-32(s0)                  # Load file size
	addi	a5,a5,1                 # Add 1 for null terminator
	mv	a0,a5                       # Move size to a0
	call	malloc@plt              # Call malloc(size+1)
	mv	a5,a0                       # Move malloc result to a5
	sd	a5,-24(s0)                  # Store buffer pointer at s0-24
	ld	a5,-24(s0)                  # Load buffer pointer
	bne	a5,zero,.L4                 # If malloc succeeded, jump to .L4
	ld	a0,-40(s0)                  # Load file pointer
	call	fclose@plt              # Call fclose(file)
	li	a5,1                        # Load immediate 1 (exit code)
	j	.L3                         # Jump to function exit
.L4:                                # Memory allocated successfully
	ld	a5,-32(s0)                  # Load file size
	ld	a3,-40(s0)                  # Load file pointer into a3
	mv	a2,a5                       # Move file size to a2 (count)
	li	a1,1                        # Load immediate 1 (size of each element)
	ld	a0,-24(s0)                  # Load buffer pointer
	call	fread@plt               # Call fread(buffer, 1, filesize, file)
	ld	a5,-32(s0)                  # Load file size
	ld	a4,-24(s0)                  # Load buffer pointer
	add	a5,a4,a5                    # Calculate buffer + filesize
	sb	zero,0(a5)                  # Store null terminator at end of buffer
	ld	a0,-40(s0)                  # Load file pointer
	call	fclose@plt              # Call fclose(file)
	sw	zero,-56(s0)                # Initialize elf_count = 0 at s0-56
	sw	zero,-52(s0)                # Initialize has_content = 0 at s0-52
	sd	zero,-48(s0)                # Initialize i = 0 at s0-48 (loop counter)
	j	.L5                         # Jump to loop condition check
.L9:                                # Main processing loop body
	ld	a5,-48(s0)                  # Load loop counter i
	ld	a4,-24(s0)                  # Load buffer pointer
	add	a5,a4,a5                    # Calculate buffer[i] address
	lbu	a5,0(a5)                    # Load unsigned byte buffer[i]
	mv	a4,a5                       # Move character to a4
	li	a5,10                       # Load immediate 10 (newline character)
	bne	a4,a5,.L6                   # If buffer[i] != '\n', jump to .L6
	ld	a5,-48(s0)                  # Load loop counter i
	addi	a5,a5,1                 # Calculate i+1
	ld	a4,-24(s0)                  # Load buffer pointer
	add	a5,a4,a5                    # Calculate buffer[i+1] address
	lbu	a5,0(a5)                    # Load unsigned byte buffer[i+1]
	mv	a4,a5                       # Move character to a4
	li	a5,10                       # Load immediate 10 (newline character)
	bne	a4,a5,.L6                   # If buffer[i+1] != '\n', jump to .L6
	lw	a5,-52(s0)                  # Load has_content flag
	sext.w	a5,a5                   # Sign extend to word
	beq	a5,zero,.L8                 # If has_content == 0, jump to .L8
	lw	a5,-56(s0)                  # Load elf_count
	addiw	a5,a5,1                 # Increment elf_count
	sw	a5,-56(s0)                  # Store updated elf_count
	sw	zero,-52(s0)                # Reset has_content = 0
	j	.L8                         # Jump to loop increment
.L6:                                # Character is not double newline
	ld	a5,-48(s0)                  # Load loop counter i
	ld	a4,-24(s0)                  # Load buffer pointer
	add	a5,a4,a5                    # Calculate buffer[i] address
	lbu	a5,0(a5)                    # Load unsigned byte buffer[i]
	mv	a4,a5                       # Move character to a4
	li	a5,10                       # Load immediate 10 (newline character)
	beq	a4,a5,.L8                   # If buffer[i] == '\n', jump to .L8
	li	a5,1                        # Load immediate 1
	sw	a5,-52(s0)                  # Set has_content = 1
.L8:                                # Loop increment
	ld	a5,-48(s0)                  # Load loop counter i
	addi	a5,a5,1                 # Increment i
	sd	a5,-48(s0)                  # Store updated i
.L5:                                # Loop condition check
	ld	a4,-48(s0)                  # Load loop counter i
	ld	a5,-32(s0)                  # Load file size
	blt	a4,a5,.L9                   # If i < filesize, continue loop
	lw	a5,-52(s0)                  # Load has_content flag
	sext.w	a5,a5                   # Sign extend to word
	beq	a5,zero,.L10                # If has_content == 0, jump to .L10
	lw	a5,-56(s0)                  # Load elf_count
	addiw	a5,a5,1                 # Increment elf_count (final group)
	sw	a5,-56(s0)                  # Store updated elf_count
.L10:                               # Print result
	lw	a5,-56(s0)                  # Load elf_count
	mv	a1,a5                       # Move elf_count to a1 (printf argument)
	lla	a0,.LC3                     # Load address of "Elf count: %d\n"
	call	printf@plt              # Call printf("Elf count: %d\n", elf_count)
	ld	a0,-24(s0)                  # Load buffer pointer
	call	free@plt                # Call free(buffer)
	li	a5,0                        # Load immediate 0 (success exit code)
.L3:                                # Function exit
	mv	a0,a5                       # Move exit code to a0 (return value)
	ld	ra,56(sp)                   # Restore return address
	ld	s0,48(sp)                   # Restore frame pointer
	addi	sp,sp,64                # Deallocate stack frame
	jr	ra                          # Return to caller
	.size	main, .-main            # Set function size
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"  # Compiler identification
	.section	.note.GNU-stack,"",@progbits  # GNU stack section (non-executable stack)
