/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/
#include "task2.hpp"

int main(int argc, char* argv[])
{
    float src[row][colomn];
    float dst[row][colomn];
    bool save = false;

    // ------------ time calculation preparation
    struct timeval t0, t1;
    float total_time = 0.f;
    float min_time = __DBL_MAX__;
    float max_time = -__DBL_MAX__;    
    // ------------ time calculation preparation
    random_num(src); 

    // ------------ input args control
    int res;
    while((res = getopt(argc, argv, "s")) != -1)
    {
        switch(res)
        {
            case 's':
                save = true;
                break;
            default:
                break;
        }
    }
    // ------------ input args control

    int size = row*colomn/4;                                 // 生成随机数

    // ------------- calculation start
    gettimeofday(&t0, NULL);                            // 计时开始
    for(int t = 0; t < repeat_count; t++)
    {
	    // ReluFoward(dst,src);
        #ifdef __ARM_NEON
        // ReluNeon(&dst[0][0],&src[0][0],row,colomn);
        ReluAssem(&dst[0][0],&src[0][0],size);
        // ReluUnroll(&dst[0][0],&src[0][0],size);
        // ReluReorder(&dst[0][0],&src[0][0],size);
        #endif

    }
    gettimeofday(&t1, NULL);                            // 计时结束
    // ------------- calculation end

    // save array to txt
    if(save == true)
    {
        SaveImage(src,"./src.txt");
        SaveImage(dst,"./dst.txt");
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
* 函数: 生成随机数
* 参数: 输出数组
* 说明: 随机数范围0~10000
*/
void random_num(float image[row][colomn]){
    srand((float)time(0));
    for(int i=0;i<row;i++){
        for(int j=0; j<colomn; j++){
            image[i][j] = (float)((rand()% 10000 -5000)/1000.0) ;         // -5~5
        }
    }
}

/*
* 函数: ReLU计算
* 参数: 输入数组，输出数组
* 说明: 
*/
void ReluFoward(float dst[row][colomn], float src[row][colomn])
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<colomn;j++)
        {
            dst[i][j] = src[i][j] > 0 ? src[i][j] : 0;
        }
    }
}

#ifdef __ARM_NEON
#include "arm_neon.h"
/*
* 函数: ReLU计算--neon版本
* 参数: 输入数组，输出数组
* 说明: 
*/
void ReluNeon(float * dst, float * src, int h, int w)
{
    int size = h*w/4;
    float32x4_t limit = vdupq_n_f32(0);
    for(int i=0;i<size;++i)
    {
        float32x4_t value = vld1q_f32(src);
        value = vmaxq_f32(value,limit);
        vst1q_f32(dst,value);
        dst += 4;
        src += 4;
    }
}
#endif

/*
* 函数: SaveImage
* 参数: 被保存的数组dst
* 说明: 存储数组为txt
*/
void SaveImage(float dst[row][colomn],string name)
{
    ofstream dst_array(name);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<colomn;j++)
        {
            dst_array << dec << dst[i][j] << " ";
        }
        dst_array << endl;
    }
}
