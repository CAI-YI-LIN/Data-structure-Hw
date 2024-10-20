#include <iostream>
#include <chrono>  // �ޤJ�ɶ����q�����Y�ɮ�
using namespace std;

const int STACK_SIZE = 250000; // �w�q���|���j�p

// �Τ@�Ӱ}�C�������|�� Ackermann �D���j�禡
int AckermannSingleStack(int m, int n)
{
    int stack_m[STACK_SIZE]; // �ϥΰ}�C�������|
    int top = 0; // ���|������
    stack_m[top] = m; // �N��l m ���J���|

    // ����|�����Ů�
    while (top >= 0)
    {
        m = stack_m[top]; // ���X���|���� m
        top--; // �X���|

        if (m == 0) {
            n = n + 1; // �p�G m �� 0�A�h n + 1
        }
        else if (n == 0) {
            n = 1; // �p�G n �� 0�A�] n �� 1
            stack_m[++top] = m - 1; // �۷��I�s Ackermann(m - 1, 1)
        }
        else { // �_�h�����I�s Ackermann(m, n - 1)
            stack_m[++top] = m - 1; // ������ A(m - 1, A(m, n - 1))
            stack_m[++top] = m; // �M��A���� A(m, n - 1)
            n = n - 1; // �N n �� 1
        }
    }

    return n; // ��^�̲׭p�⵲�G n
}

int main()
{
    int m, n;

    // �`��Ū�� m �M n ����
    while (cin >> m >> n)
    {
        // �}�l�p��
        auto start = chrono::high_resolution_clock::now();

        int result = AckermannSingleStack(m, n); // ����p��

        // ����p��
        auto end = chrono::high_resolution_clock::now();

        // �p�����ɶ�
        chrono::duration<double> duration = end - start;

        // ��X���G�M����ɶ�
        cout << "Ackermann Single Stack: " << result << endl;
        cout << "Execution time: " << duration.count() << " seconds" << endl;
    }

    return 0;
}

/*
�i�������
    ������(3,13)=65533
    ������(4, 1)=65533

�̤j�Ө�����
    ������(3,14)=131069

STACK_SIZE���|�j�p�����i�Ө�����
    ��100000 -> (3,13) = 65533
    ��200000 -> (3,14) = 131069
*/
