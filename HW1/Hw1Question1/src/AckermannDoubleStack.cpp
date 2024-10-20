#include <iostream>
#include <chrono>  // 引入時間測量的標頭檔案
using namespace std;

const int STACK_SIZE = 50000;  // 設定一個足夠大的堆疊空間

// 用兩個陣列模擬堆疊的 Ackermann 非遞迴函式
int AckermannDoubleStack(int m, int n) {
    // 使用兩個陣列來模擬堆疊
    int stack_m[STACK_SIZE]; // 存放 m 的值
    int stack_n[STACK_SIZE]; // 存放 n 的值

    int top = 0;  // 初始化堆疊頂部指針
    stack_m[top] = m; // 將初始 m 推入堆疊
    stack_n[top] = n; // 將初始 n 推入堆疊

    // 當堆疊不為空時
    while (top >= 0) {
        m = stack_m[top]; // 取出堆疊頂的 m
        n = stack_n[top]; // 取出堆疊頂的 n
        top--; // 出堆疊

        if (m == 0) {
            if (top >= 0) {
                stack_n[top] = n + 1;  // 當 m == 0 時，更新 n 為 n + 1
            }
            else {
                return n + 1;  // 堆疊空時，返回計算結果
            }
        }
        else if (n == 0) {
            top++; // 進入下一層遞迴
            stack_m[top] = m - 1; // 將 (m-1) 推入堆疊
            stack_n[top] = 1;  // 將 n 設為 1
        }
        else {
            top++; // 進入下一層遞迴
            stack_m[top] = m - 1; // 將 (m-1) 推入堆疊
            stack_n[top] = -1;  // 標記需要更新的 n
            top++; // 進入下一層
            stack_m[top] = m; // 將 m 推入堆疊
            stack_n[top] = n - 1; // 將 (n-1) 推入堆疊
        }
    }

    return -1;  // 永遠不應該到這裡，作為保險的返回值
}

int main()
{
    int m, n;

    // 循環讀取 m 和 n 的值
    while (cin >> m >> n)
    {
        // 開始計時
        auto start = chrono::high_resolution_clock::now();

      
        int result = AckermannDoubleStack(m, n);

        // 停止計時
        auto end = chrono::high_resolution_clock::now();

        // 計算執行時間
        chrono::duration<double> duration = end - start;

        // 輸出結果和執行時間
        cout << "Ackermann Double Stack: " << result << endl;
        cout << "Execution time: " << duration.count() << " seconds" << endl;
    }

    return 0;
}

/*
最大承受測資
    ˙測資(3,12)=32765

STACK_SIZE堆疊大小對應可承受測資
    ˙[50000] --> (3,12) = 32765
*/
