#include <iostream>
#include <chrono> // 引入計時庫
using namespace std;

// 生成集合的冪集，接受一個字符陣列、集合大小和當前索引
void PowersetRecursion(char set[], int n, int i)
{
    // 如果索引超過2^n，則返回（已經處理所有可能的子集）
    if (i >= (1 << n)) return; // (1 << n) 等同於 2^n

    cout << "{"; // 輸出子集的開頭
    // 遍歷集合中的每個元素
    for (int j = 0; j < n; ++j)
    {
        // 使用位元運算檢查第 j 個元素是否應該包含在當前子集中
        if (i & (1 << j)) // (1 << j) 代表第 j 位元
            cout << set[j] << " "; // 輸出該元素
    }
    cout << "}\n"; // 輸出子集的結尾

    // 生成下一個子集，i + 1 代表下一个可能的子集
    PowersetRecursion(set, n, i + 1);
}

int main() {
    char set[] = { 'a', 'b', 'c'}; // 定義集合
    int n = sizeof(set) / sizeof(set[0]); // 計算集合的大小（元素數量）

    cout << "PowersetRecursion:\n";
    auto start = chrono::high_resolution_clock::now(); // 開始計時

     PowersetRecursion(set, n, 0); // 從索引0開始生成冪集

    auto end = chrono::high_resolution_clock::now(); // 結束計時
    chrono::duration<double> elapsed = end - start; // 計算耗時
    cout << "Elapsed time: " << elapsed.count() << " seconds\n"; // 輸出耗時

    return 0;
}

/*
測資 set[] = { 'a', 'b', 'c'}
PowersetRecursion:
{}
{a }
{b }
{a b }
{c }
{a c }
{b c }
{a b c }

測資 set[] = { 'a', 'b', 'c','d'}
PowersetRecursion:
{}
{a }
{b }
{a b }
{c }
{a c }
{b c }
{a b c }
{d }
{a d }
{b d }
{a b d }
{c d }
{a c d }
{b c d }
{a b c d }

測資(11個) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k' }
PowersetRecursion:
....
Elapsed time: 0.346304 seconds


測資(12個) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l' }
PowersetRecursion:
....
Elapsed time: 0.624426 seconds


測資(13個) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m' }
PowersetRecursion:
....
失敗
*/
