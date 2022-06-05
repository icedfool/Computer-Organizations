# reverse.s

.data
  string:        .asciiz "this is fine."
  stringlen:     .word   13
  newline:       .asciiz "\n"

.text
  .globl main

main:
  sub $sp, $sp, 4   # allocate stack space to store $ra
  sw  $ra, 0($sp)   # store $ra on the stack

  # reverse the string in memory

  # obtain the hard-coded length of the string
  la  $t0, stringlen
  lw  $t0, 0($t0)      # $t0 = 13

  # set memory pointers $t1 and $t2 to the start and end bytes of string
  la  $t1, string   # $t1 holds the start address
  add $t2, $t1, $t0
  sub $t2, $t2, 1   # make sure $t2 points to the last byte of string

  # while ( $t2 >= $t1 ) { ... }
  #
loop:
  # use the set if less than (slt) instruction to control the loop
  slt $t3, $t2, $t1 # if $t2 < $t1 then set $t3 = 1; else set $t3 = 0

  # branch if not equal (bne)
  bne $t3, $0, exit # if $t3 != $0 then goto exit (note $0 always contains 0)

  # TO DO: print the string for each iteration of the loop

  # swap bytes pointed to by $t1 and $t2
  lbu $t4, 0($t1)   # load byte unsigned (lbu)
  lbu $t5, 0($t2)
  sb  $t4, 0($t2)   # store byte (sb)
  sb  $t5, 0($t1)

  # update pointers $t1 and $t2
  add $t1, $t1, 1
  add $t2, $t2, -1

  # unconditional jump (j)
  j loop

exit:
  # display final reversed string
  la  $a0, string
  li  $v0, 4
  syscall
  la  $a0, newline
  syscall


  # we're done, so restore $ra, free the stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr $ra