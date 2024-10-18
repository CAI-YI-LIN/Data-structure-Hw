#include<iostream>
using namespace std;

// �w�q���j�� Ackermann �禡
int AckermannRecursive(int m, int n)
{
    // �p�G m �� 0�A��^ n + 1
    if (m == 0) return (n + 1);
    // �p�G n �� 0�A�N m �� 1�A�ñN n �]�� 1 �i�滼�j
    else if (n == 0) return AckermannRecursive(m - 1, 1);
    // �_�h�A�i��⦸���j�p��
    else return AckermannRecursive(m - 1, AckermannRecursive(m, n - 1));
}

int main()
{
    int m, n;
    // �`��Ū�� m �M n ����
    while (cin >> m >> n)
    {
        // ��X Ackermann �禡���p�⵲�G
        cout << "Ackermann Recursive: " << AckermannRecursive(m, n) << endl;
    }
    return 0;
}
/*
�̤j�Ө�����
    ������(3,9)=4093
*/

