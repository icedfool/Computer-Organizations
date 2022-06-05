.data
    prompt: .asciiz "Enter your number: "
    result: .asciiz "A result of 0 is even, 1 is odd: result = "
    even: .asciiz "EVEN\n"
    odd: .asciiz "ODD\n"

.text
    .globl main

main:
    # Get input value
    li $v0, 4    # Write Prompt
    la $a0, prompt
    syscall
    li $v0, 5    # Retrieve input
    syscall
    move $s0, $v0
    
    andi $s0, 1	# 
    li $v0, 4
    move $a0, $s0
    syscall
    
    
    # Print output        
    li $v0, 4    # Print result string
    la $a0, result
    syscall
    li $v0, 1  # Print result
    move $a0, $s1
    syscall
    
    #Exit program
    li $v0, 10
    syscall
