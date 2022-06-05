.data
    even: .asciiz "EVEN\n"
    odd: .asciiz "ODD\n"
    prompt_1: .asciiz "Enter your number for a0: "
    prompt_2: .asciiz "Enter your number for a1: "

.text
    .globl main

main: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)

    # Get input for a0 and a1:
    li $v0, 4
    la $a0, prompt_1
    syscall

    addi $v0, $zero, 5
    syscall
    move $s0, $v0

    li $v0, 4
    la $a0, prompt_2
    syscall

    addi $v0, $zero, 5
    syscall
    move $s1, $v0

    jal func

    # exit program
    lw $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra


func:
    bne $s1, $zero, print

    j exit

    # base on the even or odd, do some arithmetic to find out the memory adress of the item to print:


print:
    # Load the two options into two registats: 
    la $s2, even
    la $s3, odd
    sub $s4, $s3, $s2

    # Determine the odd or even of the a0 number. 
    andi $t0, $s0, 1

    mult $t0, $s4
    mflo $s5

    add $s5, $s5, $s2

    li $v0, 4
    move$a0, $s5
    syscall



    j exit



exit:
    li $v0, 10
    syscall
