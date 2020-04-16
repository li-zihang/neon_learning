/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/
#include "task1.hpp"

int main(){
    int16_t image[row][colomn];
    int16_t image_2[row][colomn];
    
    // ------------ time calculation preparation
    struct timeval t0, t1;
    float total_time = 0.f;
    float min_time = __DBL_MAX__;
    float max_time = -__DBL_MAX__;    
    // ------------ time calculation preparation
    random_num(image);                                  // 生成随机数

    // ------------- calculation start
    gettimeofday(&t0, NULL);                            // 计时开始
    for(int t = 0; t < repeat_count; t++)
    {
	    add_neig(image_2, image, row, colomn);
    }
    gettimeofday(&t1, NULL);                            // 计时结束
    // ------------- calculation end

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
* 函数: 生成随机数
* 参数: 输出数组
* 说明: 随机数范围0~10000
*/
int random_num(int16_t image[row][colomn]){
    srand((int)time(0));
    for(int i=0;i<row;i++){
        for(int j=0; j<colomn; j++){
                image[i][j] = rand()% 10000;         // 0~10000
        }
    }
    return 0;
}

/*
* 函数: 计算函数
* 参数: 输出数组image2，输入数组image，高h，宽w
* 返回: 无
* 说明: 使用数组计算
*/
void add_neig(int16_t image_2[row][colomn], int16_t image[row][colomn], int h, int w){
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

