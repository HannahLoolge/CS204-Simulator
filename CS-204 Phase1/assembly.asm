addi x10,x0,10
jal x1,fib
jal x0 ,exit
fib:
addi sp,sp,-4
sw x1,0(sp)
beq x10,x0,n_0
addi x3,x0,1
beq x10,x3,n_1
jal x0,fib_recur
n_0:
addi sp,sp,4
addi x11,x0,0
jalr x0,0(x1)
n_1:
addi sp,sp,4
addi x11,x0,1
jalr x0,0(x1)
fib_recur:
addi sp,sp,-4
addi x10,x10,-1
sw x10,0(sp)
jal x1,fib
lw x10,0(sp)
sw x11,0(sp)
addi x10,x10,-1
jal x1,fib
lw x5,0(sp)
addi sp,sp,4
add x11,x11,x5
lw x1,0(sp)
addi sp,sp,4
jalr x0,0(x1)
exit:
