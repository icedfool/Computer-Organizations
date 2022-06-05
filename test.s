.data
	tips:	.asciiz "please input your name:"
	name:	.space 32
	out:	.asciiz "\nyour name is:"

.text
    .globl main
	
main:
    #打印字符串
    li	$v0, 4
    la	$a0, tips
    syscall
    
    # 通过键盘输入string类型字符串
    li	$v0, 8
    la	$a0, name
    li	$a1, 4
    syscall
    
    #打印字符串
    li	$v0, 4
    la	$a0, out
    syscall
    
    #打印字符串
    li	$v0, 4
    la	$a0, name
    syscall
    
    jr $ra