#include<iostream>
using namespace std;

const int STACK_SIZE = 250000; // 定義堆疊的大小

// 用一個陣列模擬堆疊的 Ackermann 非遞迴函式
int AckermannSingleStack(int m, int n)
{
    int stack_m[STACK_SIZE]; // 使用陣列模擬堆疊，大小可以根據需求調整
    int top = 0; // 堆疊頂指標
    stack_m[top] = m; // 將初始 m 推入堆疊

    // 當堆疊不為空時
    while (top >= 0)
    {
        m = stack_m[top]; // 取出堆疊頂的 m
        top--; // 出堆疊

        if (m == 0) {
            n = n + 1; // 如果 m 為 0，則 n + 1
        }
        else if (n == 0) {
            n = 1; // 如果 n 為 0，設 n 為 1
            stack_m[++top] = m - 1; // 相當於呼叫 Ackermann(m - 1, 1)
        }
        else { // 否則模擬呼叫 Ackermann(m, n - 1)
            stack_m[++top] = m - 1; // 先模擬 A(m - 1, A(m, n - 1))
            stack_m[++top] = m; // 然後再模擬 A(m, n - 1)
            n = n - 1; // 將 n 減 1
        }
    }

    return n; // 返回最終計算結果 n
}

int main()
{
    int m, n;
    // 循環讀取 m 和 n 的值
    while (cin >> m >> n)
    {
        cout << "Ackermann Single Stack: " << AckermannSingleStack(m, n) << endl; // 輸出結果
    }
    return 0;
}
/*
可執行測資
    ˙測資(3,13)=65533
    ˙測資(4, 1)=65533

最大承受測資
    ˙測資(3,14)=131069

STACK_SIZE堆疊大小對應可承受測資
    ˙100000 -> (3,13) = 65533
    ˙200000 -> (3,14) = 131069
*/
