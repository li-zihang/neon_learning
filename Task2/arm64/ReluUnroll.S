/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*
*   input: 
*       x0  *dst        输出目标地址
*       x1  *src        输入数组地址
*       x2  size        输入image的size
*
*
*/
        .section .text,"ax"                 // 汇编指示Assembler Directive，伪操作Pseudo-operation; data段保存数据，全局变量； text段保存代码，只读可执行；
        .align 5                                
        .type ReluUnroll STT_FUNC
        .global ReluUnroll                   // 地址到执行路径, ReluAssem代表一个地址，等于main函数
        .hidden ReluUnroll
ReluUnroll:
movi d15,#0                                     // mov immediate

cmp w2, #3                                  // 比较两个操作数,size == 3 ，结果存在CPSR
ble L1                                      // size <= 3, 少于3个数据时，进L1，否则进L4Loop

L4Loop:

ld2 {v0.4s,v1.4s},[x1],#32
ld2 {v2.4s,v3.4s},[x1],#32
fmax v0.4s, v0.4s, v15.4s
fmax v1.4s, v1.4s, v15.4s
fmax v2.4s, v2.4s, v15.4s
fmax v3.4s, v3.4s, v15.4s

st2 {v0.4s,v1.4s},[x0],#32
st2 {v2.4s,v3.4s},[x0],#32

sub x2, x2, #4                              // x2 = x2 -4
cmp x2, #4                                  // x2 ? 4
bge L4Loop                                  // x2>=4时，继续L4Loop

L1:
cmp x2,#0                                   // x2 ? 0
beq End                                     // x2 == 0 --> End

L1Loop:
ld1 {v0.4s},[x1],#16
fmax v0.4s,v0.4s,v15.4s
st1 {v0.4s},[x0],#16
subs x2,x2, #1                              // x2 = x2 -1
bne L1Loop                                  // x2 != 0, 继续L1Loop

End:
ret