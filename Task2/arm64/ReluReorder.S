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
        .type ReluReorder STT_FUNC
        .global ReluReorder                   // 地址到执行路径, ReluAssem代表一个地址，等于main函数
        .hidden ReluReorder
ReluReorder:
movi d15,#0x0

L4:
cmp x2, #3
ble  L1

//vld1.32 {q0,q1}, [r1]!                      // 循环控制, src减1, 取q0, q1
ld2 {v0.4s,v1.4s},[x1],#32
//vmax.f32 q0,q0,q15                          // 判断大小, q0/q1/q2/q3与0相比，大的放到q0
fmax v0.4s, v0.4s, v15.4s
//vld1.32 {q2,q3}, [r1]!                      // 循环控制, src减1, 取q2, q3
ld2 {v2.4s,v3.4s},[x1],#32
//vmax.f32 q1,q1,q15
fmax v1.4s, v1.4s, v15.4s
// q2, q3 没比较，q0,q1没存储

sub x2, x2, #4                              // x2 = x2 -4
cmp x2, #3                                  // x2 ? 3
ble L4End                                  // x2<=3时，跳转到L4End


L4Loop:

st2 {v0.4s,v1.4s},[x0],#32
fmax v2.4s, v2.4s, v15.4s 

ld2 {v0.4s, v1.4s},[x1],#32
fmax v3.4s, v3.4s, v15.4s 

st2 {v2.4s,v3.4s},[x0],#32
fmax v0.4s, v0.4s, v15.4s 

ld2 {v2.4s, v3.4s},[x1],#32
sub x2,x2,#4

fmax v1.4s, v1.4s, v15.4s
cmp x2, #4                                      // x2 ? 4

bge L4Loop                                      // x2>=4时，继续L4Loop

L4End:
ld2 {v0.4s,v1.4s},[x1],#32
fmax v2.4s,v2.4s,v15.4s
fmax v3.4s,v3.4s,v15.4s
ld2 {v2.4s,v3.4s},[x0],#32

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