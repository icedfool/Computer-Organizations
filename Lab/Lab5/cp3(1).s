    # strncpy.s  (check out the man page for strncpy)

    # ADDITIONAL TO DO: test the strlen() function

    # TO DO: write a strlen() function and use that instead of
    #         prompting the user, i.e., get the length of src
    #          and copy all of the bytes over to dest
    #
    # TO DO: write a strncmp() function (...Exam 1)
    #

    .data
    prompt: .asciiz "Enter n: "
    dest:   .asciiz "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
    src:    .asciiz "this is fine."


    .text
    .globl main

    main:
    sub $sp, $sp, 4   # allocate stack space to store $ra   
    sw  $ra, 0($sp)   # store $ra on the stack

    # display prompt (print_string)
    la  $a0, prompt
    # li  $v0, 4 
    ori $v0, $0, 4
    syscall


    # read int from keyboard
    # li  $v0, 5
    ori $2, $0, 5
    syscall      # read_int ==> result is in $v0

    # set up parameters dest, src, and n for strncpy() function call:
    la  $a0, dest
    la  $a1, src
    # move $a2, $v0   # $v0 is the result from read_int above...
    addu $a2, $0, $v0
    jal strncpy

    # display dest string via print_string syscall
    la  $a0, dest
    # li  $v0, 4
    ori $v0, $0, 4
    syscall

    # we're done, so restore $ra, free the stack space, and return
    lw  $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra

    #############################################################
    # strncpy( char * dest, const char * src, size_t n );
    #                  $a0               $a1        $a2
    strncpy:
    # for ( $t0 = 0 ; $t0 < $a2 ; $t0++ ) { ... }
    #
    # li  $t0, 0       # $t0 = 0
    ori $t0, $0, 0                                                          # 1. 0x34080000: opcode: 001101, rs: 00000, rt: 01000, immediate: 0000000000000000

    loop:
    # use the set if less than (slt) instruction to control the loop
    slt $t1, $t0, $a2  # if $t0 < $a2 then set $t1 = 1; else $t1 = 0        # 2. 0x0106482a: opcode: 101010, rs: 01000, rt: 00110, rd:01001 shift: 00000

    # branch if not equal (bne)
    bne $t1, 1, exit  # if $t1 != 1 then goto exit                          # 3. 0x34010001: opcode: 001101, rs: 00000, rt: 00001, immediate: 0000000000000001

    # copy byte from src to dest
    lbu $t2, 0($a1)  # load byte unsigned (lbu)                             # 4. 0x90aa0000: opcode: 100100, fmt: 00101, rt: 01010, offset: 0000000000000000
    sb  $t2, 0($a0)  # store byte (sb)                                      # 5. 0xa08a0000: opcode: 101000, fmt: 00100, rt: 01010, offset: 0000000000000000

    # update pointers $a0 and $a1
    add $a0, $a0, 1                                                         # 6. 0x20840001: opcode: 001000, rs: 00100, rt: 00100, immediate: 0000000000000001
    add $a1, $a1, 1                                                         # 7. 0x20a50001: opcode: 001000, rs: 00101, rt: 00101, immediate: 0000000000000001

    # update loop variable $t0
    add $t0, $t0, 1                                                         # 8. 0x21080001: opcode: 001000, rs: 01000, rt: 01000, immediate: 0000000000000001

    # unconditional jump (j)
    j loop                                                                  # 9：0x0810001d: opcode: 000010, target: 00000100000000000000011101

    exit:
    jr $ra                                                                  # 10. 0x03e00008 rs: 11111, JR: 001000
    #
    #############################################################

    #############################################################
    # strlen( const char * s );
    #                     $a0   ==>  length returned in $v0
    strlen:
    # move $t0, $a0                                                                   # Needs Change
    addu $t0, $0, $a0                                                                   # New Change
    # li  $t1, 0       # $t1 = 0                                                      # Needs Change
    ori $t1, $0, 0                                                                     # New Change

    L1:
    lbu $t2, 0($t0)  # load byte unsigned (lbu)
    beq $t2, $zero, strlenexit

    # update pointer $t0
    add $t0, $t0, 1

    # update byte count $t1
    add $t1, $t1, 1

    # unconditional jump (j)
    j L1

    strlenexit:
    # move $v0, $t1                                                                   # Needs Change
    addu $v0, $0, $t1                                                                   # New Change  
    jr $ra
    #
    #############################################################
