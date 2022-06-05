.data
    data: .asciiz "byte #"
    colon: .asciiz ": "
    vertical: .asciiz " | "
    num: .word 0x4a889cf1
    newline: .asciiz "\n"

.text
    .globl main

main:
    lw  $t0 , num($zero)    #first number
    srl $t0 , $t0 , 24
    li $v0 , 4
    la $a0 , data
    syscall
    addi $t1 , $zero , 1
    li $v0 , 1
    move $a0 , $t1
    syscall
    li $v0 , 4
    la $a0 , colon
    syscall
    move $a0 , $t0
    li  $v0, 1
    syscall
    li $v0 , 4
    la $a0 , vertical
    syscall

    lw  $t0 , num($zero)   #second number
    and $t0 , $t0 , 0x00FF0000
    srl $t0 , $t0 , 16
    li $v0 , 4
    la $a0 , data
    syscall
    addi $t1 , $zero , 2
    li $v0 , 1
    move $a0 , $t1
    syscall
    li $v0 , 4
    la $a0 , colon
    syscall
    move $a0 , $t0
    li  $v0, 1
    syscall
    li $v0 , 4
    la $a0 , vertical
    syscall

    lw  $t0 , num($zero)   #third number
    and $t0 , $t0 , 0x0000FF00
    srl $t0 , $t0 , 8
    li $v0 , 4
    la $a0 , data
    syscall
    addi $t1 , $zero , 3
    li $v0 , 1
    move $a0 , $t1
    syscall
    li $v0 , 4
    la $a0 , colon
    syscall
    move $a0 , $t0
    li  $v0, 1
    syscall
    li $v0 , 4
    la $a0 , vertical
    syscall

    lw  $t0 , num($zero)   #fourth number
    and $t0 , $t0 , 0x000000FF
    srl $t0 , $t0 , 0
    li $v0 , 4
    la $a0 , data
    syscall
    addi $t1 , $zero , 4
    li $v0 , 1
    move $a0 , $t1
    syscall
    li $v0 , 4
    la $a0 , colon
    syscall
    move $a0 , $t0
    li  $v0, 1
    syscall
    li $v0 , 4
    la $a0 , vertical
    syscall

    li $v0, 10
    syscall
