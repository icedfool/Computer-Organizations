.data
    in_space:       .space 129
    begin:          .asciiz "Enter data: "
    next1:          .asciiz "Read "
    next2:          .asciiz " bytes\n"
    maohao:         .asciiz": "
    nextline1:      .asciiz" ("
    nextline2:      .asciiz"#"
    nextline3:      .asciiz")\n"

.text
  .globl main

main:
    la $a0, begin   #print the first line
    li $v0, 4
    syscall
    la $a0, in_space    #read in the string
    la $a1, 129
    li $v0, 8
    syscall
    li $t0, 0   #count how many byte
    li $t2, 0
    j count_byte
    print_byte: #print how many byte inside
        la $a0, next1
        li $v0, 4
        syscall
        move $a0, $t2
        li $v0, 1
        syscall
        la $a0, next2
        li $v0,4
        syscall
    
    li $t0, 32  #find the specified char
    j count
    j exit

count_byte: #read through the string to know how many byte
    lb $t1, in_space($t2)
    beqz $t1, print_byte
    add $t2, $t2, 1
    j count_byte

count:  #move to different char and find
    li $t2, 0
    li $t3, 0
    beq $t0, 127, exit
    j read
    next_char:
        add $t0, $t0, 1
    j count

read:   #count number of specified char
    lb $t1, in_space($t2)
    beq $t1, 10, lianjie
    beqz $t1, lianjie
    beq $t1, $t0, one_more
    conti:
        add $t2, $t2, 1
    j read

one_more:   #find one more char than count +1
    move $t5, $t2
    add $t3,$t3,1
    j conti

lianjie:    #connection for two function
    jal isprint
    beq $t7, 0, print
    j next_char

isprint:    #make sure this symbol can be print
    li $t4, 32
    li $t7, 0
    beqz $t3, add1
    bgt $t1,$t4, add1
    then:
        jr $ra

add1:
    add $t7, $t7, 1
    j then

print:  #print out the data of this char
    la $a1, in_space
    addu $a1,$a1,$t5
    lbu $a0, ($a1)
    li $v0, 11
    syscall
    la $a0,maohao
    li $v0,4
    syscall
    li $t6,0
    symbol: #print the symbol for times
        beq $t6, $t3, last_part
        la $a0,nextline2
        syscall
        add $t6,$t6,1
        j symbol

last_part:  #print out times of this char
    la $a0,nextline1
    li $v0,4
    syscall
    move $a0, $t3
    li $v0,1
    syscall
    la $a0,nextline3
    li $v0,4
    syscall
    j next_char

exit:   #ending
    li $v0,10
    syscall