/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/
#ifndef __TASK2_HPP__
#define __TASK2_HPP__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <fstream>
#include <unistd.h>

#ifdef __ARM_NEON
#include "arm_neon.h"
void ReluNeon(float * dst, float * src, int h, int w);
extern "C" void ReluAssem(float * dst, float * src, int size);
extern "C" void ReluUnroll(float * dst, float * src, int size);
extern "C" void ReluReorder(float * dst, float * src, int size);
#endif

#define row 480
#define colomn 640
#define repeat_count 1000

using namespace std;

void random_num(float image[row][colomn]);
void ReluFoward(float dst[row][colomn], float src[row][colomn]);
void SaveImage(float dst[row][colomn],string name);

#endif