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
        .type ReluAssem STT_FUNC
        .global ReluAssem                   // 地址到执行路径, ReluAssem代表一个地址，等于main函数
        .hidden ReluAssem
ReluAssem:

movi v15.4s,#0
cmp x2, #0 
beq End 

Loop:
ld1 {v0.4s},[x1],#16
fmax v0.4s,v0.4s,v15.4s 
st1 {v0.4s},[x0],#16
subs x2, x2, #1 
bne Loop

End:
ret