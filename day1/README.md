This file will be in both Chinese and English.
这篇文档将使用中英文。

学习Neon。在这里添加了一个image作为例子。
在这个例子中，此image是一个二维数组，它填充为640*480的随机数。
例子的目的是，得到一个新的数组，新的数组每个元素为其与相邻两个元素的和。

1. 规则如下：
  (1) image[i][j] = image[i][j] + image[i][j-1] + image[i][j+1];
  (2) image[i][j] = image[i][j] + image[i][j+1], 在每行的头;
  (3) image[i][j] = image[i][j] + image[i][j-1], 在每行末尾。
  
2. 数据格式
  使用int16_t，为了方便，限定随机数在0～10000之间，这样三个随机数的和不会超过30000，不会发生溢出等情况；
  
3. 计算时间
  使用了sys/time.h中的相关函数计算时间。
-----------------------------------------

Here I start Neon. An image is added into this project as an example. 
In this example, the image is a two-dimension array by 640*480, and it is filled by random numbers. 
The purpose is to get a new array by adding each element of this array with its neighbor two elements.

1.Here are rules:
  (1) image[i][j] = image[i][j] + image[i][j-1] + image[i][j+1];
  (2) image[i][j] = image[i][j] + image[i][j+1], for the first element of every row;
  (3) image[i][j] = image[i][j] + image[i][j-1], for the last element of every row.

2. data format
  Use int16_t. In order to simplify, the range of random number is set between 0 and 10000. 
  Then the sum of this three random numbers would not supress 30000. You are happy with it because no data overflow occurs;
  
3. Time duration calculation
  Use sys/time.h including some functions to calculation time speeding.
