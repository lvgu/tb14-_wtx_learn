#include <chrono>
#include <iostream>


#include "../h/test.h"


void testChrono()
{

    auto start = std::chrono::high_resolution_clock::now(); // ��ʼʱ��
    factorial(10); // ������Ĳ��Ժ���
    auto end = std::chrono::high_resolution_clock::now();   // ����ʱ��
    std::chrono::duration<double, std::milli> elapsed = end - start; // ����ʱ��

    std::cout << "Execution time: " << elapsed.count() << " ms\n";
    return ;
}

void testCpp()
{

    testChrono();
}
