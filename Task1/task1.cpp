/*
*   本工程用于学习Neon。
*   This file is used to test the Neon instinsic. 
*   Some comments will be in only Chinese.
*   by: Pierrick Lee 
*/
#include "task1.hpp"

int main(int argc, char* argv[]){
    int16_t src[row][colomn];
    int16_t dst[row][colomn];
    bool save = false;
    
    // ------------ time calculation preparation
    struct timeval t0, t1;
    float total_time = 0.f;
    float min_time = __DBL_MAX__;
    float max_time = -__DBL_MAX__;    
    // ------------ time calculation preparation
    random_num(src);                                  // 生成随机数

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

    // ------------- calculation start
    gettimeofday(&t0, NULL);                            // 计时开始
    for(int t = 0; t < repeat_count; t++)
    {
	    add_neig(dst, src, row, colomn);
        #ifdef __ARM_NEON
         add_intrinsics_d(&(dst[0][0]),&(src[0][0]),row,colomn);
         add_intrinsics_q(&(dst[0][0]),&(src[0][0]),row,colomn);
         add_intrinsics_rearrange_d(&(dst[0][0]),&(src[0][0]),row,colomn);
         add_intrinsics_rearrange_q(&(dst[0][0]),&(src[0][0]),row,colomn);
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
* 函数: 计算函数, 纯C
* 参数: 输出数组image2，输入数组image，高h，宽w
* 返回: 无
* 说明: 使用数组计算
*/
void add_neig(int16_t dst[row][colomn], int16_t src[row][colomn], int h, int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j == 0)
                dst[i][j] = src[i][j] + src[i][j+1];
            else if(j == colomn-1)
                dst[i][j] = src[i][j] + src[i][j-1];
            else 
                dst[i][j] = src[i][j] + src[i][j+1] + src[i][j-1];
        }
	}
}

/*
* 函数: SaveImage
* 参数: 被保存的数组dst
* 说明: 存储数组为txt
*/
void SaveImage(int16_t dst[row][colomn],string name)
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

/*
* 函数: veritify
* 参数: 被验证的array，正确结果pointer，数组尺寸h/w
* 说明: 做差检验
*/
int veritify(int16_t *array, int16_t *pointer, int h, int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if((*(array+i*w+j) - *(pointer+i*w+j)) != 0)
                return 1;
        }
	}
    return 0;
}

/*
* 函数: add_pointer
* 参数: 源数组指针src，输出数组指针dst，数组尺寸h/w
* 说明: 使用指针替代数组
*/
void add_pointer(int16_t *dst, int16_t *src, int h, int w){
    for(int i=0;i<h;i++){
        int16_t* pld = dst + i*w;
        int16_t* pls = src + i*w;
        for(int j=0;j<w;j++){
            if(j == 0){
                *pld++ = *pls + *(pls+1);
                pls++;
            }
            else if(j == w-1)
                *pld = *pls + *(pls-1);
            else{
                *pld++ = *pls + *(pls+1) + *(pls-1);
                pls++;
            }
        }
    }
}

// use Neon intrinstic  
#ifdef __ARM_NEON
/*
* 函数: add_intrinsics_d
* 参数: 源数组指针src，输出数组指针dst，数组尺寸h/w
* 说明: 使用Arm Neon Intrinsics指令，使用d_registers (64bits)
*/
void add_intrinsics_d(int16_t * dst, int16_t * src, int h, int w){
    int16x4_t a;
    int16x4_t b;
    int16x4_t c;
    int16x4_t v;
    for(int i=0;i<h;i++){
        // first loop
        *dst++ = *src + *(src+1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        // main loop
        for(int j=0;j<(w-8)/4;j++){
                a = vld1_s16(src-1);
                b = vld1_s16(src);
                c = vld1_s16(src+1);
                v = vadd_s16(a,b);
                v = vadd_s16(v,c);
                vst1_s16(dst,v);
		        src+=4;
                dst+=4;
		}
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src-1);
        src++;
    }
}

/*
* 函数: add_intrinsics_q
* 参数: 源数组指针src，输出数组指针dst，数组尺寸h/w
* 说明: 使用Arm Neon Intrinsics指令，使用q_registers (128bits)
*/
void add_intrinsics_q(int16_t * dst, int16_t * src, int h, int w){
    int16x8_t a;
    int16x8_t b;
    int16x8_t c;
    int16x8_t v;
    for(int i=0;i<h;i++){
        // first loop
        *dst++ = *src + *(src+1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        // main loop
        for(int j=0;j<(w-8)/8;j++){
                a = vld1q_s16(src-1);
                b = vld1q_s16(src);
                c = vld1q_s16(src+1);
                v = vaddq_s16(a,b);
                v = vaddq_s16(v,c);
                vst1q_s16(dst,v);
		        src+=8;
                dst+=8;
		}
        // last loop
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src+1) + *(src-1);
        src++;
        *dst++ = *src + *(src-1);
        src++;
    }
}

