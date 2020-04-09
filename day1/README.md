This file will be in both Chinese and English. <br>
这篇文档将使用中英文。<br>

---

开始学习Neon。在这里添加了一个image作为例子。<br>
在这个例子中，此image是一个二维数组，它填充为640*480的随机数。<br>
例子的目的是，得到一个新的数组，新的数组每个元素为其与相邻两个元素的和。<br>

1. 规则如下：<br>
  (1) image[i][j] = image[i][j] + image[i][j-1] + image[i][j+1];<br>
  (2) image[i][j] = image[i][j] + image[i][j+1], 在每行的头;<br>
  (3) image[i][j] = image[i][j] + image[i][j-1], 在每行末尾。<br>
  <br>
  2. 数据格式<br>
  使用int16_t，为了方便，限定随机数在0～10000之间，这样三个随机数的和不会超过30000，不会发生溢出等情况；<br>
3. 计算时间<br>
  使用了sys/time.h中的相关函数计算时间。<br>
4. 编译与运行<br>
  ```
  pi@raspberrypi:$ g++ image_test.cpp 
  pi@raspberrypi:$ ./a.out 
--------------------------------------
Avg time per run is 7.48944 ms
  ```
---

Here I start Neon. An image is added into this project as an example.<br>
In this example, the image is a two-dimension array by 640*480, and it is filled by random numbers. <br>
The purpose is to get a new array by adding each element of this array with its neighbor two elements.<br>

1.Here are rules:<br>
  (1) image[i][j] = image[i][j] + image[i][j-1] + image[i][j+1];<br>
  (2) image[i][j] = image[i][j] + image[i][j+1], for the first element of every row;<br>
  (3) image[i][j] = image[i][j] + image[i][j-1], for the last element of every row.<br>

2. data format<br>
  Use int16_t. In order to simplify, the range of random number is set between 0 and 10000. <br>
  Then the sum of this three random numbers would not supress 30000. You are happy with it because no data overflow occurs;<br>
  
3. Time duration calculation<br>
  Use sys/time.h including some functions to calculation time speeding.<br>

4. Compile and run
```
  pi@raspberrypi:$ g++ image_test.cpp 
  pi@raspberrypi:$ ./a.out 
--------------------------------------
Avg time per run is 7.48944 ms
  ```

---
Platform: Raspberry 4B, BCM2711， Arm-Cortex A72 @1.5GHz