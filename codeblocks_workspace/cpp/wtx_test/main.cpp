#include <iostream>
#include <vector>

using namespace std;

int main() {
    // ��Ʒ����
    double goods[] = {9,5.4,10.3,75,37,45,29.8,28.6,53.2,44,129.6,30,26,41,42,25.2,23.8,5.8,3.6,2.1,38,104,62,96.6};
    int m = sizeof(goods) / sizeof(goods[0]);  // ��Ʒ����
    int n = 10; // ÿ����Ʒ��������n��
    const int target = 1000;  // Ŀ���ܼ�
    vector<int> dp(target + 1, 0); // dp���飬��ʼ��Ϊ0
    dp[0] = 1; // ��ʼ״̬

    // ����ÿ����Ʒ
    for (int i = 0; i < m; i++) {
        int price = (int)(goods[i] * 10); // �Ŵ�10��������С�����
        // �Ӵ�С����dp����
        for (int j = target * 10; j >= price; j--) {
            for (int k = 1; k <= n && k * price <= j; k++) {
                dp[j] += dp[j - k * price];
            }
        }
    }

    cout << "������: " << dp[target * 10] << endl; // ������
    return 0;
}


