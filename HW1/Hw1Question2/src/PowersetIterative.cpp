#include <iostream>
#include <chrono> // �ޤJ�p�ɮw
using namespace std;

// �ϥΰj��ͦ����X�������A�����@�Ӧr�Ű}�C�M���X�j�p
void PowersetIterative(char set[], int n) {
    // �p���`�l���ƶq
    int total_subsets = 1 << n; // 2^n

    // �M���Ҧ��l��������
    for (int i = 0; i < total_subsets; ++i) {
        cout << "{";
        // �ͦ��C�Ӥl��
        for (int j = 0; j < n; ++j) {
            // �p�G�� j �줸�b i ���Q�]�m�� 1�A�h�]�A set[j]
            if (i & (1 << j)) {
                cout << set[j] << " ";
            }
        }
        cout << "}\n"; // ��X�l��������
    }
}

int main() {
    char set[] = { 'a', 'b', 'c' }; // �w�q�r�Ŷ��X
    int n = sizeof(set) / sizeof(set[0]); // �p�ⶰ�X�j�p            
    cout << "PowersetIterative:\n";
    auto start = chrono::high_resolution_clock::now(); // �}�l�p��

    PowersetIterative(set, n); // �ϥΰj��ͦ�����

    auto end = chrono::high_resolution_clock::now(); // �����p��
    chrono::duration<double> elapsed = end - start; // �p��Ӯ�
    cout << "Elapsed time: " << elapsed.count() << " seconds\n"; // ��X�Ӯ�

    return 0;
}
/*
���� set[] = { 'a', 'b', 'c'}
PowersetIterative:
{}
{a }
{b }
{a b }
{c }
{a c }
{b c }
{a b c }

���� set[] = { 'a', 'b', 'c','d'}
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

����(11��) set[] = { 'a', 'b', 'c','d','e','f','g','h','i','j','k'}
PowersetIterative:
....
Elapsed time: 0.333289 seconds


����(12��) set[] = { 'a', 'b', 'c','d','e','f','g','h','i','j','k','l' }
PowersetIterative:
....
Elapsed time: 0.770582 seconds


����(13��) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m' }
PowersetIterative:
....
Elapsed time: 1.37522 seconds


����(14��) set[] ={ 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n' }
PowersetIterative:
....
Elapsed time: 2.70392 seconds
*/