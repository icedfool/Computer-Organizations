# strncpy.s  (check out the man page for strncpy)

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
  li  $v0, 4
  syscall

  # read int from keyboard
  li  $v0, 5
  syscall      # read_int ==> result is in $v0

  # set up parameters dest, src, and n for strncpy() function call:
  la  $a0, dest
  la  $a1, src
  move $a2, $v0   # $v0 is the result from read_int above...
  jal strncpy

  # display dest string via print_string syscall
  la  $a0, dest
  li  $v0, 4
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
  li  $t0, 0       # $t0 = 0

loop:
  # use the set if less than (slt) instruction to control the loop
  slt $t1, $t0, $a2  # if $t0 < $a2 then set $t1 = 1; else $t1 = 0

  # branch if not equal (bne)
  bne $t1, 1, exit  # if $t1 != 1 then goto exit

  # copy byte from src to dest
  lbu $t2, 0($a1)  # load byte unsigned (lbu)
  sb  $t2, 0($a0)  # store byte (sb)

  # update pointers $a0 and $a1
  add $a0, $a0, 1
  add $a1, $a1, 1

  # update loop variable $t0
  add $t0, $t0, 1

  # unconditional jump (j)
  j loop

exit:
  jr $ra
#
#############################################################