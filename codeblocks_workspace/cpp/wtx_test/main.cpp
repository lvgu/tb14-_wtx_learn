#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 商品单价
    double goods[] = {9,5.4,10.3,75,37,45,29.8,28.6,53.2,44,129.6,30,26,41,42,25.2,23.8,5.8,3.6,2.1,38,104,62,96.6};
    int m = sizeof(goods) / sizeof(goods[0]);  // 商品个数
    int n = 10; // 每个商品最多可以买n个
    const int target = 1000;  // 目标总价
    vector<int> dp(target + 1, 0); // dp数组，初始化为0
    dp[0] = 1; // 初始状态

    // 遍历每个商品
    for (int i = 0; i < m; i++) {
        int price = (int)(goods[i] * 10); // 放大10倍，避免小数误差
        // 从大到小更新dp数组
        for (int j = target * 10; j >= price; j--) {
            for (int k = 1; k <= n && k * price <= j; k++) {
                dp[j] += dp[j - k * price];
            }
        }
    }

    cout << "方案数: " << dp[target * 10] << endl; // 输出结果
    return 0;
}


