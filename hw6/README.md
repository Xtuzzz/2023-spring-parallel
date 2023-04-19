# 并行程序设计hw6

<p align=right>
  2000011068 李安
</p>


对于作业6，使用cmake工具时cmakelist如下：

```cmake
cmake_minimum_required(VERSION 3.25)
project(hw6)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)

add_executable(
        hw6 src/main.cpp
        src/Timer.cpp
        src/Input.cpp
        src/Matrix.cpp
)

```

使用命令`mkdir build -> cd build -> cmake .. -> make -> ./hw6`可以完成编译，
运行时需要将输入文件和可执行文件放到同一目录下。

### 目录结构
`include`和`src`，分别存放`.cpp`和`.h`文件

其中，`Timer.h`和`Timer.cpp`是本次作业完成的内容，具体完成了一个计时类，通过静态方法和`unordered_map`来存储了程序的运行时间和调用次数等信息。
并重载了`<<`运算符来进行输出。

### output
其中的一次输出是

```shell
+--------------------
| Profiling Summery ...
+---------------------------------------
| Class Name | Function Name |     Total |Called Times | Avg Times | Percentage |
|            |Total Run Time |0.000572 s |     1 times |0.000572 s |    100.0 % |
| Matrix     |           Mat |0.000002 s |     1 times |0.000002 s |      0.3 % |
| Matrix     |            << |0.000043 s |     2 times |0.000022 s |      7.5 % |
| Matrix     |           Mat |0.000002 s |     1 times |0.000002 s |      0.3 % |
| Matrix     |       mat_max |0.000002 s |     1 times |0.000002 s |      0.3 % |
| Matrix     |        Matrix |0.000013 s |     3 times |0.000004 s |      2.3 % |
| Input      |            << |0.000020 s |     1 times |0.000020 s |      3.5 % |
| Input      |          init |0.000416 s |     1 times |0.000416 s |     72.7 % |

```

