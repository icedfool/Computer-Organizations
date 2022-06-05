.data
    myArray: .space 80
    newline: .asciiz "\n"
.text
    main:
        li $s0, 0  #save Fib(0)
        li $s1, 1  #save Fib(1)  
        la $s3, myArray

        addi $t0, $zero,0   #create a counter
        sw $s0, myArray($t0)    #save Fib(0) in the first element of array
        move $a0, $s0
        li $v0, 1
        syscall
        la $a0, newline
        li $v0, 4
        syscall
        addi $t0, $t0, 4    #move to next integer in array
        sw $s1, myArray($t0)    #save Fib(1) in the first element of array
        move $a0, $s1
        li $v0, 1
        syscall
        la $a0, newline
        li $v0, 4
        syscall
        addi $t0, $t0, 4    #move to next integer in array
        addi $t1, $zero, 0      #counter for while loop

        while:
            bgt $t1, 17, exit   #exit after 18 iterations
            add $s2, $s0, $s1  #find the next Fib given the previous two

            sw $s2, myArray($t0)
            move $a0, $s2
            li $v0, 1
            syscall
            la $a0, newline
            li $v0, 4
            syscall    
            addi $t0, $t0, 4    #increament array
            
            addi $t1, $t1, 1
            addi $s0, $s1, 0
            add $s1, $s2, 0
            j while
            
        exit:
            jr $ra



