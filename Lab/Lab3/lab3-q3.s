.data 
    output: .asciiz "What is the capital of Connecticut? "
    output2: .asciiz "You entered \""
    output3: .asciiz "\" ("
    output4: .asciiz " bytes)\n"
    answer: .asciiz "Hartford"
    no: .asciiz "Sorry, incorrect!\n"
    yes: .asciiz "Wow, you got it.\n"
    next: .asciiz "\n"
.text 
    .globl main
main:
    la $s3, answer

    la $a0, output          #print prompt
    li $v0, 4
    syscall

    li $v0, 8               #take user input
    syscall 

    la $s0, ($a0)           #load address of input into vars
    la $s1, ($a0)

    la $a0, output2         #print You entered
    li $v0, 4
    syscall

    li $t3,0                #find the length of input
    jal lenth
    sub $t3, $t3, 1         #remove trailing \n         

    add $s1, $s1, $t3       
    sb $zero, 0($s1)
    sub $s1, $s1, $t3

    move $a0, $s1
    syscall

    la $a0, output3         #print the format for byte
    li $v0, 4               #print (
    syscall

    
    move $a0 $t3            #print the length of the input
    li $v0, 1
    syscall

    

    la $a0, output4         #print bytes)
    li $v0, 4
    syscall

    jal LOOP                #compare strings


    li $v0,10               #exit program
    syscall

lenth:
    lbu $t4, 0($s0)         #calculate string length
    beqz $t4, END
    add $s0, $s0, 1
    add $t3, $t3,1
    j lenth


LOOP:
    lbu $t0, 0($s1)
    lbu $t1, 0($s3)
    add $s1, $s1, 1        
    add $s3, $s3, 1
    beqz $t0, L_END         #if one is shorter than the other
    beqz $t1, L_END
    bgt $t0, $t1, dif       #length of 
    blt $t0, $t1, dif
    beq $t0, $t1, LOOP
Equal:
    la $a0, yes             #if user input matches answer
    li $v0,4
    syscall
    j END
dif:
    la $a0, no              #if user input doesn't matches
    li $v0, 4
    syscall
    j END
L_END:
    beq $t0, $t1,Equal      #check it is equal or diff
    beqz $t0, dif
    beqz $t1, dif
END:
    jr $ra