/*
* 函数: add_intrinsics_rearrange_d
* 参数: 源数组指针src，输出数组指针dst，数组尺寸h/w
* 说明: 使用Arm Neon Intrinsics指令，使用d_registers (64bits)
*       增加(1) 访存数据对齐
*           (2) 数据拼接，减少访存次数
*/
void add_intrinsics_rearrange_d(int16_t * dst, int16_t * src, int h, int w){
    int16x4_t v0;
    int16x4_t v1;
    int16x4_t v2;
    int16x4_t p0;
    int16x4_t p1;
    int16x4_t p2;
    int16x4_t res;
    // first loop
    for(int j=0;j<h;j++){
        v1 = vld1_s16(src);
        v2 = vld1_s16(src+4);               
        src +=8;
        v0 = vdup_n_s16(0);                 // pad 0
        p0 = vext_s16(v0,v1,3);             // x2 x1 x0 0
        p1 = v1;                            // x3 x2 x1 x0
        p2 = vext_s16(v1,v2,1);             // x4 x3 x2 x1
        res = vadd_s16(p0,p1);
        res = vadd_s16(res,p2);
        vst1_s16(dst,res);
        dst += 4;
        // main loop
        for(int i=0;i<(w/4-2);i++){
            v0 = v1;
            v1 = v2;
            v2 = vld1_s16(src);
            src+=4;
            p0 = vext_s16(v0,v1,3);             // x2 x1 x0 0
            p1 = v1;                            // x3 x2 x1 x0
            p2 = vext_s16(v1,v2,1);             // x4 x3 x2 x1
            res = vadd_s16(p0,p1);
            res = vadd_s16(res,p2);
            vst1_s16(dst,res);
            dst += 4;
        }
        // last loop
        v0 = v1;
        v1 = v2;
        v2 = vdup_n_s16(0);
        p0 = vext_s16(v0,v1,3);             // x2 x1 x0 0
        p1 = v1;                            // x3 x2 x1 x0
        p2 = vext_s16(v1,v2,1);             // x4 x3 x2 x1
        res = vadd_s16(p0,p1);
        res = vadd_s16(res,p2);
            vst1_s16(dst,res);
            dst += 4;
        }
}

/*
* 函数: add_intrinsics_rearrange_q
* 参数: 源数组指针src，输出数组指针dst，数组尺寸h/w
* 说明: 使用Arm Neon Intrinsics指令，使用q_registers (128bits)
*       增加(1) 访存数据对齐
*           (2) 数据拼接，减少访存次数
*/
void add_intrinsics_rearrange_q(int16_t * dst, int16_t * src, int h, int w){
    int16x8_t v0;
    int16x8_t v1;
    int16x8_t v2;
    int16x8_t p0;
    int16x8_t p1;
    int16x8_t p2;
    int16x8_t res;
    // first loop
    for(int j=0;j<h;j++){
        v1 = vld1q_s16(src);
        v2 = vld1q_s16(src+8);               
        src +=16;
        v0 = vdupq_n_s16(0);                 // 补零
        p0 = vextq_s16(v0,v1,7);             // x2 x1 x0 0
        p1 = v1;                            // x3 x2 x1 x0
        p2 = vextq_s16(v1,v2,1);             // x4 x3 x2 x1
        res = vaddq_s16(p0,p1
        );
        res = vaddq_s16(res,p2);
        vst1q_s16(dst,res);
        dst += 8;
        // main loop
        for(int i=0;i<(w/8-2);i++){
            v0 = v1;
            v1 = v2;
            v2 = vld1q_s16(src);
            src+=8;
            p0 = vextq_s16(v0,v1,7);             // x2 x1 x0 0
            p1 = v1;                            // x3 x2 x1 x0
            p2 = vextq_s16(v1,v2,1);             // x4 x3 x2 x1
            res = vaddq_s16(p0,p1);
            res = vaddq_s16(res,p2);
            vst1q_s16(dst,res);
            dst += 8;
        }
        // last loop
        v0 = v1;
        v1 = v2;
        v2 = vdupq_n_s16(0);
        p0 = vextq_s16(v0,v1,7);             // x2 x1 x0 0
        p1 = v1;                            // x3 x2 x1 x0
        p2 = vextq_s16(v1,v2,1);             // x4 x3 x2 x1
        res = vaddq_s16(p0,p1);
        res = vaddq_s16(res,p2);
            vst1q_s16(dst,res);
            dst += 8;
        }
}
#endif

