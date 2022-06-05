.data
        Message: .asciiz "==> lucky "
        newline: .asciiz "\n"

.text
  .globl main
  
main:   
        sub $sp, $sp, 4
        sw $s0, 0($sp)
        li $s0, -15       # Load Immediate (li)  lucky = 13
        li $s1, -13               
        
        ble $s0, $s1, L1         # branch if (lucky > -13) 
        sub $s0, $s0, 6          # lucky -= 6  
L1:     
        li  $v0, 4               # Load Immediate (li)  syscall = 4
        la  $a0, Message
        syscall                  # syscall
        li $v0, 1                # Load Immediate (li)  syscall = 1
        move $a0, $s0
        syscall                  # syscall
        li $v0, 4                # Load Immediate (li)  syscall = 4
        la $a0, newline
        syscall                  # syscall
        lw $s0, 0($sp)
        add $sp, $sp, 4     
        jr $ra