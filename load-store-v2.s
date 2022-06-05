# load-store-v2.s

# the data segment contains program data, e.g., static arrays, hard-coded strings, etc.
#   (note that a word is 4 bytes)
.data
  array:       .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
  welcome:     .asciiz "Watch this\n"
  newline:     .asciiz "\n"

# the text segment contains our program code
.text
  .globl main     # main is a global label

main:
  sub $sp, $sp, 4     # allocate stack space to store $ra (return address pointer)
  sw $ra, 0($sp)      # store $ra onto the stack ($sp is the stack pointer)

  la $a0, welcome     # load the address of welcome into register $a0
  li $v0, 4           # set up to print the string pointed to by $a0
  syscall             # print_string

  # read a specific value from our array (using pointer arithmetic),
  #  modify its value, then confirm re-reading from the same location in array

  la $s0, array       # load the address of array into register $s0

  lw $t0, 32($s0)     # load (address in $s0) + 32 bytes
                      # note that this is equivalent to array[8] or *(array+8) in C
                      #  (with array as an int* pointer and sizeof(int) == 4 bytes)

  # let's call our own print function
  move $a0, $t0
  jal print           # jal copies the program counter into $ra

  # modify the value in the array at index 8
  li $t0, 8888
  sw $t0, 32($s0)     # store $t0 into array[8] or *(array+8)

  # confirm the change was made
  lw $a0, 32($s0)
  jal print

  # we're done, so restore $ra, free the stack space, and return
  lw $ra, 0($sp)
  add $sp, $sp, 4
  jr $ra


# our print function will print the integer in register $a0
#  (and change the contents of $a0 in the process of printing)
#
# the print function is a "leaf" function in that it never calls
#  a function, i.e., never runs a jal instruction (and therefore,
#   never overwrite the return address $ra register)
#
# TO DO: add more output to this function to display as:
#          "The value is: $a0\n"
#
# TO DO: store the value of $a0 on the stack so that we can
#         restore $a0 to its original value on return
print:
  li $v0, 1
  syscall             # print an integer (contents of $a0)

  la $a0, newline
  li $v0, 4           # print string pointed to by $a0
  syscall

  jr $ra              # return to the calling function



# the data segment at the top of this MIPS code is similar to this C code:
#
# int array[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
#
# char * welcome = "Watch this\n";
#
# printf( "Watch this\n" );
#

#
#                             mmap() XXXXXXXX <== how do I get back to calloc() when I'm done?
#                             calloc() XXXXXXXX <== how do I get back to main() when I'm done?
#                             main() XXXXXXXX
# stack of C function calls: ___________
#