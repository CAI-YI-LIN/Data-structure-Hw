#include <iostream>
#include <chrono> // 引入計時庫
using namespace std;

// 使用迴圈生成集合的冪集，接受一個字符陣列和集合大小
void PowersetIterative(char set[], int n) {
    // 計算總子集數量
    int total_subsets = 1 << n; // 2^n

    // 遍歷所有子集的索引
    for (int i = 0; i < total_subsets; ++i) {
        cout << "{";
        // 生成每個子集
        for (int j = 0; j < n; ++j) {
            // 如果第 j 位元在 i 中被設置為 1，則包括 set[j]
            if (i & (1 << j)) {
                cout << set[j] << " ";
            }
        }
        cout << "}\n"; // 輸出子集的結尾
    }
}

int main() {
    char set[] = { 'a', 'b', 'c' }; // 定義字符集合
    int n = sizeof(set) / sizeof(set[0]); // 計算集合大小            
    cout << "PowersetIterative:\n";
    auto start = chrono::high_resolution_clock::now(); // 開始計時

    PowersetIterative(set, n); // 使用迴圈生成冪集

    auto end = chrono::high_resolution_clock::now(); // 結束計時
    chrono::duration<double> elapsed = end - start; // 計算耗時
    cout << "Elapsed time: " << elapsed.count() << " seconds\n"; // 輸出耗時

    return 0;
}
/*
測資 set[] = { 'a', 'b', 'c'}
PowersetIterative:
{}
{a }
{b }
{a b }
{c }
{a c }
{b c }
{a b c }

測資 set[] = { 'a', 'b', 'c','d'}
PowersetIterative:
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

測資(11個) set[] = { 'a', 'b', 'c','d','e','f','g','h','i','j','k'}
PowersetIterative:
....
Elapsed time: 0.333289 seconds


測資(12個) set[] = { 'a', 'b', 'c','d','e','f','g','h','i','j','k','l' }
PowersetIterative:
....
Elapsed time: 0.770582 seconds


測資(13個) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m' }
PowersetIterative:
....
Elapsed time: 1.37522 seconds


測資(14個) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n' }
PowersetIterative:
....
Elapsed time: 2.70392 seconds
*/