#include<iostream>
using namespace std;

// 定義遞迴的 Ackermann 函式
int AckermannRecursive(int m, int n)
{
    // 如果 m 為 0，返回 n + 1
    if (m == 0) return (n + 1);
    // 如果 n 為 0，將 m 減 1，並將 n 設為 1 進行遞迴
    else if (n == 0) return AckermannRecursive(m - 1, 1);
    // 否則，進行兩次遞迴計算
    else return AckermannRecursive(m - 1, AckermannRecursive(m, n - 1));
}

int main()
{
    int m, n;
    // 循環讀取 m 和 n 的值
    while (cin >> m >> n)
    {
        // 輸出 Ackermann 函式的計算結果
        cout << "Ackermann Recursive: " << AckermannRecursive(m, n) << endl;
    }
    return 0;
}
/*
最大承受測資
    ˙測資(3,9)=4093
*/

