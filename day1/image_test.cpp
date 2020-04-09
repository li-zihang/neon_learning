/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <fstream>

#define row 480
#define colomn 640
#define repeat_count 1000

using namespace std;
int16_t image[row][colomn];                     // 存储随机数
int16_t image_2[row][colomn];

int random_num();
void add_neig(int h, int w);

int main(){
    int row_t = 480;
    int colomn_t = 640;
    ofstream later_array("./later.txt");                // 输出txt，用于对比数据

    // ------------ time calculation preparation
    struct timeval t0, t1;
    float total_time = 0.f;
    float min_time = __DBL_MAX__;
    float max_time = -__DBL_MAX__;    
    // ------------ time calculation preparation

    random_num();                                       // 生成随机数
    gettimeofday(&t0, NULL);                            // 计时开始

    // ------------- calculation start
    for(int t = 0; t < repeat_count; t++)
    {
	    add_neig(row_t,colomn_t);
    }
    // ------------- calculation end

    gettimeofday(&t1, NULL);                            // 计时结束 

    // 存储输出image_2到later.txt
    for(int i=0;i<row;i++){
        for(int j=0;j<colomn;j++){
            later_array << dec << image_2[i][j] << " ";
        }
        later_array << endl;
    }

    // ------------- time calculation
    float mytime = ( float )((t1.tv_sec * 1000000 + t1.tv_usec) - (t0.tv_sec * 1000000 + t0.tv_usec)) / 1000;
    total_time += mytime;
    min_time = std::min(min_time, mytime);
    max_time = std::max(max_time, mytime);
    cout << "--------------------------------------\n";
    cout << "Avg time per run is " << (total_time /repeat_count) << " ms\n" << endl;
    // ------------- time calculation
    return 0;
}

/*
1.  int num = rand() % n +a;
    n为最大值，从a开始
2.  rand() % (b-a+1)+ a 
    表示 a~b之间的一个整数
*/
int random_num(){
    ofstream previous_array("./previous.txt");       // 存储输入image到previous.txt
    srand((int)time(0));
    for(int i=0;i<row;i++){
        for(int j=0; j<colomn; j++){
                image[i][j] = rand()% 10000;         // 0~10000
                previous_array << dec << image[i][j] << " ";
        }
        previous_array << endl;
    }
    return 0;
}

void add_neig(int h, int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j == 0)
                image_2[i][j] = image[i][j] + image[i][j+1];
            else if(j == colomn-1)
                image_2[i][j] = image[i][j] + image[i][j-1];
            else 
                image_2[i][j] = image[i][j] + image[i][j+1] + image[i][j-1];
        }
	}
}

