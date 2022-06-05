.data
    Question: .asciiz "What is the capital of Connecticut?"
    newline: .asciiz "\n"
    Enter: .asciiz "You entered "
    Correct: .asciiz "Wow, you got it.\n"
    Wrong: .asciiz "Sorry, incorrect!\n"
    name: .space 33
    Answer: .asciiz "Hartford"
    Content1: .asciiz "( "
    Content2: .asciiz " bytes)"

.text
    .globl main

main:
    
    li	$v0, 4             # print the question line
    la	$a0, Question
    syscall

    li	$v0, 8
    la	$a0, name
    li	$a1, 32
    syscall

    li	$v0, 4
    la	$a0, Enter
    syscall

    li	$v0, 4
    la	$a0, name
    syscall

    la	$a0, name
    jal strlen
    move $a0, $t0
    li $v0,1
    syscall
    li $v0, 10
    syscall

strlen:
    li $t0, -1 # initialize the count to -1
loop:
    lb $t1, 0($a0) # load the next character into t1
    beq $t1, $zero, exit # check for the null character
    addi $a0, $a0, 1 # increment the string pointer
    addi $t0, $t0, 1 # increment the count
    j loop # return to the top of the loop
exit:
    jr $ra #remember to call $t0


strcmp:
    add $t0,$zero,$zero
    add $t1,$zero,$a0
    add $t2,$zero,$a1
loop2:
    lb $t3($t1)  #load a byte from each string
    lb $t4($t2)
    beqz $t3,checkt2 #str1 end
    beqz $t4,missmatch
    slt $t5,$t3,$t4  #compare two bytes
    bnez $t5,missmatch
    addi $t1,$t1,1  #t1 points to the next byte of str1
    addi $t2,$t2,1
    j loop2
missmatch: 
    addi $v0,$zero,1
    j endfunction
checkt2:
    bnez $t4,missmatch
    add $v0,$zero,$zero
endfunction:
    jr $ra