       .data

msg:   .asciiz "==> lucky "
luck:     .word   -100
min1:      .word   6
newline:     .asciiz "\n"
       .text
       .globl main

main:   
        la $a0, msg
        li $v0 ,4
        syscall
        lw $s0, luck              
        lw $s1, min1                
        li $s3,-13              
                    

        #add $t0,$s1,$s2         # temp t0 = g + h
        #sub $t1,$t0,$s3         # temp t1 = t0 - i
        slt $t0, $s0, $s3
        beq $t0, 1, number    #$t0 < $t1
    sth:
        #sub $a0,$s0,$s1         # f = t1 - j
        move $a0, $s0
        li $v0,1                # syscall 1 (print_int)
        syscall                 # prints $a0
        la $a0, newline
        li $v0, 4
        syscall
        #li $v0 10
	jr $ra                  # return to the calling function

number:
    sub $s0,$s0,$s1 
    j sth
    #syscall
    #main:   sub $sp, $sp, 4     # allocate stack space to store $ra (return address pointer)
        #sw $ra, 0($sp)      # store $ra onto the stack ($sp is the stack pointer)
        
        #la $a0, msg    # load the address of welcome into register $a0
        #li $v0, 4           # set up to print the string pointed to by $a0
        #syscall             # print_string
        
        #la $t0, luck
        #la $t1, min
       # sub $s0, $t0 ,$t1
        #la $s0, luck
       # sub $s0, $t0 ,$t1
       # move $s0, $v0
       # li $v0, 1
       # move $a0, $s0
       # syscall
       # la $a0, newline
       # li $v0, 4           # print string pointed to by $a0
        #syscall
        #jr $ra

        #sub $s0, $t0 ,$t1