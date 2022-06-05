.data
    array: .word 1,2,3,4,5,6,7,8,9,10
    newline: .asciiz "\n"
.text
    .globl main

main:
    add $sp, $sp, -4
    sw  $ra, 0($sp)
    addi $t0, $t0, 1    #assign t0 to 1(serve as index)
    la  $t1, array      #load address of array in $t1
    jal loop
    lw $ra, 0($sp)      # reload $ra so we can return to caller
    addiu $sp, $sp, 4   # restore $sp, freeing the allocated space
    jr $ra

loop:
    bge $t0, 10 , exit
    sll $t2, $t0, 2     # multiply by $t0 by 4 as offset to $t2
    li  $v0 , 1         # print num
    lw  $a0, 0($t1)
    syscall
    li  $v0 , 4
    la  $a0, newline
    syscall
    addi $t1, $t1, 4    # add $t1 to $t0($t1)
    addi $t0, $t0, 1
    j loop

exit:
    jr $ra