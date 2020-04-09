/*
*   This file is used to test the Neon instinsic.
*   by: Zihang Li 
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <fstream>

#define row 480
#define colomn 640
#define repeat_count 1000

using namespace std;            // 640 , 480
int16_t image[row][colomn];
int16_t image_2[row][colomn];

int random_num();
void add_neig(int16_t * dst, int16_t * src, int h, int w);
void add2_neig(int16_t *dst, int16_t *src, int h, int w);
void add3_neig(int h, int w);

int main(){
    int row_t = 480;
    int colomn_t = 640;
    ofstream later_array("./later.txt");    
    // ------------ time calculation preparation
    struct timeval t0, t1;
    float total_time = 0.f;
    float min_time = __DBL_MAX__;
    float max_time = -__DBL_MAX__;    
    // ------------ time calculation preparation

    random_num();               // put an 640*480 image into an array
    gettimeofday(&t0, NULL);    // time start

    // ------------- calculation start
    for(int t = 0; t < repeat_count; t++)
    {
        // The start of calculation
        add3_neig(row_t,colomn_t);                                            // 直接数组
        //add2_neig(&(image_2[0][0]),&(image[0][0]),row_t,colomn_t);          // 计算指针
	    //add_neig(&(image_2[0][0]),&(image[0][0]),row_t,colomn_t);           // 直接指针
        // The end of calculation
    }
    // ------------- calculation end

    gettimeofday(&t1, NULL);    // time end 
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
    ofstream previous_array("./previous.txt");
    srand((int)time(0));
    for(int i=0;i<row;i++){
        for(int j=0; j<colomn; j++){
                image[i][j] = rand()% 10000;         // 0~65536
                previous_array << dec << image[i][j] << " ";
        }
        previous_array << endl;
    }
    return 0;
}

void add3_neig(int h, int w){
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

void add2_neig(int16_t *dst, int16_t *src, int h, int w){
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

void add_neig(int16_t * dst, int16_t * src, int h, int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j == 0){
                *dst++ = *src + *(src+1);
                src++;
            }
            else if(j == w-1){
                *dst++ = *src + *(src-1);
		        src++;
		    }
            else
		    {
                *dst++ = *src + *(src+1) + *(src-1);
		        src++;
		    }
        }
}
	

} 


