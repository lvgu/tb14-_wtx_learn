#include <chrono>
#include <iostream>


#include "../h/test.h"


void testChrono()
{

    auto start = std::chrono::high_resolution_clock::now(); // 开始时间
    factorial(10); // 调用你的测试函数
    auto end = std::chrono::high_resolution_clock::now();   // 结束时间
    std::chrono::duration<double, std::milli> elapsed = end - start; // 计算时间

    std::cout << "Execution time: " << elapsed.count() << " ms\n";
    return ;
}

void testCpp()
{

    testChrono();
}
