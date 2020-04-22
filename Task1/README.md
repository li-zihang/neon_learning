# Arm Neon learning

创建本项目的目的是学习Arm Neon。<br>
The purpose of this project is to learn Arm Neon.

----------------------
任务1：

1. 创建一个640*480的图片`image[640][480]`，填充随机数；

2. 进行加法运算，每个元素等于自身与相邻两个元素的和，每行第一个和最后一个元素分别向左、向右补零；
```
   ————————————————————————————————————————————————————————————————————
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * image[r-1][h] image[r][h] image[r+1][h] * * * * * *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   ————————————————————————————————————————————————————————————————————
                                     |
                                     |
                                     |
                                     V
   ————————————————————————————————————————————————————————————————————
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * image2[r+1][h] image2[r][h] image2[r+1][h]* * * * * *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   ————————————————————————————————————————————————————————————————————
   
   image2[r][h] = image[r-1][h] + image[r][h] + image[r+1][h]
   if(r==0)
   	image[r-1][h] = 0;
   if(r==640)
   	image[r+1][h] = 0;
```

3. 在`树莓派4B`上编译运行；

4. 编译方法：

   `g++ task1.cpp -mfpu=neon`

   `g++ task1.cpp -S`

   选项：

   (1) `-S` 生成汇编文件`task1.S`；

   (2) `-mfpu=neon` 使用`arm_neon.h` (取决于平台)；

   (3)  `-O3` 进行自动优化。

5. 使用方法

   `./a.out -s`

   (1) 分别使用`task2.cpp: 39-44` 所加入的函数，并观察运行时间差异；

   (2) `-s` 保存源和计算完成的数组到txt文件；
   
   (3) 编译时使用 `-O3` 进行优化，观察运行时间差异；

   (3) 编译时使用 `-S` 生成汇编文件`task1.S` ，观察使用不同`add` 函数的差异。
  
----------------------
Task1:

1. Create a 2-D array `image[640][480]` filled with random number;

2. Derive  `image2[640][480]` from `image[640][480]`. Every element equals the sum of itself and its neighbor two elements. For every first and last element of every line, pad a '0'.
```
   ————————————————————————————————————————————————————————————————————
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * image[r-1][h] image[r][h] image[r+1][h] * * * * * *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   ————————————————————————————————————————————————————————————————————
                                     |
                                     |
                                     |
                                     V
   ————————————————————————————————————————————————————————————————————
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * image2[r+1][h] image2[r][h] image2[r+1][h]* * * * * *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
   ————————————————————————————————————————————————————————————————————
   
   image2[r][h] = image[r-1][h] + image[r][h] + image[r+1][h]
   if(r==0)
   	image[r-1][h] = 0;
   if(r==640)
   	image[r+1][h] = 0;
```

3. Compile and run this demo on `Raspberry 4B`

4. Compile method:

   `g++ task1.cpp -mfpu=neon`

   `g++ task1.cpp -S`

   options:

   (1) `-S` to produce assembly language file `task.S`.

   (2) `-mfpu=neon` to use `arm_neon.h` (up to platform).

   (3) `-O3` to optimise program automatically.
  
   
5. How to use

   `./a.out -s`

   (1) Use the functions on`task2.cpp: 39-44` respectively, and observe the program running time difference;

   (2) `-s` to save source and destination array. 

   (3) Use `-O3` while compling, observe the program running time difference.

   (4) Use `-S` while compling, and observe the difference between different `add` functions.

----------------------

2020/04/16
上海 Shanghai
