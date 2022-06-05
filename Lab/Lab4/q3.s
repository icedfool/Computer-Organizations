.data
    list: .word 12,100,101,5,123456789,18
    hexlist: .word 0x4a889cf1, 0xff00fefd
    hexbytes: .word 0xfc, 0x01, 0xaa, 0xbb
.text
    .globl main

main:
    add $sp, $sp, -4
    sw  $ra, 0($sp)
    la  $a0, list
    jal loop
    lw $ra, 0($sp)      # reload $ra so we can return to caller
    addiu $sp, $sp, 4   # restore $sp, freeing the allocated space
    jr $ra

loop:
    lw  $a0, 0($t1)
    li  $v0, 1
    syscall
    j exit
    
exit:
    li $v0, 10
    syscall