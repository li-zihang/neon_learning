/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/
#ifndef __TASK1_HPP__
#define __TASK1_HPP__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <fstream>
#include <unistd.h>
#ifdef __ARM_NEON
#include "arm_neon.h"
#endif
#define row 480
#define colomn 640
#define repeat_count 1000

using namespace std;

// function declaration
int random_num(int16_t image[row][colomn]);
void add_neig(int16_t image_2[row][colomn], int16_t image[row][colomn], int h, int w);
void SaveImage(int16_t dst[row][colomn],string name);
// use Neon intrinstic  
#ifdef __ARM_NEON
void add_intrinsics_d(int16_t * dst, int16_t * src, int h, int w);
void add_intrinsics_q(int16_t * dst, int16_t * src, int h, int w);
void add_intrinsics_rearrange_d(int16_t * dst, int16_t * src, int h, int w);
void add_intrinsics_rearrange_q(int16_t * dst, int16_t * src, int h, int w);
#endif

#endif
