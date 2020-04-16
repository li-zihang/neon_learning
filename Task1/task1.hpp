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

#define row 480
#define colomn 640
#define repeat_count 1000

using std::endl;
using std::cout;

// 函数声明
int random_num(int16_t image[row][colomn]);
void add_neig(int16_t image_2[row][colomn], int16_t image[row][colomn], int h, int w);

#endif
