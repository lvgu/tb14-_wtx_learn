#include <stdio.h>
#include <stdlib.h>


#if 0


#define TARGET_TOTAL 100000 // 1000.00
#define MAX_GOODS 24

double goods[] = {9, 5.4, 10.3, 75, 37, 45, 29.8, 28.6, 53.2, 44, 129.6, 30,
                  26, 41, 42, 25.2, 23.8, 5.8, 3.6, 2.1, 38, 104, 62, 96.6};

int n; // 每个商品最多可以购买的数量
int totalWays = 0; // 记录满足条件的方案数

void find_combinations(int index, int current_sum) {
    if (current_sum > TARGET_TOTAL) return; // 超过目标总价，回溯

    if (index == MAX_GOODS) {
        if (current_sum == TARGET_TOTAL) totalWays++; // 找到有效方案
        return;
    }

    for (int i = 0; i <= n; i++) {
        find_combinations(index + 1, current_sum + (int)(goods[index] * 100) * i);
    }
}


void test()
{
    n = 10;

    find_combinations(0, 0);

    printf("满足总价为1000元的方案数为: %d\n", totalWays);

}


#endif // 0


int main()
{
    test();
    return 0;
}
